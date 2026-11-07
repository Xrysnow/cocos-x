#include "AudioSource.h"
#include "AudioSoundData.h"
#include "AudioDecoder.h"
#include "AudioEngine.h"
#include "AudioFilter.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <new>

NS_CC_BEGIN
using namespace AudioInternal;

namespace
{
	double queueSteadySeconds()
	{
		return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
	}

	// Accessed only with the process-lifetime AudioPool lock held. A query
	// failure latches uncalibrated output until a new context is created.
	int latencyGeneration = -1;
	bool latencyFailed = false;
#ifdef AL_SOFT_source_latency
	LPALGETSOURCEI64VSOFT queueGetSourcei64v = nullptr;
#endif
}

constexpr double PI = 3.14159265358979323846;
constexpr double TORAD_ = PI / 180.0;
constexpr double TODEG_ = 180.0 / PI;
#define TORAD(x)	(float)(x*TORAD_)
#define TODEG(x)	(float)(x*TODEG_)

AudioStaticDataBuffer::AudioStaticDataBuffer(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq)
	: buffer(0)
	, size(size)
	, data()
	, format(format)
	, freq(freq)
	, generation(AudioEngine::getDeviceGeneration())
{
	// Keep a private PCM copy so the buffer can be re-uploaded after a
	// context recreation (the AudioSource does not hold the original AudioSoundData).
	if (size > 0 && data)
	{
		this->data.resize(size);
		memcpy(this->data.data(), data, size);
	}
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, size, freq);
}

AudioStaticDataBuffer::~AudioStaticDataBuffer()
{
	// Skip the AL delete when the context that created the buffer is gone
	// to avoid free an unrelated buffer of a newer context.
	if (AudioEngine::getDeviceGeneration() == generation)
		alDeleteBuffers(1, &buffer);
}

void AudioStaticDataBuffer::reload()
{
	// Already current (several Sources may share this buffer).
	if (generation == AudioEngine::getDeviceGeneration())
		return;

	// The old id belongs to a destroyed context - never delete it, just
	// replace it and re-upload the retained PCM.
	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data.data(), size, freq);
	generation = AudioEngine::getDeviceGeneration();
}

AudioSource::AudioSource()
	: sourceType(Type::MAX_ENUM)
{
}

bool AudioSource::initWithSoundData(AudioSoundData* soundData)
{
	sourceType = Type::STATIC;
	pool = AudioPool::getInstance();
	if (!pool)
		return false;
	sampleRate = soundData->getSampleRate();
	channels = soundData->getChannelCount();
	bitDepth = soundData->getBitDepth();
	const auto fmt = AudioEngine::getFormat(soundData->getBitDepth(), soundData->getChannelCount());
	if (fmt == AL_NONE)
	{
		InvalidFormatException(soundData->getChannelCount(), soundData->getBitDepth());
		return false;
	}

	staticBuffer = new (std::nothrow) AudioStaticDataBuffer(fmt, soundData->getData(), (ALsizei)soundData->getSize(), sampleRate);
	if (!staticBuffer)
		return false;
	staticBuffer->autorelease();
	staticBuffer->retain();

	position.setZero();
	velocity.setZero();
	direction.setZero();

	// Remember which device generation the buffer ids were created for, so
	// prepareAtomic() can detect stale ids after a context recreation.
	bufferGeneration = AudioEngine::getDeviceGeneration();

	for (int i = 0; i < AudioEngine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return true;
}

bool AudioSource::initWithDecoder(AudioDecoder* _decoder)
{
	sourceType = Type::STREAM;
	pool = AudioPool::getInstance();
	if (!pool)
	{
		AINFO("failed for pool");
		return false;
	}
	decoder = _decoder;
	if (decoder)
		decoder->retain();
	else
	{
		AINFO("failed for decoder");
		return false;
	}
	sampleRate = decoder->getSampleRate();
	channels = decoder->getChannelCount();
	bitDepth = decoder->getBitDepth();
	buffers = DEFAULT_BUFFERS;
	if (AudioEngine::getFormat(decoder->getBitDepth(), decoder->getChannelCount()) == AL_NONE)
	{
		AINFO("failed for format");
		InvalidFormatException(decoder->getChannelCount(), decoder->getBitDepth());
		return false;
	}

	for (int i = 0; i < buffers; i++)
	{
		ALuint buf;
		alGenBuffers(1, &buf);
		if (alGetError() == AL_NO_ERROR)
			unusedBuffers.push(buf);
		else
		{
			buffers = i;
			break;
		}
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	bufferGeneration = AudioEngine::getDeviceGeneration();

	for (int i = 0; i < AudioEngine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return true;
}

bool AudioSource::init(int _sampleRate, int _bitDepth, int _channels, int _buffers)
{
	sourceType = Type::QUEUE;
	pool = AudioPool::getInstance();
	if (!pool)
		return false;
	sampleRate = _sampleRate;
	channels = _channels;
	bitDepth = _bitDepth;
	buffers = _buffers;
	ALenum fmt = AudioEngine::getFormat(bitDepth, channels);
	if (fmt == AL_NONE || sampleRate <= 0)
	{
		InvalidFormatException(channels, bitDepth);
		return false;
	}

	if (buffers < 1)
		buffers = DEFAULT_BUFFERS;
	if (buffers > MAX_BUFFERS)
		buffers = MAX_BUFFERS;

	alGetError();
	for (int i = 0; i < buffers; i++)
	{
		ALuint buf;
		alGenBuffers(1, &buf);
		if (alGetError() == AL_NO_ERROR)
			unusedBuffers.push(buf);
		else
		{
			buffers = i;
			break;
		}
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	bufferGeneration = AudioEngine::getDeviceGeneration();

	for (int i = 0; i < AudioEngine::getMaxSourceEffectCount(); i++)
		slotlist.push(i);
	return buffers > 0;
}

bool AudioSource::initWithOther(const AudioSource &s)
{
	sourceType = s.sourceType;
	pool = s.pool;
	valid = false;
	staticBuffer = s.staticBuffer;
	pitch = s.pitch;
	volume = s.volume;
	relative = s.relative;
	looping = s.looping;
	minVolume = s.minVolume;
	maxVolume = s.maxVolume;
	referenceDistance = s.referenceDistance;
	rolloffFactor = s.rolloffFactor;
	maxDistance = s.maxDistance;
	cone = s.cone;
	offsetSamples = 0;
	sampleRate = s.sampleRate;
	channels = s.channels;
	bitDepth = s.bitDepth;
	decoder = nullptr;
	toLoop = 0;
	buffers = s.buffers;

	if (staticBuffer)
		staticBuffer->retain();
	if (sourceType == Type::STREAM)
	{
		if (s.decoder)
			decoder = s.decoder->clone();
		if (decoder)
			decoder->retain();
	}
	if (sourceType != Type::STATIC)
	{
		for (int i = 0; i < buffers; i++)
		{
			ALuint buf;
			alGenBuffers(1, &buf);
			if (alGetError() == AL_NO_ERROR)
				unusedBuffers.push(buf);
			else
			{
				buffers = i;
				break;
			}
		}
	}

	bufferGeneration = AudioEngine::getDeviceGeneration();

	if (s.directfilter)
		directfilter = s.directfilter->clone();

	for (auto e : s.effectmap)
	{
		AudioFilter *filter = e.second.filter ? e.second.filter->clone() : nullptr;
		effectmap[e.first] = { filter, e.second.slot, e.second.target };
	}

	position.setZero();
	velocity.setZero();
	direction.setZero();

	for (int i = 0; i < AudioEngine::getMaxSourceEffectCount(); i++)
	{
		// filter out already taken slots
		bool push = true;
		for (auto& e : effectmap)
		{
			if (e.second.slot)
			{
				push = false;
				break;
			}
		}
		if (push)
			slotlist.push(i);
	}
	return true;
}

AudioSource::~AudioSource()
{
	AudioSource::stop();
	// Buffer disposal participates in the same lock as context recreation.
	auto disposalLock = pool ? pool->lock() : std::unique_lock<std::mutex>();

	if (sourceType != Type::STATIC)
	{
		// Skip the AL deletes when the context that created these ids is gone
		if (bufferGeneration == AudioEngine::getDeviceGeneration())
		{
			while (!streamBuffers.empty())
			{
				alDeleteBuffers(1, &streamBuffers.front());
				streamBuffers.pop();
			}
			while (!unusedBuffers.empty())
			{
				alDeleteBuffers(1, &unusedBuffers.top());
				unusedBuffers.pop();
			}
		}
	}

	delete directfilter;
	for (auto& e : effectmap)
		delete e.second.filter;
	if (staticBuffer)
		staticBuffer->release();
	if (decoder)
		decoder->release();
}

AudioSource* AudioSource::createFromSoundData(AudioSoundData* soundData)
{
	if (!AudioEngine::isValid() || !soundData)
		return nullptr;
	auto ret = new (std::nothrow) AudioSource();
	if (ret&&ret->initWithSoundData(soundData))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

AudioSource* AudioSource::createFromDecoder(AudioDecoder* decoder)
{
	if (!AudioEngine::isValid() || !decoder)
		return nullptr;
	auto ret = new (std::nothrow) AudioSource();
	if (ret&&ret->initWithDecoder(decoder))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

AudioSource* AudioSource::create(int sampleRate, int bitDepth, int channels, int buffers)
{
	auto ret = createOwnedQueue(sampleRate, bitDepth, channels, buffers);
	if (ret)
		ret->autorelease();
	return ret;
}

AudioSource* AudioSource::createOwnedQueue(int sampleRate, int bitDepth, int channels, int buffers)
{
	if (!AudioEngine::isValid())
		return nullptr;
	auto ownerPool = AudioPool::getInstance();
	auto ret = new (std::nothrow) AudioSource();
	bool initialized = false;
	{
		auto lock = ownerPool->lock();
		if (ret && AudioEngine::isValid())
			initialized = ret->init(sampleRate, bitDepth, channels, buffers);
	}
	if (initialized)
		return ret;
	delete ret;
	return nullptr;
}

AudioSource *AudioSource::clone()
{
	if (!AudioEngine::isValid())
		return nullptr;
	auto ret = new (std::nothrow) AudioSource();
	if (ret&&ret->initWithOther(*this))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool AudioSource::play()
{
	if (!AudioEngine::isValid() || !pool)
		return false;
	auto l = pool->lock();
	if (!AudioEngine::isValid())
		return false;
	if (sourceType == Type::QUEUE && sessionControlled &&
		(!queuePlaybackAllowed || AudioEngine::isSuspended() ||
		 bufferGeneration != AudioEngine::getDeviceGeneration()))
		return false;
	ALuint out;
	char wasPlaying;
	if (!pool->assignSource(this, out, wasPlaying))
		return valid = false;
	if (!wasPlaying)
		return valid = playAtomic(out);
	if (sourceType == Type::QUEUE)
	{
		alGetError();
		alSourcePlay(out);
		queueError = alGetError();
		if (queueError != AL_NO_ERROR)
		{
			releaseSource();
			return false;
		}
		queueStarted = true;
		queueStopReason = QueueStopReason::None;
		return valid = true;
	}
	resumeAtomic();
	return valid = true;
}

void AudioSource::stop()
{
	if (!pool)
		return;
	auto l = pool->lock();
	if (sourceType == Type::QUEUE)
	{
		clearQueueAtomic(QueueStopReason::Explicit);
		return;
	}
	if (!valid)
		return;
	releaseSource();
}

void AudioSource::pause()
{
	if (!pool)
		return;
	auto lock = pool->lock();
	if (bufferGeneration == AudioEngine::getDeviceGeneration())
		pauseAtomic();
}

bool AudioSource::isPlaying() const
{
	if (!valid)
		return false;

	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

bool AudioSource::isFinished() const
{
	if (!valid)
		return false;

	if (sourceType == Type::STREAM && (isLooping() || !decoder->isFinished()))
		return false;

	ALenum state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return state == AL_STOPPED;
}

bool AudioSource::update()
{
	if (!valid)
		return false;

	switch (sourceType)
	{
	case Type::STATIC:
	{
		// Looping mode could have changed.
		// FIXME: make looping mode change atomically so this is not needed
		alSourcei(source, AL_LOOPING, isLooping() ? AL_TRUE : AL_FALSE);
		return !isFinished();
	}
	case Type::STREAM:
		if (!isFinished())
		{
/*
			ALint processed;
			ALuint buffers[MAX_BUFFERS];
			ALint curOffsetSamples, newOffsetSamples;
			const auto freq = decoder->getSampleRate();

			alGetSourcei(source, AL_SAMPLE_OFFSET, &curOffsetSamples);
			const double curOffsetSecs = (double)curOffsetSamples / freq;

			alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
			alSourceUnqueueBuffers(source, processed, buffers);

			alGetSourcei(source, AL_SAMPLE_OFFSET, &newOffsetSamples);
			const double newOffsetSecs = (double)newOffsetSamples / freq;

			offsetSamples += curOffsetSamples - newOffsetSamples;
			offsetSeconds += curOffsetSecs - newOffsetSecs;

			for (int i = 0; i < processed; i++)
				unusedBuffers.push(buffers[i]);
*/
			ALint processed;
			alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

			// It would theoretically be better to unqueue all processed
			// buffers in a single call to alSourceUnqueueBuffers, but on
			// iOS I observed occasional (every ~5-10 seconds) pops in the
			// streaming source test I was using, when doing that. Perhaps
			// there was a bug in this code when I was testing, or maybe
			// this code runs into the same problem but now it's much harder
			// to reproduce. The test I used is the play-stop-play .love
			// from https://bitbucket.org/rude/love/issues/1484/
			while (processed--)
			{
				int curOffsetSamples;
				alGetSourcei(source, AL_SAMPLE_OFFSET, &curOffsetSamples);

				ALuint buffer;
				alSourceUnqueueBuffers(source, 1, &buffer);

				int newOffsetSamples;
				alGetSourcei(source, AL_SAMPLE_OFFSET, &newOffsetSamples);

				offsetSamples += (curOffsetSamples - newOffsetSamples);

				if (streamAtomic(buffer, decoder) > 0)
					alSourceQueueBuffers(source, 1, &buffer);
				else
					unusedBuffers.push(buffer);
			}

			while (!unusedBuffers.empty())
			{
				auto b = unusedBuffers.top();
				if (streamAtomic(b, decoder) > 0)
				{
					alSourceQueueBuffers(source, 1, &b);
					unusedBuffers.pop();
				}
				else
					break;
			}
			return true;
		}
		return false;
	case Type::QUEUE:
		return updateQueueAtomic();
	case Type::MAX_ENUM:
		break;
	}

	return false;
}

void AudioSource::setPitch(float value)
{
	value = std::max(0.5f, std::min(value, 2.0f));
	if (valid)
		alSourcef(source, AL_PITCH, value);
	pitch = value;
}

float AudioSource::getPitch() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_PITCH, &f);
		return f;
	}
	// In case the AudioSource isn't playing.
	return pitch;
}

void AudioSource::setVolume(float value)
{
	value = std::max(0.f, value);
	if (valid)
		alSourcef(source, AL_GAIN, value);
	volume = value;
}

float AudioSource::getVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_GAIN, &f);
		return f;
	}
	// In case the AudioSource isn't playing.
	return volume;
}

void AudioSource::seek(int64_t offset)
{
	auto l = pool->lock();
	auto offsetSamples = offset;
	//double offsetSeconds = (double)offset / sampleRate;
	const bool wasPlaying = isPlaying();
	switch (sourceType)
	{
	case Type::STATIC:
		if (valid)
		{
			alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
			offsetSamples = 0;
		}
		break;
	case Type::STREAM:
		{
			// To drain all buffers
			if (valid)
				releaseSource();

			decoder->seek(offsetSamples);

			if (wasPlaying)
			{
				//play();
				ALuint out;
				char wasPlaying_;
				if (!pool->assignSource(this, out, wasPlaying_))
					valid = false;
				else if (!wasPlaying_)
					valid = playAtomic(out);
				else
				{					
					resumeAtomic();
					valid = true;
				}
			}

			break;
		}
	case Type::QUEUE:
		if (valid)
		{
			alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
			offsetSamples = 0;
		}
		else
		{
			//emulate AL behavior, discarding buffer once playback head is past one
			while (!unusedBuffers.empty())
			{
				ALint size;
				const auto buffer = unusedBuffers.top();
				alGetBufferi(buffer, AL_SIZE, &size);

				const int bytesPerFrame = bitDepth / 8 * channels;
				if (offsetSamples < size / bytesPerFrame)
					break;

				unusedBuffers.pop();
				bufferedBytes -= size;
				offsetSamples -= size / bytesPerFrame;
			}
			if (unusedBuffers.empty())
				offsetSamples = 0;
			//offsetSeconds = (double)offsetSamples / sampleRate;
		}
		break;
	case Type::MAX_ENUM:
	default:
		break;
	}

	if (wasPlaying && (alGetError() == AL_INVALID_VALUE || sourceType == Type::STREAM && !isPlaying()))
	{
		releaseSource();
		if (isLooping())
		{
			//play();
			ALuint out;
			char wasPlaying_;
			if (!pool->assignSource(this, out, wasPlaying_))
				valid = false;
			else if (!wasPlaying_)
				valid = playAtomic(out);
			else
			{
				resumeAtomic();
				valid = true;
			}
		}
		return;
	}
	this->offsetSamples = offsetSamples;
}

int64_t AudioSource::tell()
{
	auto l = pool->lock();

	ALint offset = 0;
	if (valid)
		alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);
	offset += offsetSamples;
	return offset;
}

int64_t AudioSource::getTotalFrames()
{
	auto l = pool->lock();

	switch (sourceType)
	{
	case Type::STATIC:
	{
		const ALsizei size = staticBuffer->getSize();
		const ALsizei samples = size / channels / (bitDepth / 8);
		return (int64_t)samples;
	}
	case Type::STREAM:
	{
		return decoder->getTotalFrames();
	}
	case Type::QUEUE:
	{
		const ALsizei samples = bufferedBytes / channels / (bitDepth / 8);
		return (int64_t)samples;
	}
	case Type::MAX_ENUM:
	default:
		return 0;
	}
}

void AudioSource::setTime(double seconds)
{
	seek(seconds*sampleRate);
}

double AudioSource::getTime()
{
	return (double)tell() / sampleRate;
}

double AudioSource::getTotalTime()
{
	return (double)getTotalFrames() / sampleRate;
}

void AudioSource::setPosition(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_POSITION, (float*)&v);

	position = v;
}

cocos2d::Vec3 AudioSource::getPosition()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_POSITION, (float*)&v);
	return v;
}

void AudioSource::setVelocity(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_VELOCITY, (float*)&v);

	velocity = v;
}

cocos2d::Vec3 AudioSource::getVelocity()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_VELOCITY, (float*)&v);
	return v;
}

void AudioSource::setDirection(const cocos2d::Vec3& v)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcefv(source, AL_DIRECTION, (float*)&v);
	else
		direction = v;
}

cocos2d::Vec3 AudioSource::getDirection()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}

	auto v = position;
	if (valid)
		alGetSourcefv(source, AL_DIRECTION, (float*)&v);
	return v;
}

void AudioSource::setCone(float innerAngle, float outerAngle, float outerVolume, float outerHighGain)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	cone.innerAngle = (int)TODEG(innerAngle);
	cone.outerAngle = (int)TODEG(outerAngle);
	cone.outerVolume = outerVolume;
	cone.outerHighGain = outerHighGain;

	if (valid)
	{
		alSourcei(source, AL_CONE_INNER_ANGLE, cone.innerAngle);
		alSourcei(source, AL_CONE_OUTER_ANGLE, cone.outerAngle);
		alSourcef(source, AL_CONE_OUTER_GAIN, cone.outerVolume);
#ifdef ALC_EXT_EFX
		alSourcef(source, AL_CONE_OUTER_GAINHF, cone.outerHighGain);
#endif
	}
}

void AudioSource::setCone(const std::array<float, 4>& param)
{
	setCone(param[0], param[1], param[2], param[3]);
}

std::array<float, 4> AudioSource::getCone()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return {};
	}
	return {
		CC_DEGREES_TO_RADIANS(cone.innerAngle),
		CC_DEGREES_TO_RADIANS(cone.outerAngle),
		cone.outerVolume,
		cone.outerHighGain };
}

void AudioSource::setRelative(bool enable)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcei(source, AL_SOURCE_RELATIVE, enable ? AL_TRUE : AL_FALSE);

	relative = enable;
}

bool AudioSource::isRelative()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return false;
	}

	return relative;
}

void AudioSource::setLooping(bool enable)
{
	if (sourceType == Type::QUEUE)
	{
		QueueLoopingException();
		return;
	}

	if (valid && sourceType == Type::STATIC)
		alSourcei(source, AL_LOOPING, enable ? AL_TRUE : AL_FALSE);

	looping = enable;
}

bool AudioSource::isLooping() const
{
	return looping;
}

void AudioSource::setLoopingPoint(double tStart, double tEnd)
{
	if (sourceType == Type::STREAM)
		decoder->setLoopingPoint(tStart, tEnd);
}

bool AudioSource::isSupportLoopingPoint() const
{
	return sourceType == Type::STREAM;
}

double AudioSource::getLoopingStart() const
{
	if (sourceType == Type::STREAM)
		return decoder->getLoopingStart();
	return 0.0;
}

double AudioSource::getLoopingEnd() const
{
	if (sourceType == Type::STREAM)
		return decoder->getLoopingEnd();
	return 0.0;
}

bool AudioSource::queueData(void *data, size_t length, int dataSampleRate, int dataBitDepth, int dataChannels)
{
	if (sourceType != Type::QUEUE)
	{
		QueueTypeMismatchException();
		return false;
	}

	if (dataSampleRate != sampleRate || dataBitDepth != bitDepth || dataChannels != channels)
	{
		QueueFormatMismatchException();
		return false;
	}

	if (bitDepth <= 0 || channels <= 0 || length % (bitDepth / 8 * channels) != 0)
	{
		QueueMalformedLengthException(bitDepth / 8 * channels);
		return false;
	}

	const auto snapshot = getQueuePlaybackSnapshot();
	return submitQueueData(data, length, snapshot.generation, snapshot.deviceGeneration) == QueueSubmitResult::Accepted;
}

AudioSource::QueueSubmitResult AudioSource::submitQueueData(const void* data, size_t length,
	uint64_t expectedGeneration, int expectedDeviceGeneration)
{
	if (!pool)
		return QueueSubmitResult::OutputError;
	auto lock = pool->lock();
	if (!AudioEngine::isValid() || expectedDeviceGeneration != AudioEngine::getDeviceGeneration() ||
		bufferGeneration != expectedDeviceGeneration)
		return QueueSubmitResult::DeviceChanged;
	if (expectedGeneration != queueGeneration)
		return QueueSubmitResult::StaleGeneration;
	const size_t bytesPerFrame = size_t(bitDepth / 8) * channels;
	if (sourceType != Type::QUEUE || bytesPerFrame == 0 || length % bytesPerFrame ||
		(length && !data) || length > size_t(std::numeric_limits<ALsizei>::max()))
		return QueueSubmitResult::InvalidData;
	if (!length)
		return QueueSubmitResult::Accepted;
	if (queueError != AL_NO_ERROR)
		return QueueSubmitResult::OutputError;
	// Retire a naturally stopped assignment before attaching new payloads. A
	// stopped source marks new buffers processed too; it must not consume them.
	if (valid && !updateQueueAtomic())
		pool->releaseSource(this);
	if (queueError != AL_NO_ERROR)
		return QueueSubmitResult::OutputError;
	if (unusedBuffers.empty())
		return QueueSubmitResult::Full;
	const uint64_t frames = length / bytesPerFrame;
	if (frames > std::numeric_limits<uint64_t>::max() - queueSubmittedFrames ||
		length > uint64_t(std::numeric_limits<int64_t>::max() - bufferedBytes))
		return QueueSubmitResult::InvalidData;
	const ALuint buffer = unusedBuffers.top();
	alGetError();
	alBufferData(buffer, AudioEngine::getFormat(bitDepth, channels), data, ALsizei(length), sampleRate);
	ALenum error = alGetError();
	if (error == AL_NO_ERROR && valid)
	{
		alSourceQueueBuffers(source, 1, &buffer);
		error = alGetError();
	}
	if (error != AL_NO_ERROR)
	{
		queueError = error;
		queueStopReason = QueueStopReason::OutputError;
		lastError = "QUEUE PCM upload/submit failed";
		return QueueSubmitResult::OutputError;
	}
	unusedBuffers.pop();
	if (!valid)
		streamBuffers.push(buffer);
	queueBufferFrames[buffer] = frames;
	queueSubmittedFrames += frames;
	bufferedBytes += int64_t(length);
	queueStopReason = QueueStopReason::None;
	return QueueSubmitResult::Accepted;
}

AudioSource::QueuePlaybackSnapshot AudioSource::queueSnapshotAtomic()
{
	QueuePlaybackSnapshot result;
	result.generation = queueGeneration;
	result.deviceGeneration = AudioEngine::getDeviceGeneration();
	result.outputRevision = AudioEngine::getOutputRevision();
	result.suspended = AudioEngine::isSuspended();
	result.submittedFrames = queueSubmittedFrames;
	result.reclaimedFrames = queueReclaimedFrames;
	result.naturalEndFrames = queueNaturalEndFrames;
	result.stopReason = queueStopReason;
	result.sampledSeconds = queueSteadySeconds();
	result.error = queueError;
	for (const auto& buffer : queueBufferFrames)
		result.residentFrames += buffer.second;
	if (!AudioEngine::isValid() || bufferGeneration != result.deviceGeneration)
	{
		result.stopReason = QueueStopReason::DeviceChanged;
		return result;
	}
	if (result.error != AL_NO_ERROR)
		return result;
	if (!valid)
	{
		result.clockValid = queueError == AL_NO_ERROR;
		result.state = queueStarted ? AL_STOPPED : AL_INITIAL;
		return result;
	}
	if (latencyGeneration != result.deviceGeneration)
	{
		latencyGeneration = result.deviceGeneration;
		latencyFailed = false;
#ifdef AL_SOFT_source_latency
		queueGetSourcei64v = nullptr;
		if (alIsExtensionPresent("AL_SOFT_source_latency") == AL_TRUE)
			queueGetSourcei64v = reinterpret_cast<LPALGETSOURCEI64VSOFT>(alGetProcAddress("alGetSourcei64vSOFT"));
		if (!queueGetSourcei64v)
			AINFO("QUEUE output uses uncalibrated core sample offsets (source latency unavailable)");
#endif
	}
	alGetError();
#ifdef AL_SOFT_source_latency
	if (queueGetSourcei64v && !latencyFailed)
	{
		ALint64SOFT values[2] = {};
		queueGetSourcei64v(source, AL_SAMPLE_OFFSET_LATENCY_SOFT, values);
		const ALenum error = alGetError();
		if (error == AL_NO_ERROR && values[0] >= 0 && values[1] >= 0 &&
			double(values[0]) / 4294967296.0 <= double(queueSubmittedFrames - queueReclaimedFrames))
		{
			result.queueOffsetFrames = double(values[0]) / 4294967296.0;
			result.outputLatencySeconds = double(values[1]) * 1e-9;
			result.latencyValid = true;
		}
		else
		{
			latencyFailed = true;
			AWARN("QUEUE source latency query failed; using core sample offsets for this device generation");
		}
	}
#endif
	if (!result.latencyValid)
	{
		ALint offset = 0;
		alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);
		result.error = alGetError();
		result.queueOffsetFrames = double(offset);
	}
	// State is queried after the offset/latency pair, while no reclaim can
	// change the matching cumulative count under this same pool lock.
	alGetSourcei(source, AL_SOURCE_STATE, &result.state);
	const ALenum stateError = alGetError();
	if (result.error == AL_NO_ERROR)
		result.error = stateError;
	result.sampledSeconds = queueSteadySeconds();
	if (result.state == AL_STOPPED && queueStarted && result.error == AL_NO_ERROR)
	{
		queueNaturalEndFrames = queueSubmittedFrames;
		queueStopReason = QueueStopReason::Natural;
		result.naturalEndFrames = queueNaturalEndFrames;
		result.stopReason = queueStopReason;
		// OpenAL resets the sample offset at STOPPED; use the known endpoint.
		result.queueOffsetFrames = double(queueSubmittedFrames - queueReclaimedFrames);
		result.latencyValid = false;
	}
	result.clockValid = result.error == AL_NO_ERROR &&
		std::isfinite(result.queueOffsetFrames) && result.queueOffsetFrames >= 0.0 &&
		result.queueOffsetFrames <= double(queueSubmittedFrames - queueReclaimedFrames);
	return result;
}

AudioSource::QueuePlaybackSnapshot AudioSource::getQueuePlaybackSnapshot()
{
	if (!pool)
		return {};
	auto lock = pool->lock();
	return queueSnapshotAtomic();
}

bool AudioSource::updateQueueAtomic()
{
	const auto snapshot = queueSnapshotAtomic();
	if (!snapshot.clockValid)
		return true; // The session applies the bounded output-query failure policy.
	ALint processed = 0;
	alGetError();
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
	const ALenum processedError = alGetError();
	if (processedError != AL_NO_ERROR || processed < 0 || processed > MAX_BUFFERS)
	{
		queueError = processedError != AL_NO_ERROR ? processedError : AL_INVALID_VALUE;
		queueStopReason = QueueStopReason::OutputError;
		return true;
	}
	while (processed-- > 0)
	{
		ALuint buffer = 0;
		alSourceUnqueueBuffers(source, 1, &buffer);
		const ALenum error = alGetError();
		if (error != AL_NO_ERROR)
		{
			queueError = error;
			queueStopReason = QueueStopReason::OutputError;
			return true;
		}
		const auto found = queueBufferFrames.find(buffer);
		if (found == queueBufferFrames.end())
		{
			queueError = AL_INVALID_NAME;
			queueStopReason = QueueStopReason::OutputError;
			return true;
		}
		queueReclaimedFrames += found->second;
		bufferedBytes -= int64_t(found->second * size_t(bitDepth / 8) * channels);
		queueBufferFrames.erase(found);
		unusedBuffers.push(buffer);
	}
	return snapshot.state != AL_STOPPED;
}

void AudioSource::clearQueueAtomic(QueueStopReason reason)
{
	queueStopReason = reason;
	if (bufferGeneration == AudioEngine::getDeviceGeneration())
	{
		if (valid)
			pool->releaseSource(this);
		while (!streamBuffers.empty())
		{
			unusedBuffers.push(streamBuffers.front());
			streamBuffers.pop();
		}
	}
	else
	{
		valid = false;
		source = 0;
		while (!streamBuffers.empty()) streamBuffers.pop();
		while (!unusedBuffers.empty()) unusedBuffers.pop();
		if (AudioEngine::isValid())
			regenerateBuffers();
	}
	queueBufferFrames.clear();
	bufferedBytes = 0;
	queueSubmittedFrames = queueReclaimedFrames = queueNaturalEndFrames = 0;
	queueStarted = false;
	queueError = AL_NO_ERROR;
	++queueGeneration;
}

uint64_t AudioSource::resetQueue()
{
	if (!pool)
		return 0;
	auto lock = pool->lock();
	clearQueueAtomic(QueueStopReason::Explicit);
	return queueGeneration;
}

void AudioSource::setSessionControlled(bool controlled)
{
	if (!pool)
		return;
	auto lock = pool->lock();
	sessionControlled = controlled;
}

void AudioSource::setQueuePlaybackAllowed(bool allowed)
{
	if (!pool)
		return;
	auto lock = pool->lock();
	queuePlaybackAllowed = allowed;
	if (!allowed && bufferGeneration == AudioEngine::getDeviceGeneration())
		pauseAtomic();
}

void AudioSource::setQueueGain(float gain)
{
	if (!pool)
		return;
	auto lock = pool->lock();
	volume = gain;
	if (valid && bufferGeneration == AudioEngine::getDeviceGeneration())
		alSourcef(source, AL_GAIN, gain);
}

bool AudioSource::queue(AudioSoundData* data, ssize_t offset, ssize_t length)
{
	if (offset < 0)
		offset = 0;
	const auto r = (ssize_t)data->getSize() - offset;
	if (length < 0 || length > r)
		length = r;
	return queueData((unsigned char*)data->getData() + offset, length,
		data->getSampleRate(), data->getBitDepth(), data->getChannelCount());
}

int AudioSource::getFreeBufferCount() const
{
	if (!pool)
		return 0;
	auto lock = pool->lock();
	switch (sourceType) //why not :^)
	{
	case Type::STATIC:
		return 0;
	case Type::STREAM:
		return unusedBuffers.size();
	case Type::QUEUE:
		return unusedBuffers.size();
	case Type::MAX_ENUM:
		return 0;
	}
	return 0;
}

void AudioSource::prepareAtomic()
{
	// This AudioSource may now be associated with an OpenAL source that still has
	// the properties of another love AudioSource. Let's reset it to the settings
	// of the new one.
	reset();

	// If the OpenAL context was recreated (device recovery after an unplug),
	// every AL id we hold is stale - regenerate before use.
	if (bufferGeneration != AudioEngine::getDeviceGeneration())
		regenerateBuffers();

	switch (sourceType)
	{
	case Type::STATIC:
		alSourcei(source, AL_BUFFER, staticBuffer->getBuffer());
		break;
	case Type::STREAM:
		while (!unusedBuffers.empty())
		{
			auto b = unusedBuffers.top();
			if (streamAtomic(b, decoder) == 0)
				break;

			alSourceQueueBuffers(source, 1, &b);
			unusedBuffers.pop();

			if (decoder->isFinished())
				break;
		}
		break;
	case Type::QUEUE:
	{
		while (!streamBuffers.empty())
		{
			alGetError();
			alSourceQueueBuffers(source, 1, &streamBuffers.front());
			const ALenum error = alGetError();
			if (error != AL_NO_ERROR)
			{
				queueError = error;
				break;
			}
			streamBuffers.pop();
		}
		break;
	}
	case Type::MAX_ENUM:
		break;
	}
	// Seek to the current/pending offset.
	alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
	if (sourceType == Type::QUEUE && queueError == AL_NO_ERROR)
		queueError = alGetError();
}

void AudioSource::regenerateBuffers()
{
	// The context this AudioSource's buffers were created in is gone; all ALuints
	// are stale and are NOT deleted here (they belong to the destroyed
	// context, ids may collide with freshly created objects).
	switch (sourceType)
	{
	case Type::STATIC:
		// Re-upload from the retained PCM copy (AudioStaticDataBuffer::reload).
		if (staticBuffer)
			staticBuffer->reload();
		break;

	case Type::STREAM:
	{
		// Fresh ids; the AudioDecoder is not an AL object - it survived the
		// context swap and still sits at the frame it decoded up to, so the
		// stream continues where it was.
		while (!unusedBuffers.empty())
			unusedBuffers.pop();
		while (!streamBuffers.empty())
			streamBuffers.pop();
		for (int i = 0; i < buffers; i++)
		{
			ALuint buf;
			alGenBuffers(1, &buf);
			if (alGetError() == AL_NO_ERROR)
				unusedBuffers.push(buf);
			else
				break;
		}
		break;
	}

	case Type::QUEUE:
	{
		// Queued payloads are not retained: only fresh ids are provided so
		// the application can queueData()/queue() on this AudioSource again.
		while (!unusedBuffers.empty())
			unusedBuffers.pop();
		while (!streamBuffers.empty())
			streamBuffers.pop();
		for (int i = 0; i < buffers; i++)
		{
			ALuint buf;
			alGenBuffers(1, &buf);
			if (alGetError() == AL_NO_ERROR)
				unusedBuffers.push(buf);
			else
				break;
		}
		queueBufferFrames.clear();
		bufferedBytes = 0;
		queueSubmittedFrames = queueReclaimedFrames = queueNaturalEndFrames = 0;
		queueStarted = false;
		queueStopReason = QueueStopReason::DeviceChanged;
		++queueGeneration;
		break;
	}

	case Type::MAX_ENUM:
		break;
	}

	bufferGeneration = AudioEngine::getDeviceGeneration();
}

void AudioSource::teardownAtomic()
{
	switch (sourceType)
	{
	case Type::STATIC:
		break;
	case Type::STREAM:
	{
/*
		ALint queued;
		ALuint buffer;
		decoder->seek(0);
		// drain buffers
		//since we only unqueue 1 buffer, it's OK to use singular variable pointer instead of array
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		for (unsigned int i = 0; i < (unsigned int)queued; i++)
		{
			alSourceUnqueueBuffers(source, 1, &buffer);
			unusedBuffers.push(buffer);
		}
*/
		ALint queued = 0;
		ALuint buffers[MAX_BUFFERS];
		decoder->seek(0);
		// Drain buffers.
		// NOTE: The Apple implementation of OpenAL on iOS doesn't return
		// correct buffer ids for single alSourceUnqueueBuffers calls past the
		// first queued buffer, so we must unqueue them all at once.
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alSourceUnqueueBuffers(source, queued, buffers);
		for (int i = 0; i < queued; i++)
			unusedBuffers.push(buffers[i]);
		break;
	}
	case Type::QUEUE:
	{
/*
		ALint queued;
		ALuint buffer;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		for (auto i = queued; i > 0; i--)
		{
			alSourceUnqueueBuffers(source, 1, &buffer);
			unusedBuffers.push(buffer);
		}
*/
		ALint queued;
		ALuint buffers[MAX_BUFFERS];
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alSourceUnqueueBuffers(source, queued, buffers);
		for (int i = 0; i < queued; i++)
			unusedBuffers.push(buffers[i]);
		break;
	}
	case Type::MAX_ENUM:
		break;
	}

	alSourcei(source, AL_BUFFER, AL_NONE);

	toLoop = 0;
	valid = false;
	offsetSamples = 0;
}

bool AudioSource::playAtomic(ALuint source)
{
	this->source = source;
	prepareAtomic();
	if (sourceType == Type::QUEUE && queueError != AL_NO_ERROR)
	{
		valid = true; // ensure the failed assignment is detached and returned
		releaseSource();
		return false;
	}

	// Clear errors.
	alGetError();

	alSourcePlay(source);

	bool success = alGetError() == AL_NO_ERROR;

	if (sourceType == Type::STREAM)
	{
		valid = true; //isPlaying() needs source to be valid
		if (!isPlaying())
			success = false;
	}
	//else if (success)
	//{
	//	alSourcei(source, AL_SAMPLE_OFFSET, offsetSamples);
	//	success = alGetError() == AL_NO_ERROR;
	//}

	if (!success)
	{
		if (sourceType == Type::QUEUE)
		{
			queueError = AL_INVALID_OPERATION;
			valid = true;
		}
		//valid = true; //stop() needs source to be valid
		releaseSource();
	}
	// Static sources: reset the pending offset since it's not valid anymore.
	if (sourceType != Type::STREAM)
		offsetSamples = 0;
	if (success && sourceType == Type::QUEUE)
	{
		queueStarted = true;
		queueStopReason = QueueStopReason::None;
	}

	return success;
}

void AudioSource::stopAtomic()
{
	if (!valid)
		return;
	if (sourceType == Type::QUEUE && queueStopReason != QueueStopReason::Natural)
		queueStopReason = queueError == AL_NO_ERROR ? QueueStopReason::Explicit : QueueStopReason::OutputError;
	alSourceStop(source);
	teardownAtomic();
}

void AudioSource::pauseAtomic()
{
	if (valid)
		alSourcePause(source);
}

void AudioSource::resumeAtomic()
{
	if (valid && !isPlaying())
	{
		alSourcePlay(source);

		//failed to play or nothing to play
		if (alGetError() == AL_INVALID_VALUE || sourceType == Type::STREAM && (int)unusedBuffers.size() == buffers)
			releaseSource();
	}
}

size_t AudioSource::copyBuffer(char* dst, size_t size, size_t offset)
{
	auto l = pool->lock();
	switch (sourceType)
	{
	case Type::STATIC: //TODO:
		break;
	case Type::STREAM:
	{			
		const auto bufferSize = (size_t)decoder->getBufferSize();
		// note: avoid bufferSize - offset underflow
		offset = std::min(offset, bufferSize);
		size = std::min(size, bufferSize - offset);
		if (size <= 0)return 0;
		memcpy(dst, decoder->getBuffer() + offset, size);
		return size;
	}
	case Type::QUEUE:
		break;
	case Type::MAX_ENUM:
		break;
	}
	return 0;
}

int64_t AudioSource::getBufferOffset()
{
	auto l = pool->lock();
	switch (sourceType)
	{
	case Type::STATIC: //TODO:
		break;
	case Type::STREAM:
	{
		return decoder->getBufferOffset();
	}
	case Type::QUEUE:
		break;
	case Type::MAX_ENUM:
		break;
	}
	return 0;
}

bool AudioSource::playBatch(const std::vector<AudioSource*> &sources)
{
	if (sources.empty())
		return true;
	if (!AudioEngine::isValid())
		return false;
	auto pool = AudioPool::getInstance();
	if (!pool)
		return false;
	auto l = pool->lock();
	return playBatchAtomic(pool, sources);
}

bool AudioSource::playBatchAtomic(AudioPool* pool, const std::vector<AudioSource*>& sources)
{
	if (sources.empty())
		return true;
	if (!AudioEngine::isValid())
		return false;
	for (const auto* source : sources)
		if (source->sourceType == Type::QUEUE && source->sessionControlled &&
			(!source->queuePlaybackAllowed || AudioEngine::isSuspended() ||
			 source->bufferGeneration != AudioEngine::getDeviceGeneration()))
			return false;

	// NOTE: not bool, because std::vector<bool> is implemented as a bitvector
	// which means no bool references can be created.
	std::vector<char> wasPlaying(sources.size());
	std::vector<ALuint> ids(sources.size());

	for (size_t i = 0; i < sources.size(); i++)
	{
		if (!pool->assignSource(sources[i], ids[i], wasPlaying[i]))
		{
			for (size_t j = 0; j < i; j++)
				if (!wasPlaying[j])
					sources[j]->releaseSource(false);
			return false;
		}
	}

	std::vector<ALuint> toPlay;
	toPlay.reserve(sources.size());
	for (size_t i = 0; i < sources.size(); i++)
	{
		// If the source was paused, wasPlaying[i] will be true but we still
		// want to resume it. We don't want to call alSourcePlay on sources
		// that are actually playing though.
		if (wasPlaying[i] && sources[i]->isPlaying())
			continue;

		if (!wasPlaying[i])
		{
			auto source = sources[i];
			source->source = ids[i];
			source->prepareAtomic();
		}

		toPlay.push_back(ids[i]);
	}

	alGetError();
	alSourcePlayv((ALsizei)toPlay.size(), toPlay.data());
	const bool success = alGetError() == AL_NO_ERROR;

	for (auto& source : sources)
	{
		source->valid = source->valid || success;
		if (success && source->sourceType != Type::STREAM)
			source->offsetSamples = 0;
		if (success && source->sourceType == Type::QUEUE)
		{
			source->queueStarted = true;
			source->queueStopReason = QueueStopReason::None;
		}
	}

	return success;
}

void AudioSource::stopBatch(const std::vector<AudioSource*> &sources)
{
	if (sources.empty())
		return;
	auto pool = AudioPool::getInstance();
	if (!pool)
		return;
	auto l = pool->lock();
	stopBatchAtomic(sources);
}

void AudioSource::stopBatchAtomic(const std::vector<AudioSource*>& sources)
{
	std::vector<ALuint> sourceIds;
	sourceIds.reserve(sources.size());
	for (auto& source : sources)
	{
		if (source->sourceType == Type::QUEUE)
		{
			source->clearQueueAtomic(QueueStopReason::Explicit);
			continue;
		}
		if (source->valid)
			sourceIds.push_back(source->source);
	}

	alSourceStopv((ALsizei)sourceIds.size(), sourceIds.data());

	for (auto& source : sources)
	{
		if (source->valid)
			source->teardownAtomic();
		source->releaseSource(false);
	}
}

void AudioSource::pauseBatch(const std::vector<AudioSource*> &sources)
{
	if (sources.empty())
		return;
	auto pool = AudioPool::getInstance();
	if (!pool)
		return;
	auto l = pool->lock();

	std::vector<ALuint> sourceIds;
	sourceIds.reserve(sources.size());
	for (auto& source : sources)
	{
		if (source->valid)
			sourceIds.push_back(source->source);
	}

	alSourcePausev((ALsizei)sourceIds.size(), sourceIds.data());
}

std::vector<AudioSource*> AudioSource::pauseAll()
{
	auto pool = AudioPool::getInstance();
	if (!pool)
		return {};
	auto lock = pool->lock();
	auto sources = pool->getPlayingSources();

	const auto newend = std::remove_if(sources.begin(), sources.end(), [](AudioSource* s) {
		return !s->isPlaying();
	});
	sources.erase(newend, sources.end());

	std::vector<ALuint> ids;
	ids.reserve(sources.size());
	for (auto* source : sources)
		ids.push_back(source->source);
	alSourcePausev(ALsizei(ids.size()), ids.data());
	// Private worker-owned sources can disappear immediately after releasing
	// the pool lock. Pause them, but never expose their borrowed pointers for
	// an unrelated caller to retain or resume outside the session gate.
	sources.erase(std::remove_if(sources.begin(), sources.end(), [](AudioSource* source) {
		return source->sessionControlled;
	}), sources.end());
	return sources;
}

void AudioSource::stopAll()
{
	auto pool = AudioPool::getInstance();
	if (!pool)
		return;
	auto lock = pool->lock();
	stopBatchAtomic(pool->getPlayingSources());
}

bool AudioSource::releaseSource(bool stop)
{
	return pool->releaseSource(this, stop);
}

void AudioSource::reset()
{
	alSourcei(source, AL_BUFFER, AL_NONE);
	alSourcefv(source, AL_POSITION, (float*)&position);
	alSourcefv(source, AL_VELOCITY, (float*)&velocity);
	alSourcefv(source, AL_DIRECTION, (float*)&direction);
	alSourcef(source, AL_PITCH, pitch);
	alSourcef(source, AL_GAIN, volume);
	alSourcef(source, AL_MIN_GAIN, minVolume);
	alSourcef(source, AL_MAX_GAIN, maxVolume);
	alSourcef(source, AL_REFERENCE_DISTANCE, referenceDistance);
	alSourcef(source, AL_ROLLOFF_FACTOR, rolloffFactor);
	alSourcef(source, AL_MAX_DISTANCE, maxDistance);
	alSourcei(source, AL_LOOPING, sourceType == Type::STATIC && isLooping() ? AL_TRUE : AL_FALSE);
	alSourcei(source, AL_SOURCE_RELATIVE, relative ? AL_TRUE : AL_FALSE);
	alSourcei(source, AL_CONE_INNER_ANGLE, cone.innerAngle);
	alSourcei(source, AL_CONE_OUTER_ANGLE, cone.outerAngle);
	alSourcef(source, AL_CONE_OUTER_GAIN, cone.outerVolume);
#ifdef ALC_EXT_EFX
	alSourcef(source, AL_AIR_ABSORPTION_FACTOR, absorptionFactor);
	alSourcef(source, AL_CONE_OUTER_GAINHF, cone.outerHighGain);
	alSourcef(source, AL_ROOM_ROLLOFF_FACTOR, rolloffFactor); //reverb-specific rolloff
	alSourcei(source, AL_DIRECT_FILTER, directfilter ? directfilter->getFilter() : AL_FILTER_NULL);
	// clear all send slots, then re-enable applied ones
	for (int i = 0; i < AudioEngine::getMaxSourceEffectCount(); i++)
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, i, AL_FILTER_NULL);
	for (auto& i : effectmap)
		alSource3i(source, AL_AUXILIARY_SEND_FILTER,
			i.second.target,
			i.second.slot,
			i.second.filter ? i.second.filter->getFilter() : AL_FILTER_NULL);
	//alGetError();
#endif
}

int AudioSource::streamAtomic(ALuint buffer, AudioDecoder* d)
{
	if (!d) return 0;
	// Get more sound data.
	auto decoded = (ALsizei)std::max<int64_t>(d->decode(), 0);

	// OpenAL implementations are allowed to ignore 0-size alBufferData calls.
	if (decoded > 0)
	{
		const auto fmt = AudioEngine::getFormat((int)d->getBitDepth(), (int)d->getChannelCount());

		if (fmt != AL_NONE)
			alBufferData(buffer, fmt, d->getBuffer(), decoded, (ALsizei)d->getSampleRate());
		else
			decoded = 0;
	}

	if (decoder->isFinished() && isLooping())
	{
		ALint queued, processed;
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (queued > processed)
			toLoop = queued - processed;
		else
			toLoop = buffers - processed;
		d->rewind();
	}

	if (toLoop > 0)
	{
		if (--toLoop == 0)
		{
			//offsetSamples = 0;
			offsetSamples = d->tell();
		}
	}

	return decoded;
}

void AudioSource::setMinVolume(float v)
{
	v = std::max(0.f, v);
	if (valid)
		alSourcef(source, AL_MIN_GAIN, v);
	minVolume = v;
}

float AudioSource::getMinVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MIN_GAIN, &f);
		return f;
	}
	// In case the AudioSource isn't playing.
	return this->minVolume;
}

void AudioSource::setMaxVolume(float v)
{
	v = std::max(0.f, v);
	if (valid)
		alSourcef(source, AL_MAX_GAIN, v);
	maxVolume = v;
}

float AudioSource::getMaxVolume() const
{
	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MAX_GAIN, &f);
		return f;
	}
	// In case the AudioSource isn't playing.
	return maxVolume;
}

void AudioSource::setRolloffFactor(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcef(source, AL_ROLLOFF_FACTOR, value);

	rolloffFactor = value;
}

float AudioSource::getRolloffFactor()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_ROLLOFF_FACTOR, &f);
		return f;
	}

	// In case the AudioSource isn't playing.
	return rolloffFactor;
}

void AudioSource::setReferenceDistance(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	if (valid)
		alSourcef(source, AL_REFERENCE_DISTANCE, value);

	referenceDistance = value;
}

float AudioSource::getReferenceDistance()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_REFERENCE_DISTANCE, &f);
		return f;
	}

	// In case the AudioSource isn't playing.
	return referenceDistance;
}

void AudioSource::setMaxDistance(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	value = std::min(value, MAX_ATTENUATION_DISTANCE);

	if (valid)
		alSourcef(source, AL_MAX_DISTANCE, value);

	maxDistance = value;
}

float AudioSource::getMaxDistance()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	if (valid)
	{
		ALfloat f;
		alGetSourcef(source, AL_MAX_DISTANCE, &f);
		return f;
	}

	// In case the AudioSource isn't playing.
	return maxDistance;
}

void AudioSource::setAirAbsorptionFactor(float value)
{
	if (channels > 1)
	{
		SpatialSupportException();
		return;
	}

	absorptionFactor = value;
#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSourcef(source, AL_AIR_ABSORPTION_FACTOR, absorptionFactor);
		//alGetError();
	}
#endif
}

float AudioSource::getAirAbsorptionFactor()
{
	if (channels > 1)
	{
		SpatialSupportException();
		return 0;
	}

	return absorptionFactor;
}

int AudioSource::getChannelCount() const
{
	return channels;
}

int AudioSource::getSampleRate() const
{
	return sampleRate;
}

int AudioSource::getBitDepth() const
{
	return bitDepth;
}

int AudioSource::getBytesPerFrame() const
{
	return channels * bitDepth / 8;
}

bool AudioSource::setFilter(const AudioFilter::ParamMap& params)
{
	if (!directfilter)
		directfilter = new AudioFilter();

	bool result = directfilter->setParams(params);

#ifdef ALC_EXT_EFX
	if (valid)
	{
		//in case of failure contains AL_FILTER_NULL, a valid non-filter
		alSourcei(source, AL_DIRECT_FILTER, directfilter->getFilter());
		//alGetError();
	}
#endif

	return result;
}

bool AudioSource::removeFilter()
{
	delete directfilter;
	directfilter = nullptr;

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSourcei(source, AL_DIRECT_FILTER, AL_FILTER_NULL);
		//alGetError();
	}
#endif

	return true;
}

AudioFilter::ParamMap AudioSource::getFilter()
{
	if (!directfilter)
		return {};
	AudioFilter::ParamMap params = directfilter->getParams();
	return params;
}

bool AudioSource::setEffect(const std::string& name)
{
	ALuint slot, target;
	AudioFilter *filter;

	// effect with this name doesn't exist
	if (!AudioEngine::getEffectID(name, target))
		return false;

	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		// new send target needed but no more room
		if (slotlist.empty())
			return false;

		slot = slotlist.top();
		slotlist.pop();
	}
	else
	{
		slot = iter->second.slot;
		filter = iter->second.filter;
		delete filter;
	}
	effectmap[name] = { nullptr, slot, target };

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, target, slot, AL_FILTER_NULL);
		//alGetError();
	}
#endif

	return true;
}

bool AudioSource::setEffect(const std::string& name, const AudioFilter::ParamMap& filterParams)
{
	ALuint slot, target;
	AudioFilter *filter = nullptr;

	// effect with this name doesn't exist
	if (!AudioEngine::getEffectID(name, target))
		return false;

	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		// new send target needed but no more room
		if (slotlist.empty())
			return false;

		slot = slotlist.top();
		slotlist.pop();
	}
	else
	{
		slot = iter->second.slot;
		filter = iter->second.filter;
	}
	if (!filter)
		filter = new AudioFilter();

	effectmap[name] = { filter, slot, target };

	filter->setParams(filterParams);

#ifdef ALC_EXT_EFX
	if (valid)
	{
		//in case of failure contains AL_FILTER_NULL, a valid non-filter
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, target, slot, filter->getFilter());
		//alGetError();
	}
#endif
	return true;
}

bool AudioSource::removeEffect(const std::string& name)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	const ALuint slot = iter->second.slot;
	AudioFilter *filter = iter->second.filter;

	delete filter;

#ifdef ALC_EXT_EFX
	if (valid)
	{
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, slot, AL_FILTER_NULL);
		//alGetError();
	}
#endif
	effectmap.erase(iter);
	slotlist.push(slot);
	return true;
}

AudioFilter::ParamMap AudioSource::getEffect(const std::string& name)
{
	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return {};
	AudioFilter::ParamMap params;
	if (iter->second.filter)
		params = iter->second.filter->getParams();
	return params;
}

std::vector<std::string> AudioSource::getActiveEffects() const
{
	if (effectmap.empty())
		return {};
	std::vector<std::string> list;
	list.reserve(effectmap.size());
	for (auto& i : effectmap)
		list.push_back(i.first);
	return list;
}

void AudioSource::InvalidFormatException(int channelCount, int bitDepth)
{
	lastError = string_format("invalid format: channelCount=%d, bitDepth=%d" , channelCount, bitDepth);
}

void AudioSource::SpatialSupportException()
{
	lastError = "invalid spatial operation on this source";
}

void AudioSource::QueueLoopingException()
{
	lastError = "this source dose not support looping";
}

void AudioSource::QueueTypeMismatchException()
{
	lastError = "this source dose not support queue";
}

void AudioSource::QueueFormatMismatchException()
{
	lastError = "queue format mismatch";
}

void AudioSource::QueueMalformedLengthException(int bytesPerSample)
{
	lastError = string_format("invalid queue buffer length, should be multiple of %d", bytesPerSample);
}

NS_CC_END
