#pragma once
#include "VideoDecoder.h"
#include "VideoAsync.h"
#include "VideoPlayMode.h"
#include "base/CCRefPtr.h"
#include <cstdint>
#include <memory>
#include <functional>
#include <optional>

namespace video
{
	class VideoDecodeWorker;
	enum class PlaybackUpdate
	{
		NoFrame,
		FrameReady,
		Ended,
		Error,
	};

	// Main-thread playback state. The caller supplies ticks and consumes frames.
	class VideoPlayback
	{
	public:
		enum class State { Stopped, Playing, Paused, Ended, Failed };

		static std::unique_ptr<VideoPlayback> create(Decoder* source);
		static std::unique_ptr<VideoPlayback> createAsync(cocos2d::io::StreamPtr source,
			std::function<void()> cancel);
		static std::unique_ptr<VideoPlayback> createAsync(cocos2d::io::StreamPtr source,
			std::function<void()> cancel, const PlaybackOptions& options);
		~VideoPlayback();

		PlaybackUpdate start();
		PlaybackUpdate stop();
		void pause();
		void resume();
		void cancelAutomaticPlayback();
		void setMode(PlayMode mode);
		void setStep(double seconds) { step = seconds; }
		void setSceneActive(bool active);
		void setAudioVolume(float volume);
		float getAudioVolume() const { return audioVolume; }
		void setAudioMuted(bool muted);
		bool isAudioMuted() const { return audioMuted; }

		PlaybackUpdate seekFrame(uint32_t frame);
		bool seekTime(double seconds);
		PlaybackUpdate tick(double seconds);
		PlaybackUpdate advance(double seconds);
		PlaybackUpdate advanceFrame();
		void closeAsync(AsyncVideoError error = AsyncVideoError::None);
		std::optional<AsyncVideoSnapshot> getAsyncSnapshot() const;
		void onFramePresented();

		State getState() const { return state; }
		bool wantsTicks() const { return state == State::Playing || state == State::Paused; }
		bool needsTick() const;
		uint64_t getGeneration() const;
		bool endedAt(uint64_t generation) const;
		Decoder* getDecoder() const { return decoder.get(); }
		// Borrowed from the decoder. Consume before the next read, seek or close.
		const uint8_t* getFrame() const;

	private:
		explicit VideoPlayback(Decoder* source);
		explicit VideoPlayback(std::unique_ptr<VideoDecodeWorker> source, const PlaybackOptions& options);
		VideoPlayback(const VideoPlayback&) = delete;
		VideoPlayback& operator=(const VideoPlayback&) = delete;

		void syncDecoderGeneration();
		PlaybackUpdate advanceImpl(double seconds, bool nextFrame);
		PlaybackUpdate tickAsync(double seconds);
		PlaybackUpdate readAsync(double seconds, bool nextFrame, bool manual);
		PlaybackUpdate failAsyncRead();
		void syncPlaybackPermission();
		void beginAsyncSeek(uint64_t generation, bool atOrigin);
		bool usesDeviceClock() const { return audioEnabled && mode == PlayMode::REALTIME; }

		cocos2d::RefPtr<Decoder> decoder;
		std::unique_ptr<VideoDecodeWorker> worker;
		std::shared_ptr<const std::atomic<bool>> closeCompletion;
		std::optional<AsyncVideoSnapshot> async;
		bool awaitingLanding = false;
		bool pendingManualAdvance = false;
		bool pendingManualFrame = false;
		uint8_t* pixels = nullptr;
		uint64_t decoderGeneration = 0;
		double mediaTime = 0.0;
		double step = 1.0 / 60;
		bool atStart = true;
		bool audioEnabled = false;
		bool sceneActive = true;
		bool audioMuted = false;
		float audioVolume = 1.0f;
		PlayMode mode = PlayMode::STEP;
		State state = State::Stopped;
	};
}
