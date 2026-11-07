#include "VideoAudioSink.h"
#include "audio/AudioEngine.h"
#include "audio/AudioSource.h"
#include <algorithm>
#include <chrono>
#include <cmath>

namespace video
{
	namespace
	{
		double steadySeconds()
		{
			return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
		}
	}

	VideoAudioSink::VideoAudioSink()
	{
		state.deviceGeneration = cocos2d::AudioEngine::getDeviceGeneration();
	}

	VideoAudioSink::~VideoAudioSink()
	{
		close();
	}

	bool VideoAudioSink::createSourceLocked()
	{
		source = cocos2d::AudioSource::createOwnedQueue(SampleRate, 16, 2, 10);
		if (!source)
		{
			failLocked("Could not create the video audio output queue");
			return false;
		}
		source->setSessionControlled(true);
		source->setQueuePlaybackAllowed(false);
		// Stereo is non-spatial, with fixed pitch and no filters/effects.
		source->setRelative(true);
		source->setQueueGain(muted ? 0.0f : volume);
		queueGeneration = source->getQueuePlaybackSnapshot().generation;
		return true;
	}

	bool VideoAudioSink::reset(uint64_t generation, double mediaSeconds)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (closed || !std::isfinite(mediaSeconds) || mediaSeconds < 0.0)
			return false;
		if (generation < state.generation)
			return true;
		if (source)
		{
			source->setQueuePlaybackAllowed(false);
			source->resetQueue();
			// A device replacement discards all old IDs. Releasing the old owner
			// cannot address IDs in the new context (AudioSource checks generation).
			if (state.deviceGeneration != cocos2d::AudioEngine::getDeviceGeneration())
			{
				source->release();
				source = nullptr;
			}
		}
		const auto underruns = state.underruns;
		state = {};
		state.generation = generation;
		state.deviceGeneration = cocos2d::AudioEngine::getDeviceGeneration();
		state.mediaSeconds = mediaSeconds;
		state.underruns = underruns;
		anchorSeconds = mediaSeconds;
		eos = false;
		started = false;
		rebuffering = true;
		tailActive = false;
		lastSampleTime = lastLatency = lastValidTime = failureSince = 0.0;
		frozenSince = (!allowed || cocos2d::AudioEngine::isSuspended()) ? steadySeconds() : 0.0;
		outputRevision = cocos2d::AudioEngine::getOutputRevision();
		if (!source && !createSourceLocked())
			return false;
		queueGeneration = source->getQueuePlaybackSnapshot().generation;
		source->setQueuePlaybackAllowed(allowed);
		return true;
	}

	void VideoAudioSink::setPlaybackAllowed(bool value)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (closed)
			return;
		// Sample before pausing so the command freezes the actual current clock.
		if (!value && allowed)
			sampleLocked(false);
		allowed = value;
		updateFreezeLocked(!allowed || state.suspended, steadySeconds());
		if (source)
			source->setQueuePlaybackAllowed(value);
		state.playing = value && state.playing;
		if (value)
			sampleLocked();
	}

	bool VideoAudioSink::setGain(float value, bool mute)
	{
		if (!std::isfinite(value))
			return false;
		std::lock_guard<std::mutex> lock(mutex);
		volume = std::max(0.0f, std::min(value, 1.0f));
		muted = mute;
		if (source && !closed)
			source->setQueueGain(muted ? 0.0f : volume);
		return true;
	}

	VideoAudioSink::SubmitResult VideoAudioSink::submit(uint64_t generation, const int16_t* stereo, size_t frames)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (closed)
			return SubmitResult::Closed;
		if (generation != state.generation)
			return SubmitResult::StaleGeneration;
		if (frames > ChunkFrames || (frames && !stereo))
		{
			failLocked("Invalid video PCM chunk");
			return SubmitResult::Error;
		}
		sampleLocked();
		if (state.deviceChanged)
			return SubmitResult::DeviceChanged;
		if (state.failed || !source || eos)
			return SubmitResult::Error;
		if (frames > BudgetFrames - std::min(state.bufferedFrames, BudgetFrames))
			return SubmitResult::Full;
		using Result = cocos2d::AudioSource::QueueSubmitResult;
		const auto result = source->submitQueueData(stereo, frames * 4, queueGeneration, state.deviceGeneration);
		switch (result)
		{
		case Result::Accepted:
			sampleLocked();
			return SubmitResult::Accepted;
		case Result::Full:
			return SubmitResult::Full;
		case Result::DeviceChanged:
			state.deviceChanged = true;
			state.playing = false;
			state.buffering = true;
			return SubmitResult::DeviceChanged;
		case Result::StaleGeneration:
			return SubmitResult::StaleGeneration;
		default:
			failLocked("Video PCM upload or queue submission failed", int(result));
			return SubmitResult::Error;
		}
	}

	void VideoAudioSink::markEndOfStream(uint64_t generation)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (!closed && generation == state.generation)
		{
			eos = true;
			sampleLocked();
		}
	}

	void VideoAudioSink::failLocked(const std::string& message, int code)
	{
		state.failed = true;
		state.error = message;
		state.errorCode = code;
		state.playing = false;
		state.buffering = false;
		if (source)
		{
			source->setQueuePlaybackAllowed(false);
			source->resetQueue();
		}
	}

	void VideoAudioSink::updateFreezeLocked(bool frozen, double now)
	{
		if (frozen)
		{
			if (frozenSince == 0.0)
				frozenSince = now;
		}
		else if (frozenSince != 0.0)
		{
			// Translate existing estimates past the frozen interval. Preserve the
			// raw (possibly before-origin) position: clamping it here would erase
			// the remaining device delay of an extremely short audio tail.
			const double duration = std::max(0.0, now - frozenSince);
			if (lastSampleTime > 0.0)
				lastSampleTime += duration;
			if (tailActive)
				tailSampleTime += duration;
			if (failureSince > 0.0)
				failureSince += duration;
			frozenSince = 0.0;
		}
	}

	VideoAudioSink::Snapshot VideoAudioSink::sampleLocked(bool mayStart)
	{
		if (closed || state.failed || !source)
			return state;
		const auto sample = source->getQueuePlaybackSnapshot();
		const double now = sample.sampledSeconds;
		updateFreezeLocked(!allowed || sample.suspended, now);
		state.suspended = sample.suspended;
		if (state.deviceGeneration != sample.deviceGeneration ||
			sample.stopReason == cocos2d::AudioSource::QueueStopReason::DeviceChanged)
		{
			// Keep the last valid media position as the worker's recovery target.
			state.deviceChanged = true;
			state.playing = false;
			state.buffering = true;
			state.latencyValid = false;
			state.outputLatencySeconds.reset();
			return state;
		}
		if (sample.generation != queueGeneration)
		{
			failLocked("Video audio queue was reset outside its session");
			return state;
		}
		if (sample.outputRevision != outputRevision)
		{
			outputRevision = sample.outputRevision;
			lastSampleTime = lastLatency = 0.0;
			tailActive = false;
		}
		state.submittedFrames = sample.submittedFrames;
		state.residentFrames = sample.residentFrames;
		// Even a failed position query sees newly accepted submissions. Keep
		// their full cost until device consumption is confirmed, so the worker
		// cannot convert another software chunk against a stale low waterline.
		state.bufferedFrames = sample.submittedFrames -
			std::min(state.consumedFrames, sample.submittedFrames);
		if (!sample.clockValid)
		{
			state.clockValid = false;
			if (allowed && !sample.suspended)
			{
				if (failureSince == 0.0)
					failureSince = now;
				else if (now - failureSince > 0.1)
					failLocked("Video audio sample-position query failed for more than 100 ms", sample.error);
			}
			return state;
		}
		failureSince = 0.0;
		state.clockValid = true;
		const double consumed = std::min(double(sample.submittedFrames),
			double(sample.reclaimedFrames) + sample.queueOffsetFrames);
		state.consumedFrames = uint64_t(consumed);
		state.bufferedFrames = sample.submittedFrames - state.consumedFrames;
		const bool natural = sample.state == AL_STOPPED &&
			sample.stopReason == cocos2d::AudioSource::QueueStopReason::Natural;
		state.playing = sample.state == AL_PLAYING;
		const double endpoint = anchorSeconds + double(sample.submittedFrames) / SampleRate;
		state.latencyValid = sample.latencyValid;
		if (sample.latencyValid)
			state.outputLatencySeconds = sample.outputLatencySeconds;
		else
			state.outputLatencySeconds.reset();

		if (natural && started && !rebuffering)
		{
			rebuffering = true;
			if (!eos)
				++state.underruns;
			if (lastSampleTime > 0.0 && lastLatency >= 0.0 && state.mediaSeconds < endpoint)
			{
				tailActive = true;
				tailSampleTime = lastSampleTime;
				tailMediaSeconds = lastValidTime;
				tailEndSeconds = anchorSeconds + double(sample.naturalEndFrames) / SampleRate;
			}
		}
		// Playback permission and device suspension freeze the published clock,
		// including a downstream output tail that cannot physically be recalled.
		if (allowed && !sample.suspended)
		{
			if (state.playing)
			{
				double raw = anchorSeconds + consumed / SampleRate;
				if (sample.latencyValid)
					raw -= sample.outputLatencySeconds;
				const double unclamped = raw;
				raw = std::max(anchorSeconds, std::min(raw, endpoint));
				state.mediaSeconds = std::max(state.mediaSeconds, raw);
				if (sample.latencyValid)
				{
					lastSampleTime = now;
					lastLatency = sample.outputLatencySeconds;
					lastValidTime = unclamped;
				}
				else
					lastSampleTime = 0.0;
				tailActive = false;
			}
			else if (tailActive)
			{
				state.mediaSeconds = std::max(state.mediaSeconds,
					std::min(tailEndSeconds, tailMediaSeconds + std::max(0.0, now - tailSampleTime)));
				if (state.mediaSeconds >= tailEndSeconds)
					tailActive = false;
			}
			else if (natural)
				state.mediaSeconds = std::max(state.mediaSeconds,
					anchorSeconds + double(sample.naturalEndFrames) / SampleRate);
		}
		if (tailActive)
		{
			state.latencyValid = true;
			state.outputLatencySeconds = lastLatency;
		}
		state.ended = eos && state.bufferedFrames == 0 && !tailActive;
		state.buffering = !state.ended && rebuffering;
		if (mayStart && allowed && !sample.suspended && !state.ended && !state.playing &&
			((!rebuffering && sample.state == AL_PAUSED) ||
			 (rebuffering && (state.bufferedFrames >= 4800 || (eos && state.bufferedFrames > 0)))))
		{
			if (sample.state == AL_PAUSED)
			{
				// The host can pause and resume while a worker is inside blocking
				// I/O. Refresh at the actual resume boundary even if no snapshot
				// observed the intermediate suspension notification.
				lastSampleTime = sample.latencyValid ? now : 0.0;
				lastLatency = sample.outputLatencySeconds;
				lastValidTime = anchorSeconds + consumed / SampleRate -
					(sample.latencyValid ? sample.outputLatencySeconds : 0.0);
			}
			if (!source->play())
			{
				// Suspension/rebuild can win the pool lock after this snapshot.
				if (cocos2d::AudioEngine::isSuspended())
					state.suspended = true;
				else if (cocos2d::AudioEngine::getDeviceGeneration() != state.deviceGeneration)
					state.deviceChanged = true;
				else
					failLocked("Could not start the video audio queue");
			}
			else
			{
				started = true;
				rebuffering = false;
				state.playing = true;
				state.buffering = false;
			}
		}
		return state;
	}

	VideoAudioSink::Snapshot VideoAudioSink::snapshot()
	{
		std::lock_guard<std::mutex> lock(mutex);
		return sampleLocked();
	}

	void VideoAudioSink::close()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (closed)
			return;
		closed = true;
		allowed = false;
		if (source)
		{
			source->setQueuePlaybackAllowed(false);
			source->resetQueue();
			source->release();
			source = nullptr;
		}
		state.playing = false;
		state.buffering = false;
	}
}
