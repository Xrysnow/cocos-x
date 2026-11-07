#pragma once
#include "VideoAsync.h"
#include "io/Stream.h"
#include <atomic>
#include <cstdint>
#include <memory>

namespace video
{
	// Worker-only, bounded audio/video decoding. No OpenAL or caller-thread state.
	class VideoAVDecoder final
	{
	public:
		enum class Step { Progress, Waiting, NeedInput, End, Error };
		struct Info
		{
			int width = 0, height = 0;
			double duration = 0.0, frameRate = 0.0;
			size_t audioTracks = 0;
			int audioStream = -1;
		};
		struct Video
		{
			int64_t index = -1;
			double seconds = 0.0, duration = 0.0;
		};
		struct Audio
		{
			const int16_t* samples = nullptr;
			size_t frames = 0;
		};

		VideoAVDecoder();
		~VideoAVDecoder();
		bool open(cocos2d::io::StreamPtr source, const std::atomic<bool>* stop);
		bool seek(double seconds, bool audioEnabled);
		Step step(bool wantVideo, bool wantAudio);
		const Info& info() const;
		bool hasVideo() const;
		Video video() const;
		bool convertVideo(uint8_t* rgba, int stride);
		void consumeVideo();
		Audio audio() const;
		void consumeAudio();
		bool videoEnded() const;
		bool audioEnded() const;
		double videoEndSeconds() const;
		size_t packetBytes() const;
		size_t packetCount() const;
		bool packetBudgetBlocked() const;
		bool timestampEstimated() const;
		uint64_t gapFrames() const;
		uint64_t overlapFrames() const;
		AsyncVideoError error() const;
		int backendError() const;
		const char* errorStage() const;
		const char* errorMessage() const;

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;
	};
}
