#pragma once
#include <cstddef>
#include <cstdint>

namespace video
{
	enum class AsyncVideoState { Opening, Ready, Seeking, Buffering, Ended, Failed, Closing, Closed };
	enum class AsyncVideoError { None, Open, FrameBudget, Decode, Seek, Present };

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
	};
}
