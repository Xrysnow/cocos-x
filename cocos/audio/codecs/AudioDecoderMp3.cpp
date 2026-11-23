#define DR_MP3_IMPLEMENTATION
#include "AudioDecoderMp3.h"
#include <algorithm>
#include <mutex>

NS_CC_BEGIN

/*
Callback for when data is read. Return value is the number of bytes actually read.

pUserData   [in]  The user data that was passed to drmp3_init(), drmp3_open() and family.
pBufferOut  [out] The output buffer.
bytesToRead [in]  The number of bytes to read.

Returns the number of bytes actually read.

A return value of less than bytesToRead indicates the end of the stream. Do _not_ return from this callback until
either the entire bytesToRead is filled or you have reached the end of the stream.
*/
static size_t mp3Read(void* pUserData, void* pBufferOut, size_t bytesToRead)
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

pUserData [in] The user data that was passed to drmp3_init(), drmp3_open() and family.
offset    [in] The number of bytes to move, relative to the origin. Will never be negative.
origin    [in] The origin of the seek - the current position or the start of the stream.

Returns whether or not the seek was successful.

Whether or not it is relative to the beginning or current position is determined by the "origin" parameter which
will be either drmp3_seek_origin_start or drmp3_seek_origin_current.
*/
static drmp3_bool32 mp3Seek(void* pUserData, int offset, drmp3_seek_origin origin)
{
	auto src = (AudioStream*)pUserData;
	bool ret = false;
	switch (origin) {
	case drmp3_seek_origin_start:
		ret = src->seek(AudioStream::SeekOrigin::BEGINNING, offset);
		break;
	case drmp3_seek_origin_current:
		ret = src->seek(AudioStream::SeekOrigin::CURRENT, offset);
		break;
	default:;
	}
	return ret;
}

typedef struct
{
	char Header[3];
	char Ver;
	char Revision;
	char Flag;
	char Size[4];
} ID3v2Header;

uint32_t getID3v2HeaderSize(const ID3v2Header& h)
{
	if (memcmp(h.Header, "ID3", 3) != 0)
		return 0;
	return (h.Size[0] & 0x7F) * 0x200000
		+ (h.Size[1] & 0x7F) * 0x4000
		+ (h.Size[2] & 0x7F) * 0x80
		+ (h.Size[3] & 0x7F);
}

/* big endian extract */
static uint32_t ExtractI4(AudioStream* stream)
{
	uint8_t buf[4]{};
	if (!stream->read(buf, sizeof(buf)))
		return 0;
	uint32_t x;
	x = buf[0];
	x <<= 8;
	x |= buf[1];
	x <<= 8;
	x |= buf[2];
	x <<= 8;
	x |= buf[3];
	return x;
}

static void GetVbrTag(AudioStream* stream, uint32_t& frames, int& enc_delay, int& enc_padding)
{
	int head_flags = ExtractI4(stream);
	if (head_flags & 0x0001)
		frames = ExtractI4(stream);
	if (head_flags & 0x0002)
		stream->seek(AudioStream::SeekOrigin::CURRENT, 4);
	if (head_flags & 0x0004)
		stream->seek(AudioStream::SeekOrigin::CURRENT, 100);
	if (head_flags & 0x0008)
		stream->seek(AudioStream::SeekOrigin::CURRENT, 4);
	stream->seek(AudioStream::SeekOrigin::CURRENT, 21);
	uint8_t buf[3]{};
	if (!stream->read(buf, sizeof(buf)))
		return;
	enc_delay = buf[0] << 4;
	enc_delay += buf[1] >> 4;
	enc_padding = (buf[1] & 0x0F) << 8;
	enc_padding += buf[2];
	if (enc_delay < 0 || enc_delay > 3000)
		enc_delay = -1;
	if (enc_padding < 0 || enc_padding > 3000)
		enc_padding = -1;
}

AudioDecoderMp3::AudioDecoderMp3(size_t bufferSize)
	: AudioDecoder(bufferSize, DecoderType::MP3)
{
}

AudioDecoderMp3::~AudioDecoderMp3()
{
	if (mp3)
		drmp3_uninit(mp3);
	delete mp3;
	if (stream)
	{
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool AudioDecoderMp3::init(AudioStream* src)
{
	stream = src;
	if (!stream)
		return false;
	// The destructor releases stream on both successful and failed initialization.
	stream->retain();
	mp3 = new drmp3{};
	stream->lock();
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	const auto ok = drmp3_init(mp3, mp3Read, mp3Seek, stream, nullptr);
	stream->unlock();
	if(!ok)
	{
		// drmp3_init already frees its buffers on failure. Only uninit a
		// successfully initialized handle; otherwise the destructor frees twice.
		delete mp3;
		mp3 = nullptr;
		return false;
	}
	audioInfo.sampleRate = mp3->sampleRate;
	//audioInfo.bytesPerFrame = flac->bitsPerSample / 8;
	audioInfo.bytesPerFrame = 2 * mp3->channels;
	audioInfo.channelCount = mp3->channels;
	std::unique_lock streamLock(*stream);
	audioInfo.totalFrames = drmp3_get_pcm_frame_count(mp3);
	if (stream->hasIoError())
		return false;

	ID3v2Header h{};
	uint8_t hdr[4]{};
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	stream->read((uint8_t*)&h, sizeof(h));
	auto hsize = getID3v2HeaderSize(h);
	const auto readHeader = [&] {
		return stream->seek(AudioStream::SeekOrigin::BEGINNING, hsize) &&
			stream->read(hdr, sizeof(hdr)) && drmp3_hdr_valid(hdr);
	};
	bool findFrame = readHeader();
	if (!findFrame)
	{
		hsize += 10;
		findFrame = readHeader();
	}
	if (findFrame)
	{
		static const uint8_t info_hdr_offset[2][2] = {{21, 13}, {36, 21}};
		const auto offset = hsize + info_hdr_offset[!!DRMP3_HDR_TEST_MPEG1(hdr)][!!DRMP3_HDR_IS_MONO(hdr)];
		stream->seek(AudioStream::SeekOrigin::BEGINNING, offset);
		uint8_t k[4]{};
		stream->read(k, 4);
		const std::string key{ (const char*)k,4 };
		if (key == "Info" || key == "Xing")
		{
			uint32_t frames = 0;
			int enc_delay = -1;
			int enc_padding = -1;
			GetVbrTag(stream, frames, enc_delay, enc_padding);
			if (frames > 0 && enc_delay >= 0 && enc_padding >= 0)
			{
				const auto begin = enc_delay + 529;
				const auto fullend = static_cast<int64_t>(frames) * drmp3_hdr_frame_samples(hdr);
				const auto end = fullend - enc_padding + 529;
				const auto count = std::min(fullend, end) - begin;
				if (count > 0 && count <= audioInfo.totalFrames)
				{
					audioInfo.totalFrames = count;
					frameBegin = begin;
					frameEnd = begin + count;
				}
			}
		}
	}
	// Header probing moves the underlying stream independently of drmp3's
	// compressed-data cache. Reset both before seeking past encoder delay.
	const auto reset = drmp3_seek_to_pcm_frame(mp3, 0);
	streamLock.unlock();
	return reset && !stream->hasIoError() && seek(0);
}

cc::IntrusivePtr<AudioDecoderMp3> AudioDecoderMp3::create(AudioStream* src, size_t bufferSize)
{
	cc::IntrusivePtr ret{new (std::nothrow) AudioDecoderMp3(bufferSize)};
	if (ret&&ret->init(src))
	{
		return ret;
	}
	return nullptr;
}

int64_t AudioDecoderMp3::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	const auto framesRead = drmp3_read_pcm_frames_s16(mp3, bytesToRead / audioInfo.bytesPerFrame, (drmp3_int16*)dst);
	stream->unlock();
	const auto bytesRead = framesRead * 2 * audioInfo.channelCount;
	if (bytesRead < bytesToRead)
		eof = true;
	return bytesRead;
}

bool AudioDecoderMp3::seek(int64_t frameOffset)
{
	if (frameOffset >= getTotalFrames())
		return false;
	stream->lock();
	const drmp3_bool32 result = drmp3_seek_to_pcm_frame(mp3, (drmp3_uint64)(frameOffset + frameBegin));
	stream->unlock();
	if (result)
		eof = false;
	return result;
}

int64_t AudioDecoderMp3::tell()
{
	return mp3->currentPCMFrame - frameBegin;
}

bool AudioDecoderMp3::isSeekable()
{
	return true;
}

NS_CC_END
