#include "AudioCommon.h"
#include "AudioDecoderWav.h"
#include "NqrRiffUtils.h"
#include <algorithm>
#include <new>
#include <vector>
#include <cstring>

using namespace nqr;
NS_CC_BEGIN
using namespace AudioInternal;

const uint32_t CKC_RIFF = GenerateChunkCode('R', 'I', 'F', 'F');
const uint32_t CKC_RIFX = GenerateChunkCode('R', 'I', 'F', 'X');
const uint32_t CKC_FFIR = GenerateChunkCode('F', 'F', 'I', 'R');
const uint32_t CKC_WAVE = GenerateChunkCode('W', 'A', 'V', 'E');
const uint32_t CKC_fmt_ = GenerateChunkCode('f', 'm', 't', ' ');
const uint32_t CKC_fact = GenerateChunkCode('f', 'a', 'c', 't');
const uint32_t CKC_bext = GenerateChunkCode('b', 'e', 'x', 't');
const uint32_t CKC_data = GenerateChunkCode('d', 'a', 't', 'a');

AudioDecoderWav::AudioDecoderWav(size_t bufferSize)
	: AudioDecoder(bufferSize, DecoderType::WAV)
{
}

AudioDecoderWav::~AudioDecoderWav()
{
	if (stream)
	{
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->release();
		stream = nullptr;
	}
}

bool AudioDecoderWav::init(AudioStream* src)
{
	stream = src;
	if (!stream)
		return false;
	// The destructor releases stream on both successful and failed initialization.
	stream->retain();
	std::string msg;
	std::vector<uint8_t> tempBufferData;
	bool ret = false;
	stream->lock();
	stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
	auto size = stream->size();
	do
	{
		// Read RIFF Header
		RiffChunkHeader riffHeader = {};
		stream->read((uint8_t*)&riffHeader, 12);
		// Check RIFF
		if (riffHeader.id_riff != CKC_RIFF) {
			if (riffHeader.id_riff == CKC_RIFX || riffHeader.id_riff == CKC_FFIR) {
				msg = "doesn't support big endian file";
				break;
			}
			msg = "bad RIFF/RIFX/FFIR file header";
			break;
		}

		if (riffHeader.id_wave != CKC_WAVE) {
			msg = "bad WAVE header";
			break;
		}
		auto expectedSize = size - riffHeader.file_size;
		if (expectedSize != sizeof(uint32_t) * 2) {
			msg = "declared size of file dosn't match real size";
			break;
		}
		// note: assume that header is smaller than 256B
		try
		{
			tempBufferData.resize(256);
		}
		catch (const std::bad_alloc&)
		{
			msg = "failed to allocate temporary buffer";
			break;
		}
		auto tempBuffer = tempBufferData.data();
		uint64_t bufferLength;
		stream->seek(AudioStream::SeekOrigin::BEGINNING, 0);
		stream->read(tempBuffer, 256, &bufferLength);

		// Read WAVE Header
		auto WaveChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_fmt_);
		if (WaveChunkInfo.offset == 0) {
			msg = "couldn't find fmt chunk";
			break;
		}
		CC_ASSERT(WaveChunkInfo.size == 16 || WaveChunkInfo.size == 18 ||
			WaveChunkInfo.size == 20 || WaveChunkInfo.size == 40);
		WaveChunkHeader wavHeader = {};
		memcpy(&wavHeader, tempBuffer + WaveChunkInfo.offset, sizeof(WaveChunkHeader));

		if (wavHeader.chunk_size < 16) {
			msg = "format chunk too small";
			break;
		}
		//TODO: validate wav header (sane sample rate, bit depth, etc)

		audioInfo.channelCount = wavHeader.channel_count;
		audioInfo.sampleRate = wavHeader.sample_rate;
		audioInfo.bytesPerFrame = wavHeader.frame_size;

		auto bit_depth = wavHeader.bit_depth;
		CC_ASSERT(audioInfo.channelCount*bit_depth / 8 == wavHeader.frame_size);
		if (bit_depth != 16) {
			// todo: not implemented
			msg = "only support 16bit format, got " + std::to_string(bit_depth) + "bit";
			break;
		}

		bool scanForFact = false;
		bool grabExtensibleData = false;
		//bool adpcmEncoded = false;
		if (wavHeader.format == FORMAT_PCM)
		{
		}
		else if (wavHeader.format == FORMAT_IEEE)
		{
			scanForFact = true;
		}
		else if (wavHeader.format == FORMAT_IMA_ADPCM)
		{
			//adpcmEncoded = true;
			//scanForFact = true;
			// todo: not implemented
			msg = "not support ADPCM format";
			break;
		}
		else if (wavHeader.format == FORMAT_EXT)
		{
			// Used when (1) PCM data has more than 16 bits; (2) channels > 2;
			// (3) bits/sample !== container size; (4) channel/speaker mapping specified
			//std::cout << "[format id] extended" << std::endl;
			scanForFact = true;
			grabExtensibleData = true;
		}
		else if (wavHeader.format == FORMAT_UNKNOWN) {
			msg = "unknown wave format";
			break;
		}

		// Read Additional Chunks
		FactChunk factChunk{};
		if (scanForFact)
		{
			auto FactChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_fact);
			if (FactChunkInfo.size)
				memcpy(&factChunk, tempBuffer + FactChunkInfo.offset, sizeof(FactChunk));
		}
		if (grabExtensibleData)
		{
			ExtensibleData extData = {};
			memcpy(&extData, tempBuffer + WaveChunkInfo.offset + sizeof(WaveChunkHeader), sizeof(ExtensibleData));
			// extData can be compared against the multi-channel masks defined in the header
			// eg. extData.channel_mask == SPEAKER_5POINT1
		}

		// Read Bext Chunk
		auto BextChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_bext);
		BextChunk bextChunk = {};
		if (BextChunkInfo.size)
			memcpy(&bextChunk, tempBuffer + BextChunkInfo.offset, sizeof(BextChunk));

		// Read DATA Chunk
		auto DataChunkInfo = ScanForChunk(tempBuffer, bufferLength, CKC_data);
		if (DataChunkInfo.offset == 0) {
			msg = "couldn't find data chunk |size=" + std::to_string(stream->size()) +
				"|temp buf size=" + std::to_string(bufferLength);
			break;
		}
		uint32_t data_size;
		memcpy(&data_size, tempBuffer + DataChunkInfo.offset + sizeof(uint32_t), sizeof(uint32_t));
		data_offset = DataChunkInfo.offset + 2 * sizeof(uint32_t);// skip the header and size fields
		// note: there may be some info at file tail, only use data_size
		if (data_size != stream->size() - data_offset)
		{
			msg = "data size mismatch: expect " + std::to_string(data_size) +
				", got " + std::to_string(stream->size() - data_offset);
			data_size = std::min(data_size, uint32_t(stream->size() - data_offset));
		}
		//if (adpcmEncoded){}
		audioInfo.totalFrames = data_size / wavHeader.frame_size;
		stream->seek(AudioStream::SeekOrigin::BEGINNING, data_offset);
		ret = true;
	}
	while (false);
	stream->unlock();
	if (!msg.empty())
	{
		AINFO("%s", msg.c_str());
	}
	return ret;
}

AudioDecoderWav* AudioDecoderWav::create(AudioStream* src, size_t bufSize)
{
	auto ret = new (std::nothrow) AudioDecoderWav(bufSize);
	if (ret&&ret->init(src))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

int64_t AudioDecoderWav::decode(char* dst, uint64_t bytesToRead)
{
	stream->lock();
	int64_t tSizeRead = 0;
	auto tBuffer = (uint8_t*)dst;
	while (tSizeRead < bytesToRead)
	{
		uint64_t read;
		stream->read(tBuffer, bytesToRead - tSizeRead, &read);
		if (read == 0)  // got end
		{
			eof = true;
			break;
		}
		tSizeRead += read;
		tBuffer += read;
	}
	stream->unlock();
	return tSizeRead;
}

bool AudioDecoderWav::seek(int64_t frameOffset)
{
	if (frameOffset >= getTotalFrames())
		return false;
	stream->lock();
	const bool ret = stream->seek(AudioStream::SeekOrigin::BEGINNING, data_offset + frameOffset * getBytesPerFrame());
	stream->unlock();
	if (ret)
		eof = false;
	return ret;
}

int64_t AudioDecoderWav::tell()
{
	const int64_t p = (int64_t)stream->tell() - (int64_t)data_offset;
	return std::max<int64_t>(0, p) / getBytesPerFrame();
}

bool AudioDecoderWav::isSeekable()
{
	return true;
}

NS_CC_END
