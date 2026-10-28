#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioDecoder.h"
#include "base/ccMacros.h"
#if CC_64BITS
#define DRFLAC_64BIT
#endif
#include "dr_flac.h"

NS_CC_BEGIN
	class CC_DLL AudioDecoderFlac : public AudioDecoder
	{
		AudioDecoderFlac(size_t bufferSize);
		virtual ~AudioDecoderFlac();
		bool init(AudioStream* src);
	public:
		static AudioDecoderFlac* create(AudioStream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;
	private:
		drflac* flac = nullptr;
	};	
NS_CC_END
