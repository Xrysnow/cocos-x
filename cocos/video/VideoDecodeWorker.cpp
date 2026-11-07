#include "VideoDecodeWorker.h"
#include "VideoCommon.h"
#include "VideoDecoder.h"
#include "VideoAVDecoder.h"
#include "VideoAudioSink.h"
#include "audio/AudioEngine.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <chrono>
#include <deque>
#include <limits>
#include <list>
#include <mutex>
#include <thread>

using namespace video;
using namespace cocos2d;
using namespace cocos2d::io;

namespace
{
	constexpr size_t maxFrames = 3;
	constexpr size_t maxFrameBytes = 64 * 1024 * 1024;
}

struct VideoDecodeWorker::State
{
	struct Seek
	{
		uint64_t generation;
		double seconds;
		std::optional<uint32_t> frame;
	};

	explicit State(std::function<void()> cancel, const PlaybackOptions& options)
		: cancel(std::move(cancel)), audioEnabled(options.audioEnabled), mode(options.mode) {}

	void close()
	{
		if (stop.exchange(true))
			return;
		std::unique_lock control(outputControl);
		std::shared_ptr<VideoAudioSink> output;
		{
			std::lock_guard lock(mutex);
			clearReady();
			output = sink;
		}
		changed.notify_all();
		if (output)
			output->close();
		control.unlock();
		if (cancel && !finished->load())
		{
			try { cancel(); }
			catch (...) { /* The stop flag still interrupts subsequent AVIO calls. */ }
		}
	}

	void clearReady()
	{
		for (const auto slot : ready)
			used[slot] = false;
		ready.clear();
	}

	int freeSlot() const
	{
		for (int i = 0; i < slots; ++i)
			if (!used[i])
				return i;
		return -1;
	}

	void updateMonotonic()
	{
		const auto now = std::chrono::steady_clock::now();
		if (monotonic && monotonicAdvancing)
			info.mediaSeconds += std::chrono::duration<double>(now - monotonicStamp).count();
		monotonicStamp = now;
	}

	std::mutex mutex;
	// Serializes caller controls with initial sink publication. It is never
	// acquired while holding mutex; sink methods likewise run without mutex.
	std::mutex outputControl;
	std::condition_variable changed;
	std::atomic<bool> stop{false};
	const std::shared_ptr<std::atomic<bool>> finished = std::make_shared<std::atomic<bool>>(false);
	const std::function<void()> cancel;
	const bool audioEnabled;
	PlayMode mode;
	bool playbackActive = false;
	float volume = 1.0f;
	bool muted = false;
	double frameRate = 0.0;
	std::shared_ptr<VideoAudioSink> sink;
	bool monotonic = false, monotonicAdvancing = false;
	std::chrono::steady_clock::time_point monotonicStamp = std::chrono::steady_clock::now();
	std::optional<Seek> pendingSeek;
	uint64_t generation = 0;
	bool opened = false;
	bool eof = false;
	AsyncVideoError error = AsyncVideoError::None;
	AsyncVideoSnapshot info;
	int slots = 0;
	std::array<Frame, maxFrames> frames;
	std::array<bool, maxFrames> used{};
	std::deque<int> ready;
};

// A reaper joins completed threads without waiting on the Player's thread.
struct VideoDecodeWorker::Threads
{
	struct Entry
	{
		std::weak_ptr<State> state;
		std::shared_ptr<std::atomic<bool>> finished;
		std::thread thread;
		bool exited = false;
	};

	Threads() : reaper([this] { reap(); }) {}

	~Threads()
	{
		std::list<Entry> remaining;
		{
			std::lock_guard lock(mutex);
			shutdown = true;
			remaining.splice(remaining.end(), workers);
		}
		changed.notify_one();
		for (auto& entry : remaining)
			if (auto state = entry.state.lock())
				state->close();
		for (auto& entry : remaining)
		{
			entry.thread.join();
			entry.finished->store(true);
		}
		reaper.join();
	}

	void reap()
	{
		std::unique_lock lock(mutex);
		for (;;)
		{
			const auto completed = [this] {
				return std::find_if(workers.begin(), workers.end(), [](const Entry& entry) { return entry.exited; });
			};
			changed.wait(lock, [&] { return shutdown || completed() != workers.end(); });
			if (shutdown)
				return;
			const auto it = completed();
			auto entry = std::move(*it);
			workers.erase(it);
			lock.unlock();
			entry.thread.join();
			entry.finished->store(true);
			lock.lock();
		}
	}

	void launch(std::shared_ptr<State> state, StreamPtr source)
	{
		std::lock_guard lock(mutex);
		workers.push_back({state, state->finished, {}});
		auto& entry = workers.back();
		try
		{
			entry.thread = std::thread([this, &entry, state, source = std::move(source)]() mutable {
				useWorkerLogging();
				try { run(*state, std::move(source)); }
				catch (...)
				{
					std::shared_ptr<VideoAudioSink> output;
					{
						std::lock_guard lock(state->mutex);
						state->error = state->opened ? AsyncVideoError::Decode : AsyncVideoError::Open;
						state->info.errorStage = "worker";
						state->info.errorMessage = "Unexpected exception in media worker";
						output = state->sink;
					}
					if (output)
						output->close();
				}
				state.reset();
				std::lock_guard lock(mutex);
				entry.exited = true;
				changed.notify_one();
			});
		}
		catch (...)
		{
			workers.pop_back();
			throw;
		}
	}

	static Threads& instance()
	{
		static Threads threads;
		return threads;
	}

	std::mutex mutex;
	std::condition_variable changed;
	std::list<Entry> workers;
	bool shutdown = false;
	std::thread reaper;
};

VideoDecodeWorker::VideoDecodeWorker(std::shared_ptr<State> state) : state(std::move(state)) {}

std::unique_ptr<VideoDecodeWorker> VideoDecodeWorker::create(StreamPtr source, std::function<void()> cancel)
{
	return create(std::move(source), std::move(cancel), PlaybackOptions{});
}

std::unique_ptr<VideoDecodeWorker> VideoDecodeWorker::create(StreamPtr source, std::function<void()> cancel,
	const PlaybackOptions& options)
{
	if (!source || !source->isOpen() ||
		!hasCapability(source->capabilities(), Capability::Read | Capability::Seek) ||
		(options.audioEnabled && options.mode != PlayMode::REALTIME))
		return nullptr;

	try
	{
		auto state = std::make_shared<State>(std::move(cancel), options);
		auto worker = std::unique_ptr<VideoDecodeWorker>(new VideoDecodeWorker(state));
		Threads::instance().launch(std::move(state), std::move(source));
		return worker;
	}
	catch (...)
	{
		return nullptr;
	}
}

VideoDecodeWorker::~VideoDecodeWorker()
{
	requestClose();
}

void VideoDecodeWorker::requestClose()
{
	state->close();
}

std::shared_ptr<const std::atomic<bool>> VideoDecodeWorker::completion() const
{
	return state->finished;
}

std::optional<uint64_t> VideoDecodeWorker::seek(uint32_t frame)
{
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	uint64_t generation;
	double seconds;
	{
		std::lock_guard lock(state->mutex);
		if (state->stop || state->finished->load() || (state->opened && frame && state->frameRate <= 0.0))
			return {};
		seconds = frame && state->frameRate > 0.0 ? frame / state->frameRate : 0.0;
		if (state->opened && state->info.duration > 0 && seconds > state->info.duration)
			return {};
		generation = ++state->generation;
		state->clearReady();
		state->pendingSeek = State::Seek{generation, seconds, frame};
		state->error = AsyncVideoError::None;
		state->eof = false;
		state->info.seekTargetSeconds = seconds;
		state->info.seekActualSeconds.reset();
		state->info.mediaSeconds = seconds;
		state->info.clockValid = false;
		state->info.bufferedAudioSeconds = 0.0;
		state->monotonic = state->monotonicAdvancing = false;
		state->info.state = AsyncVideoState::Seeking;
		output = state->sink;
	}
	if (output)
		output->reset(generation, seconds);
	state->changed.notify_one();
	return generation;
}

std::optional<uint64_t> VideoDecodeWorker::seekTime(double seconds)
{
	if (!std::isfinite(seconds) || seconds < 0.0 ||
		seconds > static_cast<double>(std::numeric_limits<int64_t>::max() / AV_TIME_BASE))
		return {};
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	uint64_t generation;
	{
		std::lock_guard lock(state->mutex);
		if (state->stop || state->finished->load() || (state->opened && state->info.duration > 0 && seconds > state->info.duration))
			return {};
		generation = ++state->generation;
		state->clearReady();
		state->pendingSeek = State::Seek{generation, seconds, {}};
		state->error = AsyncVideoError::None;
		state->eof = false;
		state->info.seekTargetSeconds = seconds;
		state->info.seekActualSeconds.reset();
		state->info.mediaSeconds = seconds;
		state->info.clockValid = false;
		state->info.bufferedAudioSeconds = 0.0;
		state->monotonic = state->monotonicAdvancing = false;
		state->info.state = AsyncVideoState::Seeking;
		output = state->sink;
	}
	if (output)
		output->reset(generation, seconds);
	state->changed.notify_one();
	return generation;
}

void VideoDecodeWorker::setMode(PlayMode mode)
{
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	{
		std::lock_guard lock(state->mutex);
		state->updateMonotonic();
		state->mode = mode;
		state->monotonicAdvancing = false;
		output = state->sink;
	}
	if (output)
		output->setPlaybackAllowed(false);
	state->changed.notify_one();
}

void VideoDecodeWorker::setPlaybackActive(bool active)
{
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	bool allowed;
	{
		std::lock_guard lock(state->mutex);
		state->updateMonotonic();
		state->playbackActive = active;
		state->monotonicAdvancing = state->monotonic && active &&
			state->mode == PlayMode::REALTIME && !state->info.audioSuspended;
		output = state->sink;
		allowed = active && state->mode == PlayMode::REALTIME && !state->stop;
	}
	if (output)
	{
		output->setPlaybackAllowed(allowed);
		const auto snapshot = output->snapshot();
		std::lock_guard lock(state->mutex);
		if (snapshot.generation == state->generation && state->mode == PlayMode::REALTIME &&
			!state->monotonic && snapshot.clockValid)
			state->info.mediaSeconds = snapshot.mediaSeconds;
	}
	state->changed.notify_one();
}

void VideoDecodeWorker::setAudioVolume(float volume)
{
	if (!std::isfinite(volume))
		return;
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	bool muted;
	{
		std::lock_guard lock(state->mutex);
		state->volume = std::clamp(volume, 0.0f, 1.0f);
		muted = state->muted;
		output = state->sink;
	}
	if (output)
		output->setGain(std::clamp(volume, 0.0f, 1.0f), muted);
}

void VideoDecodeWorker::setAudioMuted(bool muted)
{
	std::lock_guard control(state->outputControl);
	std::shared_ptr<VideoAudioSink> output;
	float volume;
	{
		std::lock_guard lock(state->mutex);
		state->muted = muted;
		volume = state->volume;
		output = state->sink;
	}
	if (output)
		output->setGain(volume, muted);
}

VideoDecodeWorker::Read VideoDecodeWorker::take(std::optional<double> deadline, bool latest)
{
	std::lock_guard lock(state->mutex);
	if (state->stop)
		return {ReadStatus::Closed};
	if (state->ready.empty())
	{
		if (state->error != AsyncVideoError::None)
			return {ReadStatus::Error};
		const bool audible = state->audioEnabled && state->mode == PlayMode::REALTIME;
		const bool complete = state->eof && (!audible || !state->playbackActive || state->info.audioEnded &&
			state->info.clockValid && state->info.mediaSeconds >= state->info.videoEndSeconds);
		return {complete ? ReadStatus::EndOfStream : ReadStatus::Waiting};
	}

	const auto due = [&](int slot) {
		return !deadline || state->frames[slot].seconds <=
			std::nextafter(*deadline, std::numeric_limits<double>::infinity());
	};
	if (!due(state->ready.front()))
		return {ReadStatus::NotDue};

	if (presented >= 0)
		state->used[presented] = false;
	presented = state->ready.front();
	state->ready.pop_front();
	size_t skipped = 0;
	while (latest && !state->ready.empty() && due(state->ready.front()))
	{
		state->used[presented] = false;
		presented = state->ready.front();
		state->ready.pop_front();
		++skipped;
	}
	state->changed.notify_one();
	if (state->audioEnabled && state->mode != PlayMode::REALTIME)
		state->info.mediaSeconds = state->frames[presented].seconds;
	return {ReadStatus::FrameReady, skipped};
}

const VideoDecodeWorker::Frame* VideoDecodeWorker::presentedFrame() const
{
	return presented < 0 ? nullptr : &state->frames[presented];
}

AsyncVideoSnapshot VideoDecodeWorker::snapshot() const
{
	std::lock_guard lock(state->mutex);
	auto info = state->info;
	info.generation = state->generation;
	info.bufferedFrames = state->ready.size();
	info.error = state->error;
	if (state->stop)
		info.state = state->finished->load() ? AsyncVideoState::Closed : AsyncVideoState::Closing;
	else if (info.error != AsyncVideoError::None)
		info.state = AsyncVideoState::Failed;
	else if (state->opened && info.state == AsyncVideoState::Opening)
		info.state = AsyncVideoState::Ready;
	return info;
}

void VideoDecodeWorker::run(State& state, StreamPtr source)
{
	if (state.audioEnabled)
		runWithAudio(state, std::move(source));
	else
		runSilent(state, std::move(source));
}

void VideoDecodeWorker::runSilent(State& state, StreamPtr source)
{
	RefPtr<Decoder> decoder(ReferencedObject<Decoder>{new Decoder()});
	if (state.stop)
		return;
	if (!decoder->openInput(std::move(source), nullptr, false, &state.stop))
	{
		std::lock_guard lock(state.mutex);
		state.error = AsyncVideoError::Open;
		return;
	}
	if (state.stop)
		return;

	const size_t width = decoder->rawWidth;
	const size_t height = decoder->rawHeight;
	// At least two slots are needed because one backs the presented frame.
	constexpr auto maxPixelsPerFrame = (maxFrameBytes / 2 - AV_INPUT_BUFFER_PADDING_SIZE) / 4;
	if (!width || !height || width > maxPixelsPerFrame / height)
	{
		std::lock_guard lock(state.mutex);
		state.error = AsyncVideoError::FrameBudget;
		return;
	}
	const size_t bytes = width * height * 4 + AV_INPUT_BUFFER_PADDING_SIZE;
	const int slots = static_cast<int>(std::min(maxFrames, maxFrameBytes / bytes));
	for (int i = 0; i < slots; ++i)
		state.frames[i].rgba = std::make_unique<uint8_t[]>(bytes);
	decoder->targetSize = Size(static_cast<float>(width), static_cast<float>(height));
	const auto duration = decoder->getContainerDuration();
	const auto audioTracks = decoder->countContainerAudioTracks();
	std::unique_lock lock(state.mutex);
	state.slots = slots;
	state.info.width = static_cast<int>(width);
	state.info.height = static_cast<int>(height);
	state.info.duration = duration;
	state.info.audioTracks = audioTracks;
	state.frameRate = decoder->getVideoFrameRateForPlayer();
	state.info.allocatedFrameBytes = bytes * slots;
	state.opened = true;

	uint64_t generation = 0;
	for (;;)
	{
		state.changed.wait(lock, [&] {
			return state.stop || state.pendingSeek ||
				(!state.eof && state.error == AsyncVideoError::None && state.freeSlot() >= 0);
		});
		if (state.stop)
			break;
		if (state.pendingSeek)
		{
			const auto request = *state.pendingSeek;
			state.pendingSeek.reset();
			lock.unlock();
			double actual = 0.0;
			const bool landed = request.frame ? decoder->seek(*request.frame) : decoder->seekTime(request.seconds, actual);
			lock.lock();
			generation = request.generation;
			if (state.generation == generation && !landed)
				state.error = AsyncVideoError::Seek;
			if (state.generation == generation && landed)
				state.info.state = AsyncVideoState::Ready;
			continue;
		}

		const auto slot = state.freeSlot();
		state.used[slot] = true;
		auto& frame = state.frames[slot];
		lock.unlock();
		auto result = decoder->fillPendingFrame();
		if (result == Decoder::ReadResult::FrameReady && !state.stop)
		{
			uint8_t* data[] = {frame.rgba.get(), nullptr, nullptr, nullptr};
			const int stride[] = {static_cast<int>(width * 4), 0, 0, 0};
			result = decoder->convertPendingFrame(data, stride);
			frame.index = decoder->tell();
			frame.seconds = decoder->getFrameTime();
			frame.duration = decoder->getFrameDuration();
		}
		lock.lock();
		if (state.generation == generation && !state.stop && result == Decoder::ReadResult::FrameReady)
		{
			state.ready.push_back(slot);
			if (!state.info.seekActualSeconds)
				state.info.seekActualSeconds = frame.seconds;
			state.info.state = AsyncVideoState::Ready;
			continue;
		}
		state.used[slot] = false;
		if (state.generation != generation || state.stop)
			continue;
		if (result == Decoder::ReadResult::EndOfStream)
			state.eof = true;
		else
			state.error = AsyncVideoError::Decode;
	}
}

void VideoDecodeWorker::runWithAudio(State& state, StreamPtr source)
{
	VideoAVDecoder decoder;
	const auto failDecoder = [&](uint64_t generation) {
		std::shared_ptr<VideoAudioSink> output;
		{
			std::lock_guard lock(state.mutex);
			if (state.generation != generation || state.stop)
				return;
			state.error = decoder.error() == AsyncVideoError::None ? AsyncVideoError::Decode : decoder.error();
			state.info.errorStage = decoder.errorStage();
			state.info.errorMessage = decoder.errorMessage();
			state.info.backendError = decoder.backendError();
			state.info.audioState = AudioTrackState::Failed;
			state.info.clockValid = false;
			output = state.sink;
		}
		if (output)
			output->setPlaybackAllowed(false);
	};
	if (state.stop || !decoder.open(std::move(source), &state.stop))
	{
		std::lock_guard lock(state.mutex);
		if (!state.stop)
		{
			state.error = decoder.error() == AsyncVideoError::None ? AsyncVideoError::Open : decoder.error();
			state.info.errorStage = decoder.errorStage();
			state.info.errorMessage = decoder.errorMessage();
			state.info.backendError = decoder.backendError();
			state.info.audioState = AudioTrackState::Failed;
		}
		return;
	}
	const auto& metadata = decoder.info();
	const size_t width = static_cast<size_t>(std::max(0, metadata.width));
	const size_t height = static_cast<size_t>(std::max(0, metadata.height));
	constexpr auto maxPixelsPerFrame = (maxFrameBytes / 2 - AV_INPUT_BUFFER_PADDING_SIZE) / 4;
	if (!width || !height || width > maxPixelsPerFrame / height)
	{
		std::lock_guard lock(state.mutex);
		state.error = AsyncVideoError::FrameBudget;
		state.info.errorStage = "video pool";
		state.info.errorMessage = "RGBA pool cannot hold at least two frames within 64 MiB";
		return;
	}
	const size_t frameBytes = width * height * 4 + AV_INPUT_BUFFER_PADDING_SIZE;
	const int slots = static_cast<int>(std::min(maxFrames, maxFrameBytes / frameBytes));
	for (int i = 0; i < slots; ++i)
		state.frames[i].rgba = std::make_unique<uint8_t[]>(frameBytes);
	{
		std::lock_guard lock(state.mutex);
		state.slots = slots;
		state.frameRate = metadata.frameRate;
		state.info.width = metadata.width;
		state.info.height = metadata.height;
		state.info.duration = metadata.duration;
		state.info.audioTracks = metadata.audioTracks;
		state.info.selectedAudioStream = metadata.audioStream;
		state.info.audioState = metadata.audioTracks ? AudioTrackState::Preparing : AudioTrackState::NoTrack;
		state.info.allocatedFrameBytes = frameBytes * slots;
		state.opened = true;
	}

	uint64_t generation = 0;
	double targetSeconds = 0.0;
	uint64_t markedEos = std::numeric_limits<uint64_t>::max();
	auto lastProgress = std::chrono::steady_clock::now();
	auto lastVideoProgress = lastProgress;
	for (;;)
	{
		std::optional<State::Seek> request;
		std::shared_ptr<VideoAudioSink> output;
		PlayMode mode;
		bool active;
		float volume;
		bool muted;
		{
			std::lock_guard lock(state.mutex);
			if (state.stop)
				return;
			if (state.pendingSeek)
			{
				request = state.pendingSeek;
				state.pendingSeek.reset();
			}
			mode = state.mode;
			active = state.playbackActive;
			volume = state.volume;
			muted = state.muted;
			output = state.sink;
		}
		if (request)
		{
			generation = request->generation;
			targetSeconds = request->seconds;
			if (request->frame && *request->frame)
			{
				if (metadata.frameRate <= 0)
				{
					std::lock_guard lock(state.mutex);
					if (state.generation == generation)
					{
						state.error = AsyncVideoError::Seek;
						state.info.errorStage = "seek frame";
						state.info.errorMessage = "Frame seek requires a usable frame-rate estimate";
					}
					continue;
				}
				targetSeconds = *request->frame / metadata.frameRate;
			}
			if (!decoder.seek(targetSeconds, mode == PlayMode::REALTIME))
				failDecoder(generation);
			else
			{
				std::lock_guard lock(state.mutex);
				if (state.generation == generation)
				{
					state.eof = false;
					state.error = AsyncVideoError::None;
					state.info.errorStage.clear();
					state.info.errorMessage.clear();
					state.info.backendError = 0;
					state.info.seekTargetSeconds = targetSeconds;
					state.info.seekActualSeconds.reset();
					state.info.mediaSeconds = targetSeconds;
					state.info.videoEnded = state.info.audioEnded = false;
					state.info.clockValid = false;
					state.info.audioState = !metadata.audioTracks ? AudioTrackState::NoTrack :
						mode == PlayMode::REALTIME ? AudioTrackState::Preparing : AudioTrackState::Disabled;
				}
			}
			markedEos = std::numeric_limits<uint64_t>::max();
			lastProgress = lastVideoProgress = std::chrono::steady_clock::now();
			continue;
		}

		{
			std::unique_lock lock(state.mutex);
			if (state.generation != generation)
				continue;
			if (state.error != AsyncVideoError::None)
			{
				state.changed.wait(lock, [&] { return state.stop || state.pendingSeek; });
				continue;
			}
		}

		const bool realtime = mode == PlayMode::REALTIME;
		const bool suspended = AudioEngine::isSuspended();
		VideoAudioSink::Snapshot audio;
		if (output && realtime)
		{
			audio = output->snapshot();
			if (audio.failed)
			{
				output->setPlaybackAllowed(false);
				std::lock_guard lock(state.mutex);
				if (state.generation == generation)
				{
					state.error = AsyncVideoError::AudioOutput;
					state.info.errorStage = "audio output";
					state.info.backendError = audio.errorCode;
					state.info.errorMessage = audio.error;
					state.info.audioState = AudioTrackState::Failed;
					state.info.clockValid = false;
				}
				continue;
			}
			if (audio.deviceChanged)
			{
				uint64_t recovery = 0;
				{
					std::lock_guard lock(state.mutex);
					if (state.generation == generation && !state.pendingSeek)
					{
						recovery = ++state.generation;
						state.clearReady();
						state.pendingSeek = State::Seek{recovery, audio.mediaSeconds, {}};
						state.info.mediaSeconds = audio.mediaSeconds;
						state.info.clockValid = false;
						state.info.state = AsyncVideoState::Buffering;
						state.monotonic = state.monotonicAdvancing = false;
					}
				}
				if (recovery)
					output->reset(recovery, audio.mediaSeconds);
				continue;
			}
		}

		bool clockValid = false;
		double mediaSeconds = targetSeconds;
		int freeSlot;
		{
			std::lock_guard lock(state.mutex);
			if (state.generation != generation || state.pendingSeek)
				continue;
			state.info.audioSuspended = suspended || audio.suspended;
			if (realtime)
			{
				const bool monotonic = !metadata.audioTracks || decoder.audioEnded() && (!output || audio.ended);
				if (monotonic)
				{
					if (!state.monotonic)
					{
						state.info.mediaSeconds = output ? audio.mediaSeconds : targetSeconds;
						state.monotonicStamp = std::chrono::steady_clock::now();
						state.monotonic = true;
					}
					state.updateMonotonic();
					state.monotonicAdvancing = state.playbackActive && !state.info.audioSuspended;
					state.info.clock = MediaClock::Monotonic;
					state.info.clockValid = true;
					state.info.latencyValid = false;
					state.info.outputLatencySeconds.reset();
					state.info.bufferedAudioSeconds = 0.0;
					state.info.audioEnded = true;
					state.info.audioState = metadata.audioTracks ? AudioTrackState::Ended : AudioTrackState::NoTrack;
				}
				else if (output && audio.generation == generation)
				{
					state.info.mediaSeconds = audio.mediaSeconds;
					state.info.clock = audio.latencyValid ? MediaClock::AudioCalibrated : MediaClock::AudioUncalibrated;
					state.info.clockValid = audio.clockValid;
					state.info.latencyValid = audio.latencyValid;
					state.info.outputLatencySeconds = audio.outputLatencySeconds;
					state.info.deviceGeneration = audio.deviceGeneration;
					state.info.audioUnderruns = audio.underruns;
					state.info.bufferedAudioSeconds = static_cast<double>(audio.bufferedFrames + decoder.audio().frames) / VideoAudioSink::SampleRate;
					state.info.audioState = audio.submittedFrames ? AudioTrackState::Active : AudioTrackState::Preparing;
					state.info.audioEnded = false;
				}
			}
			else
			{
				state.info.clock = MediaClock::Scheduler;
				state.info.clockValid = true;
				state.info.latencyValid = false;
				state.info.outputLatencySeconds.reset();
				state.info.bufferedAudioSeconds = 0.0;
				state.info.audioState = metadata.audioTracks ? AudioTrackState::Disabled : AudioTrackState::NoTrack;
			}
			mediaSeconds = state.info.mediaSeconds;
			clockValid = state.info.clockValid;
			// Keep the newest due frame even while draw/tick is stalled. Compressed
			// references are always decoded; only obsolete RGBA outputs are released.
			if (realtime && clockValid)
				while (state.ready.size() > 1 && state.frames[state.ready[1]].seconds <= mediaSeconds)
				{
					state.used[state.ready.front()] = false;
					state.ready.pop_front();
					++state.info.skippedFrames;
				}
			if (realtime && clockValid && state.freeSlot() < 0 && decoder.hasVideo() &&
				decoder.video().seconds <= mediaSeconds && !state.ready.empty())
			{
				state.used[state.ready.front()] = false;
				state.ready.pop_front();
				++state.info.skippedFrames;
			}
			freeSlot = state.freeSlot();
		}

		bool progress = false;
		if (realtime && decoder.audio().frames)
		{
			if (!output)
			{
				auto candidate = std::make_shared<VideoAudioSink>();
				std::lock_guard control(state.outputControl);
				{
					std::lock_guard lock(state.mutex);
					if (state.generation != generation || state.stop || state.mode != PlayMode::REALTIME)
						continue;
					state.sink = candidate;
					output = candidate;
					active = state.playbackActive;
					volume = state.volume;
					muted = state.muted;
				}
				output->reset(generation, targetSeconds);
				output->setGain(volume, muted);
				output->setPlaybackAllowed(active);
				audio = output->snapshot();
			}
			const auto chunk = decoder.audio();
			const auto result = output->submit(generation, chunk.samples, chunk.frames);
			if (result == VideoAudioSink::SubmitResult::Accepted)
			{
				decoder.consumeAudio();
				progress = true;
			}
			else if (result == VideoAudioSink::SubmitResult::Error)
				continue; // snapshot supplies the detailed output failure.
			else if (result == VideoAudioSink::SubmitResult::StaleGeneration ||
				result == VideoAudioSink::SubmitResult::DeviceChanged || result == VideoAudioSink::SubmitResult::Closed)
				continue;
		}

		if (decoder.hasVideo() && freeSlot >= 0)
		{
			{
				std::lock_guard lock(state.mutex);
				if (state.generation != generation || state.stop)
					continue;
				state.used[freeSlot] = true;
			}
			auto& frame = state.frames[freeSlot];
			const auto video = decoder.video();
			const bool converted = decoder.convertVideo(frame.rgba.get(), static_cast<int>(width * 4));
			frame.index = video.index;
			frame.seconds = video.seconds;
			frame.duration = video.duration;
			decoder.consumeVideo();
			{
				std::lock_guard lock(state.mutex);
				if (converted && state.generation == generation && !state.stop)
				{
					state.ready.push_back(freeSlot);
					if (!state.info.seekActualSeconds)
						state.info.seekActualSeconds = video.seconds;
				}
				else
					state.used[freeSlot] = false;
				freeSlot = state.freeSlot();
			}
			if (!converted)
				failDecoder(generation);
			progress = true;
			lastVideoProgress = std::chrono::steady_clock::now();
		}

		if (output && realtime)
			audio = output->snapshot();
		// One not-yet-submitted chunk shares the same 200 ms allowance as AL.
		const bool wantAudio = realtime && active &&
			(!output || audio.bufferedFrames <= VideoAudioSink::BudgetFrames - VideoAudioSink::ChunkFrames);
		const auto result = decoder.step(freeSlot >= 0, wantAudio);
		if (result == VideoAVDecoder::Step::Error)
		{
			failDecoder(generation);
			continue;
		}
		progress = progress || result == VideoAVDecoder::Step::Progress;
		if (decoder.hasVideo())
			lastVideoProgress = std::chrono::steady_clock::now();
		if (realtime && output && decoder.audioEnded() && markedEos != generation)
		{
			output->markEndOfStream(generation);
			markedEos = generation;
			progress = true;
		}
		const auto now = std::chrono::steady_clock::now();
		{
			std::unique_lock lock(state.mutex);
			if (state.generation != generation)
				continue;
			state.eof = decoder.videoEnded();
			state.info.videoEnded = decoder.videoEnded();
			state.info.videoEndSeconds = decoder.videoEndSeconds();
			state.info.bufferedPacketBytes = decoder.packetBytes();
			state.info.bufferedPackets = decoder.packetCount();
			state.info.timestampEstimated = decoder.timestampEstimated();
			state.info.timestampGapFrames = decoder.gapFrames();
			state.info.timestampOverlapFrames = decoder.overlapFrames();
			const bool preparing = realtime && metadata.audioTracks && !state.info.audioEnded &&
				(!output || audio.buffering || !audio.clockValid);
			if (state.info.state != AsyncVideoState::Seeking || state.info.seekActualSeconds || state.eof)
				state.info.state = preparing ? AsyncVideoState::Buffering : AsyncVideoState::Ready;
			const bool waitingForFutureVideo = decoder.hasVideo() && decoder.video().seconds > mediaSeconds ||
				!state.ready.empty() && state.frames[state.ready.back()].seconds > mediaSeconds ||
				mediaSeconds <= decoder.videoEndSeconds();
			if (progress || !state.playbackActive || state.info.audioSuspended)
				lastProgress = now;
			// A full packet queue can be temporary while already submitted audio
			// advances the clock and releases a future video output. Fail only when
			// neither clock progress nor existing due output can break the impasse.
			const bool audioCanAdvance = state.monotonic || output &&
				(audio.bufferedFrames || audio.clockValid &&
					audio.mediaSeconds < targetSeconds + static_cast<double>(audio.submittedFrames) / VideoAudioSink::SampleRate);
			const bool dueVideoCanConsume = clockValid && !state.ready.empty() &&
				state.frames[state.ready.front()].seconds <= mediaSeconds;
			if (decoder.packetBudgetBlocked() && state.playbackActive && !state.info.audioSuspended &&
				!audioCanAdvance && !dueVideoCanConsume)
			{
				state.error = AsyncVideoError::BufferBudget;
				state.info.errorStage = "demux budget";
				state.info.errorMessage = "Shared compressed packet budget exhausted without consumable output";
				state.info.clockValid = false;
				lock.unlock();
				if (output)
					output->setPlaybackAllowed(false);
				continue;
			}
			const bool stalledInput = result == VideoAVDecoder::Step::NeedInput && now - lastProgress >= std::chrono::seconds(5);
			const bool stalledAudio = realtime && state.playbackActive && !state.info.audioSuspended && output &&
				audio.buffering && !decoder.audioEnded() && now - lastProgress >= std::chrono::seconds(5);
			const bool stalledVideo = realtime && state.playbackActive && !state.info.audioSuspended && !decoder.videoEnded() &&
				!waitingForFutureVideo && now - lastVideoProgress >= std::chrono::seconds(5);
			if (stalledInput || stalledAudio || stalledVideo)
			{
				state.error = AsyncVideoError::Decode;
				state.info.errorStage = stalledVideo ? "video starvation" : "input starvation";
				state.info.errorMessage = "No effective media progress for five seconds";
				state.info.clockValid = false;
				lock.unlock();
				if (output)
					output->setPlaybackAllowed(false);
				continue;
			}
			if (!progress)
			{
				// Active clocks and AudioPool recycling are sampled independently of
				// main-thread drawing. Paused full queues sleep until a control/take.
				if (state.playbackActive && realtime || result == VideoAVDecoder::Step::NeedInput)
					state.changed.wait_for(lock, std::chrono::milliseconds(5));
				else
					state.changed.wait(lock);
			}
		}
	}
}
