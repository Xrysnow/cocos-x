#define DR_FLAC_IMPLEMENTATION
#include "AudioDecoderFlac.h"

NS_CC_BEGIN

/*
Callback for when data needs to be read from the client.

pUserData   [in]  The user data that was passed to drflac_open() and family.
pBufferOut  [out] The output buffer.
bytesToRead [in]  The number of bytes to read.

Returns the number of bytes actually read.

A return value of less than bytesToRead indicates the end of the stream. Do _not_ return from this callback until
either the entire bytesToRead is filled or you have reached the end of the stream.
*/
static size_t flacRead(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
	auto src = (AudioStream*)pUserData;
	size_t toRead = src->size() - src->tell();
	if (toRead > bytesToRead)
		toRead = bytesToRead;
	uint64_t read = 0;
	src->read((uint8_t*)pBufferOut, toRead, &read);
	return read;
}
/*
Callback for when data needs to be seeked.

pUserData [in] The user data that was passed to drflac_open() and family.
offset    [in] The number of bytes to move, relative to the origin. Will never be negative.
origin    [in] The origin of the seek - the current position or the start of the stream.

Returns whether or not the seek was successful.

The offset will never be negative. Whether or not it is relative to the beginning or current position is determined
by the "origin" parameter which will be either drflac_seek_origin_start or drflac_seek_origin_current.
*/
static drflac_bool32 flacSeek(void* pUserData, int offset, drflac_seek_origin origin)
{
	auto src = (AudioStream*)pUserData;
	bool ret = false;
	switch (origin) {
	case drflac_seek_origin_start:
		ret = src->seek(AudioStream::SeekOrigin::BEGINNING, offset);
		break;
	case drflac_seek_origin_current:
		ret = src->seek(AudioStream::SeekOrigin::CURRENT, offset);
		break;
	default: ;
	}
	return ret;
}

AudioDecoderFlac::AudioDecoderFlac(size_t bufferSize)
	: AudioDecoder(bufferSize, DecoderType::FLAC)
{
}

AudioDecoderFlac::~AudioDecoderFlac()
{
	if (flac)
		drflac_close(flac);
	if (stream)
	{
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool AudioDecoderFlac::init(AudioStream* src)
{
	stream = src;
	if (!stream)
		return false;
	// The destructor releases stream on both successful and failed initialization.
	stream->retain();
	stream->lock();
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	//TODO: metadata
	flac = drflac_open(flacRead, flacSeek, stream, nullptr);
	stream->unlock();
	if (!flac)
		return false;
	audioInfo.sampleRate = flac->sampleRate;
	//audioInfo.bytesPerFrame = flac->bitsPerSample / 8;
	audioInfo.bytesPerFrame = 2 * flac->channels;
	audioInfo.channelCount = flac->channels;
	audioInfo.totalFrames = flac->totalPCMFrameCount;
	return true;
}

AudioDecoderFlac* AudioDecoderFlac::create(AudioStream* src, size_t bufferSize)
{
	auto ret = new (std::nothrow) AudioDecoderFlac(bufferSize);
	if (ret&&ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t AudioDecoderFlac::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	const auto framesRead = drflac_read_pcm_frames_s16(flac, bytesToRead / audioInfo.bytesPerFrame, (drflac_int16*)dst);
	stream->unlock();
	const auto bytesRead = framesRead * 2 * audioInfo.channelCount;
	if (bytesRead < bytesToRead)
		eof = true;
	return bytesRead;
}

bool AudioDecoderFlac::seek(int64_t frameOffset)
{
	stream->lock();
	const bool result = drflac_seek_to_pcm_frame(flac, (drflac_uint64)frameOffset) == DRFLAC_TRUE;
	stream->unlock();
	if (result)
		eof = false;
	return result;
}

int64_t AudioDecoderFlac::tell()
{
	return flac->currentPCMFrame;
}

bool AudioDecoderFlac::isSeekable()
{
	return true;
}

NS_CC_END
