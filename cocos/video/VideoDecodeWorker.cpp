#include "VideoDecodeWorker.h"
#include "VideoCommon.h"
#include "VideoDecoder.h"
#include "io/MemoryStream.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
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
		uint32_t frame;
	};

	explicit State(std::function<void()> cancel) : cancel(std::move(cancel)) {}

	void close()
	{
		if (stop.exchange(true))
			return;
		{
			std::lock_guard lock(mutex);
			clearReady();
		}
		changed.notify_all();
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

	std::mutex mutex;
	std::condition_variable changed;
	std::atomic<bool> stop{false};
	const std::shared_ptr<std::atomic<bool>> finished = std::make_shared<std::atomic<bool>>(false);
	const std::function<void()> cancel;
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
					std::lock_guard lock(state->mutex);
					state->error = state->opened ? AsyncVideoError::Decode : AsyncVideoError::Open;
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
	if (!source || !source->isOpen() ||
		!hasCapability(source->capabilities(), Capability::Read | Capability::Seek) ||
		(!cancel && !dynamic_cast<MemoryStream*>(source.get())))
		return nullptr;

	try
	{
		auto state = std::make_shared<State>(std::move(cancel));
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
	std::lock_guard lock(state->mutex);
	if (state->stop || state->finished->load())
		return {};
	state->clearReady();
	state->pendingSeek = State::Seek{++state->generation, frame};
	state->error = AsyncVideoError::None;
	state->eof = false;
	state->changed.notify_one();
	return state->generation;
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
		return {state->eof ? ReadStatus::EndOfStream : ReadStatus::Waiting};
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
	else if (state->opened)
		info.state = AsyncVideoState::Ready;
	return info;
}

void VideoDecodeWorker::run(State& state, StreamPtr source)
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
			const bool landed = decoder->seek(request.frame);
			lock.lock();
			generation = request.generation;
			if (state.generation == generation && !landed)
				state.error = AsyncVideoError::Seek;
			continue;
		}

		const auto slot = state.freeSlot();
		state.used[slot] = true;
		auto& frame = state.frames[slot];
		lock.unlock();
		auto result = decoder->fillPendingFrame();
		if (result == Decoder::ReadResult::FrameReady)
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
