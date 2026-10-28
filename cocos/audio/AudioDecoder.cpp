#include "AudioDecoder.h"
#include "AudioStream.h"
#include "AudioDecoderWav.h"
#ifdef AUDIO_USE_LIBVORBIS
#include "AudioDecoderVorbis.h"
#endif
#include "AudioDecoderVorbisStb.h"
#include "AudioDecoderFlac.h"
#include "AudioDecoderMp3.h"
#include "AudioCommon.h"
#include "platform/CCFileUtils.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>

NS_CC_BEGIN
using namespace AudioInternal;

static std::unordered_map<std::string, AudioDecoder::DecoderType> DecoderTypeMap = {
	{"wav", AudioDecoder::DecoderType::WAV},
	{"ogg", AudioDecoder::DecoderType::VORBIS},
	{"flac", AudioDecoder::DecoderType::FLAC},
	{"mp3", AudioDecoder::DecoderType::MP3},
};

std::string AudioDecoder::AudioInfo::toString()
{
	return string_format("Frame: %d, Freq: %d, Time: %.3f, Channel: %d, BitDepth: %d",
		(int)totalFrames, (int)sampleRate, (float)getTotalTime(),
		(int)channelCount, (int)getBitDepth());
}

AudioDecoder::AudioDecoder(size_t bufferSize, DecoderType type)
	: decoderType(type)
	, bufferSize(bufferSize)
{
	buffer.resize(bufferSize);
}

AudioDecoder::~AudioDecoder()
{
}

AudioDecoder::DecoderType AudioDecoder::getDecoderTypeFromPath(const std::string& path)
{
	// get ext in lower case
	auto ext = cocos2d::FileUtils::getInstance()->getFileExtension(path);
	// remove dot
	if (!ext.empty())
		ext = ext.substr(1);
	const auto it = DecoderTypeMap.find(ext);
	if (it != DecoderTypeMap.end())
		return it->second;
	return AudioDecoder::DecoderType::UNKNOWN;
}

AudioDecoder* AudioDecoder::createFromStream(AudioStream* s, size_t bufferSize, DecoderType type)
{
	if (!s)
		return nullptr;
	switch (type)
	{
	case AudioDecoder::DecoderType::WAV:
		return AudioDecoderWav::create(s, bufferSize);
	case AudioDecoder::DecoderType::VORBIS:
#ifdef AUDIO_USE_LIBVORBIS
		return AudioDecoderVorbis::create(s, bufferSize);
#else
		return AudioDecoderVorbisStb::create(s, bufferSize);
#endif
	case AudioDecoder::DecoderType::FLAC:
		return AudioDecoderFlac::create(s, bufferSize);
	case AudioDecoder::DecoderType::MP3:
		return AudioDecoderMp3::create(s, bufferSize);
	case AudioDecoder::DecoderType::UNKNOWN:
	default:;
	}
	return nullptr;
}

AudioDecoder* AudioDecoder::createFromFile(const std::string& path, size_t bufferSize, DecoderType type)
{
	if (type == DecoderType::UNKNOWN)
		type = getDecoderTypeFromPath(path);
	return createFromStream(AudioStream::createFromFile(path), bufferSize, type);
}

AudioDecoder* AudioDecoder::createFromLocalFile(const std::string& path, size_t bufferSize, DecoderType type)
{
	if (type == DecoderType::UNKNOWN)
		type = getDecoderTypeFromPath(path);
	return createFromStream(AudioStream::createFromLocalFile(path), bufferSize, type);
}

const uint8_t* AudioDecoder::getBuffer() const
{
	return buffer.data();
}

bool AudioDecoder::seekTime(double seconds)
{
	return seek(seconds * getSampleRate());
}

AudioDecoder* AudioDecoder::clone()
{
	//BUG: current implementation dose not support play from the same stream
	return createFromStream(stream, bufferSize, decoderType);
}

int64_t AudioDecoder::decode()
{
	int64_t toReadSize = bufferSize;
	const int64_t tCurSample = tell();
	const int64_t tSampleToRead = bufferSize / getBytesPerFrame();
	const int64_t exceed = tCurSample + tSampleToRead - getLoopEnd();
	if (exceed > 0)
		toReadSize -= exceed * getBytesPerFrame();
	toReadSize = std::max<int64_t>(toReadSize, 0);
	const int64_t size = decode((char*)buffer.data(), toReadSize);
	if (size > 0)
		bufferPosition = tCurSample;
	if (exceed > 0 && size == toReadSize)
		eof = true;
	return size;
}

int AudioDecoder::getBufferSize() const
{
	return bufferSize;
}

void AudioDecoder::setLoopingPoint(double tStart, double tEnd)
{
	if (tStart >= 0.0 && tEnd > 0.0 && tStart < tEnd)
	{
		const auto sampleRate = getSampleRate();
		const auto totalFrames = getTotalFrames();
		const auto start = std::min(int64_t(sampleRate * tStart), totalFrames);
		const auto end = std::min(int64_t(sampleRate * tEnd), totalFrames);
		if (start < end)
		{
			loopStart = start;
			loopEnd = end;
		}
	}
}

double AudioDecoder::getLoopingStart()
{
	return (double)getLoopStart() / getSampleRate();
}

double AudioDecoder::getLoopingEnd()
{
	return (double)getLoopEnd() / getSampleRate();
}

int64_t AudioDecoder::getLoopStart() const
{
	return loopStart;
}

int64_t AudioDecoder::getLoopEnd() const
{
	return loopEnd == 0 ? getTotalFrames() : loopEnd;
}

bool AudioDecoder::rewind()
{
	return seek(getLoopStart());
}

bool AudioDecoder::isFinished()
{
	return eof;
}

NS_CC_END
