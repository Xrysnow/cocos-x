#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace cocos2d { class AudioSource; }

namespace video
{
	// Private fixed-format output; the worker owns any PCM not yet accepted here.
	class VideoAudioSink final
	{
	public:
		static constexpr uint32_t SampleRate = 48000;
		static constexpr size_t ChunkFrames = 960;
		static constexpr uint64_t BudgetFrames = 9600;
		enum class SubmitResult { Accepted, Full, StaleGeneration, DeviceChanged, Closed, Error };
		struct Snapshot
		{
			uint64_t generation = 0;
			int deviceGeneration = 0;
			double mediaSeconds = 0.0;
			bool clockValid = false;
			bool latencyValid = false;
			std::optional<double> outputLatencySeconds;
			bool suspended = false;
			bool playing = false;
			bool buffering = true;
			bool ended = false;
			bool deviceChanged = false;
			bool failed = false;
			uint64_t submittedFrames = 0;
			uint64_t consumedFrames = 0;
			uint64_t bufferedFrames = 0;
			uint64_t residentFrames = 0;
			uint64_t underruns = 0;
			int errorCode = 0;
			std::string error;
		};

		VideoAudioSink();
		~VideoAudioSink();
		VideoAudioSink(const VideoAudioSink&) = delete;
		VideoAudioSink& operator=(const VideoAudioSink&) = delete;
		// Reset immediately silences and rejects earlier-generation payloads.
		bool reset(uint64_t generation, double mediaSeconds);
		void setPlaybackAllowed(bool allowed);
		bool setGain(float volume, bool muted);
		SubmitResult submit(uint64_t generation, const int16_t* stereo, size_t frames);
		void markEndOfStream(uint64_t generation);
		// Also performs the bounded start/rebuffer checks; worker calls at <=5 ms
		// intervals during active supply. No main-thread callback is needed.
		Snapshot snapshot();
		void close();

	private:
		Snapshot sampleLocked(bool mayStart = true);
		void updateFreezeLocked(bool frozen, double now);
		bool createSourceLocked();
		void failLocked(const std::string& message, int code = 0);
		std::mutex mutex;
		cocos2d::AudioSource* source = nullptr; // owns the initial Ref reference
		Snapshot state;
		uint64_t queueGeneration = 0;
		double anchorSeconds = 0.0;
		bool allowed = false;
		bool closed = false;
		bool eos = false;
		bool started = false;
		bool rebuffering = true;
		float volume = 1.0f;
		bool muted = false;
		double lastSampleTime = 0.0;
		double lastLatency = 0.0;
		double lastValidTime = 0.0;
		double failureSince = 0.0;
		double frozenSince = 0.0;
		double tailSampleTime = 0.0;
		double tailMediaSeconds = 0.0;
		double tailEndSeconds = 0.0;
		bool tailActive = false;
		int outputRevision = 0;
	};
}
