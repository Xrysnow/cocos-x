#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioDecoder.h"

NS_CC_BEGIN
	class CC_DLL AudioDecoderWav : public AudioDecoder
	{
		AudioDecoderWav(size_t bufferSize);
		virtual ~AudioDecoderWav();
		bool init(AudioStream* src);
	public:

		static AudioDecoderWav* create(AudioStream* src, size_t bufSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;

	protected:
		uint64_t data_offset = 0;
	};
NS_CC_END
