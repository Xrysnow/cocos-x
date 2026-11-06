#pragma once
#include "VideoDecoder.h"
#include "VideoPlayMode.h"
#include "base/CCRefPtr.h"
#include <cstdint>
#include <memory>
#include <string>

namespace video
{
	enum class PlaybackUpdate
	{
		NoFrame,
		FrameReady,
		Ended,
		Error,
	};

	// Synchronous playback session. The caller supplies ticks and consumes frames.
	class VideoPlayback
	{
	public:
		enum class State { Stopped, Playing, Paused, Ended, Failed };

		static std::unique_ptr<VideoPlayback> create(const std::string& path);
		~VideoPlayback();

		PlaybackUpdate start();
		PlaybackUpdate stop();
		void pause();
		void resume();
		void cancelAutomaticPlayback();
		void setMode(PlayMode mode);
		void setStep(double seconds) { step = seconds; }

		PlaybackUpdate seekFrame(uint32_t frame);
		PlaybackUpdate tick(double seconds);
		PlaybackUpdate advance(double seconds);
		PlaybackUpdate advanceFrame();

		State getState() const { return state; }
		bool wantsTicks() const { return state == State::Playing || state == State::Paused; }
		bool endedAt(uint64_t generation) const;
		Decoder* getDecoder() const { return decoder.get(); }
		// Borrowed from the decoder. Consume before the next read, seek or close.
		uint8_t* getFrame() const;

	private:
		explicit VideoPlayback(Decoder* source);
		VideoPlayback(const VideoPlayback&) = delete;
		VideoPlayback& operator=(const VideoPlayback&) = delete;

		void syncDecoderGeneration();
		PlaybackUpdate advanceImpl(double seconds, bool nextFrame);

		cocos2d::RefPtr<Decoder> decoder;
		uint8_t* pixels = nullptr;
		uint64_t decoderGeneration = 0;
		double mediaTime = 0.0;
		double step = 1.0 / 60;
		bool atStart = true;
		PlayMode mode = PlayMode::STEP;
		State state = State::Stopped;
	};
}
