#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioDecoder.h"
#include "dr_mp3.h"

NS_CC_BEGIN
	class CC_DLL AudioDecoderMp3 : public AudioDecoder
	{
		AudioDecoderMp3(size_t bufferSize);
		virtual ~AudioDecoderMp3();
		bool init(AudioStream* src);
	public:
		static AudioDecoderMp3* create(AudioStream* src, size_t bufferSize);

		int64_t decode(char* dst, uint64_t bytesToRead) override;
		bool seek(int64_t frameOffset) override;
		int64_t tell() override;
		bool isSeekable() override;
	private:
		drmp3* mp3 = nullptr;
		int64_t frameBegin = 0;
		int64_t frameEnd = -1;
	};
NS_CC_END
