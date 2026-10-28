#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioDecoder.h"
#include "AudioStream.h"
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
#include <cstdint>

NS_CC_BEGIN
	class CC_DLL AudioDecoderVorbisStb : public AudioDecoder
	{
		AudioDecoderVorbisStb(size_t bufferSize);
		virtual ~AudioDecoderVorbisStb();
		bool init(AudioStream* src);
	public:

		static AudioDecoderVorbisStb* create(AudioStream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	private:
		stb_vorbis* handle = nullptr;
		stb_vorbis_info vorbisInfo;
		stb_vorbis_comment vorbisComment;
		int64_t framePosition = 0;
	};
NS_CC_END
