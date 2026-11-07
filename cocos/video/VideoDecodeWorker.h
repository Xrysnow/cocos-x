#pragma once
#include "VideoAsync.h"
#include "io/Stream.h"
#include <atomic>
#include <functional>
#include <memory>
#include <optional>

namespace video
{
	class VideoDecodeWorker final
	{
	public:
		enum class ReadStatus { FrameReady, NotDue, Waiting, EndOfStream, Error, Closed };
		struct Frame
		{
			std::unique_ptr<uint8_t[]> rgba;
			int64_t index = -1;
			double seconds = -1.0;
			double duration = 0.0;
		};
		struct Read
		{
			ReadStatus status;
			size_t skipped = 0;
		};

		static std::unique_ptr<VideoDecodeWorker> create(cocos2d::io::StreamPtr source,
			std::function<void()> cancel);
		static std::unique_ptr<VideoDecodeWorker> create(cocos2d::io::StreamPtr source,
			std::function<void()> cancel, const PlaybackOptions& options);
		~VideoDecodeWorker();

		// All consumer operations run on the owning thread.
		std::optional<uint64_t> seek(uint32_t frame);
		std::optional<uint64_t> seekTime(double seconds);
		void setMode(PlayMode mode);
		void setPlaybackActive(bool active);
		void setAudioVolume(float volume);
		void setAudioMuted(bool muted);
		Read take(std::optional<double> deadline = {}, bool latest = false);
		const Frame* presentedFrame() const;
		AsyncVideoSnapshot snapshot() const;
		void requestClose();
		std::shared_ptr<const std::atomic<bool>> completion() const;

	private:
		struct State;
		struct Threads;
		explicit VideoDecodeWorker(std::shared_ptr<State> state);
		static void run(State& state, cocos2d::io::StreamPtr source);
		static void runSilent(State& state, cocos2d::io::StreamPtr source);
		static void runWithAudio(State& state, cocos2d::io::StreamPtr source);

		std::shared_ptr<State> state;
		int presented = -1;
	};
}
