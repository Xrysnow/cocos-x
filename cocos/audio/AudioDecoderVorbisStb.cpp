#include "AudioDecoderVorbisStb.h"
#include "AudioCommon.h"
#include <limits>
#include <string>

NS_CC_BEGIN
using namespace AudioInternal;

static int stbVorbisRead(void* cookie, char* buf, unsigned int size)
{
	const auto p = (AudioStream*)cookie;
	// skip if not enough
	if (p->size() - p->tell() < size)
		return 0;
	uint64_t read = 0;
	if (!p->read((uint8_t*)buf, size, &read))
		return 0;
	return (int)read;
}
static int stbVorbisSeek(void* cookie, int* pos, int whence)
{
	const auto p = (AudioStream*)cookie;
	AudioStream::SeekOrigin origin = AudioStream::SeekOrigin::BEGINNING;
	if (whence == SEEK_CUR)
		origin = AudioStream::SeekOrigin::CURRENT;
	else if (whence == SEEK_END)
		origin = AudioStream::SeekOrigin::END;
	const bool ok = p->seek(origin, *pos);
	*pos = (int)p->tell();
	return ok ? 0 : -1;
}
static int stbVorbisTell(void* cookie)
{
	const auto p = (AudioStream*)cookie;
	return (int)p->tell();
}
static int stbVorbisClose(void* cookie)
{
	return 0;
}

AudioDecoderVorbisStb::AudioDecoderVorbisStb(size_t bufferSize)
	: AudioDecoder(bufferSize, DecoderType::VORBIS)
{
}

AudioDecoderVorbisStb::~AudioDecoderVorbisStb()
{
	stb_vorbis_close(handle);
	if (stream)
	{
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool AudioDecoderVorbisStb::init(AudioStream* src)
{
	stream = src;
	if (!stream)
		return false;
	// The destructor releases stream on both successful and failed initialization.
	stream->retain();
	stream->lock();
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	stb_vorbis_cookie cookie;
	cookie.cookie = stream;
	cookie.reader = stbVorbisRead;
	cookie.seeker = stbVorbisSeek;
	cookie.teller = stbVorbisTell;
	cookie.closer = stbVorbisClose;
	int error;
	handle = stb_vorbis_open_cookie(cookie, &error, nullptr, (unsigned)stream->size());
	stream->unlock();
	if (!handle)
	{
		AINFO("can't open vorbis stream: %d", error);
		return false;
	}
	vorbisInfo = stb_vorbis_get_info(handle);
	vorbisComment = stb_vorbis_get_comment(handle);
	// stb reports samples per channel, which are already PCM frames.
	audioInfo.totalFrames = stb_vorbis_stream_length_in_samples(handle); // can be 0 if not given
	audioInfo.channelCount = vorbisInfo.channels;
	audioInfo.sampleRate = vorbisInfo.sample_rate;
	audioInfo.bytesPerFrame = vorbisInfo.channels * 2; // 16bit

	return true;
}

AudioDecoderVorbisStb* AudioDecoderVorbisStb::create(AudioStream* src, size_t bufferSize)
{
	auto ret = new (std::nothrow) AudioDecoderVorbisStb(bufferSize);
	if (ret && ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t AudioDecoderVorbisStb::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	const auto nFrame = stb_vorbis_get_samples_short_interleaved(handle, vorbisInfo.channels, (short*)dst, bytesToRead / 2);
	stream->unlock();
	if (nFrame == 0)
		eof = true;
	// stb's pull decoder position includes samples still in its internal buffer.
	// Track only the frames actually returned to the caller instead.
	framePosition += nFrame;
	return int64_t(nFrame) * vorbisInfo.channels * 2;
}

bool AudioDecoderVorbisStb::seek(int64_t frameOffset)
{
	if (frameOffset < 0 || static_cast<uint64_t>(frameOffset) > std::numeric_limits<unsigned int>::max())
		return false;
	stream->lock();
	const auto ret = stb_vorbis_seek(handle, static_cast<unsigned int>(frameOffset));
	stream->unlock();
	const auto ok = ret == 1;
	if (ok)
	{
		framePosition = frameOffset;
		eof = false;
	}
	return ok;
}

int64_t AudioDecoderVorbisStb::tell()
{
	return framePosition;
}

bool AudioDecoderVorbisStb::isSeekable()
{
	return true;
}

NS_CC_END
