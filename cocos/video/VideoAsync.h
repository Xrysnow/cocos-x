#pragma once
#include "VideoPlayMode.h"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace video
{
	enum class AsyncVideoState { Opening, Ready, Seeking, Buffering, Ended, Failed, Closing, Closed };
	enum class AsyncVideoError { None, Open, FrameBudget, Decode, Seek, Present,
		AudioDecode, AudioOutput, Timestamp, BufferBudget };
	enum class AudioTrackState { Disabled, NoTrack, Preparing, Active, Ended, Failed };
	enum class MediaClock { Scheduler, AudioCalibrated, AudioUncalibrated, Monotonic };

	struct PlaybackOptions
	{
		PlayMode mode = PlayMode::STEP;
		bool audioEnabled = false;
	};

	// Main-thread view. Time and frame index describe the last presented frame.
	struct AsyncVideoSnapshot
	{
		AsyncVideoState state = AsyncVideoState::Opening;
		AsyncVideoError error = AsyncVideoError::None;
		uint64_t generation = 0;
		int64_t frame = -1;
		double seconds = -1.0;
		double duration = 0.0;
		int width = 0;
		int height = 0;
		size_t audioTracks = 0;
		size_t bufferedFrames = 0;
		size_t allocatedFrameBytes = 0;
		uint64_t skippedFrames = 0;
		// The media clock is independent of the last presented frame's seconds.
		double mediaSeconds = 0.0;
		std::optional<double> seekTargetSeconds;
		std::optional<double> seekActualSeconds;
		AudioTrackState audioState = AudioTrackState::Disabled;
		int selectedAudioStream = -1;
		MediaClock clock = MediaClock::Scheduler;
		bool clockValid = false;
		bool latencyValid = false;
		bool audioSuspended = false;
		std::optional<double> outputLatencySeconds;
		double bufferedAudioSeconds = 0.0;
		uint64_t audioUnderruns = 0;
		int deviceGeneration = 0;
		size_t bufferedPacketBytes = 0;
		size_t bufferedPackets = 0;
		bool timestampEstimated = false;
		uint64_t timestampGapFrames = 0;
		uint64_t timestampOverlapFrames = 0;
		double videoEndSeconds = 0.0;
		bool videoEnded = false;
		bool audioEnded = false;
		std::string errorStage;
		int backendError = 0;
		std::string errorMessage;
	};
}
