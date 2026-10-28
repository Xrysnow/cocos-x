#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioDecoder.h"
#include "AudioStream.h"
#define OV_EXCLUDE_STATIC_CALLBACKS
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
#include <cstdint>

NS_CC_BEGIN
	class CC_DLL AudioDecoderVorbis : public AudioDecoder
	{
		AudioDecoderVorbis(size_t bufferSize);
		virtual ~AudioDecoderVorbis();
		bool init(AudioStream* src);
	public:

		static AudioDecoderVorbis* create(AudioStream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	private:
		ov_callbacks vorbisCallbacks;	// Callbacks used to read the file from mem
		OggVorbis_File handle;			// Handle to the file
		vorbis_info* vorbisInfo = nullptr;
		vorbis_comment* vorbisComment = nullptr;
		int endian = 0;
	};
NS_CC_END
