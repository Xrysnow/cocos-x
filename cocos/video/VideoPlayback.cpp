#include "VideoPlayback.h"
#include <cmath>
#include "VideoDecodeWorker.h"
#include <limits>

using namespace video;

VideoPlayback::VideoPlayback(Decoder* source)
	: decoder(source), decoderGeneration(source->getGeneration())
{
}

VideoPlayback::~VideoPlayback() = default;

VideoPlayback::VideoPlayback(std::unique_ptr<VideoDecodeWorker> source)
	: worker(std::move(source)), async(AsyncVideoSnapshot{}), awaitingLanding(true)
{
}

std::unique_ptr<VideoPlayback> VideoPlayback::createAsync(cocos2d::io::StreamPtr source,
	std::function<void()> cancel)
{
	auto worker = VideoDecodeWorker::create(std::move(source), std::move(cancel));
	return worker ? std::unique_ptr<VideoPlayback>(new (std::nothrow) VideoPlayback(std::move(worker))) : nullptr;
}

std::unique_ptr<VideoPlayback> VideoPlayback::create(Decoder* source)
{
	if (!source || !source->setup())
		return nullptr;

	auto playback = std::unique_ptr<VideoPlayback>(new VideoPlayback(source));
	const auto first = source->readFrame(&playback->pixels);
	if (first == Decoder::ReadResult::Error || first == Decoder::ReadResult::EndOfStream)
		return nullptr;
	if (first == Decoder::ReadResult::FrameReady)
		playback->mediaTime = source->getFrameTime();
	return playback;
}

PlaybackUpdate VideoPlayback::start()
{
	if (mode == PlayMode::MANUAL)
		return PlaybackUpdate::NoFrame;
	if (async)
	{
		if (!worker)
			return PlaybackUpdate::NoFrame;
		if (!atStart || state == State::Failed)
		{
			seekFrame(0);
			if (!awaitingLanding)
				return PlaybackUpdate::NoFrame;
		}
		atStart = false;
		state = State::Playing;
		return PlaybackUpdate::NoFrame;
	}

	syncDecoderGeneration();
	if (!decoder->isOpened())
		return PlaybackUpdate::NoFrame;

	auto result = PlaybackUpdate::NoFrame;
	if (!atStart)
	{
		result = seekFrame(0);
		if (result != PlaybackUpdate::FrameReady)
			return result;
	}
	atStart = false;
	state = State::Playing;
	return result;
}

PlaybackUpdate VideoPlayback::stop()
{
	if (mode == PlayMode::MANUAL)
		return PlaybackUpdate::NoFrame;

	cancelAutomaticPlayback();
	if (async)
	{
		if (!atStart)
			return seekFrame(0);
		return PlaybackUpdate::NoFrame;
	}
	syncDecoderGeneration();
	return atStart ? PlaybackUpdate::NoFrame : seekFrame(0);
}

void VideoPlayback::pause()
{
	if (state == State::Playing)
		state = State::Paused;
}

void VideoPlayback::resume()
{
	if (state == State::Paused)
		state = State::Playing;
}

void VideoPlayback::cancelAutomaticPlayback()
{
	if (wantsTicks())
		state = State::Stopped;
}

void VideoPlayback::setMode(PlayMode newMode)
{
	if (mode != newMode)
		pendingManualAdvance = false;
	mode = newMode;
	if (mode == PlayMode::MANUAL)
		cancelAutomaticPlayback();
}

void VideoPlayback::syncDecoderGeneration()
{
	if (decoderGeneration == decoder->getGeneration())
		return;

	decoderGeneration = decoder->getGeneration();
	pixels = nullptr;
	if (state == State::Ended || state == State::Failed)
		state = State::Stopped;
	atStart = false;
	mediaTime = 0.0;
}

bool VideoPlayback::endedAt(uint64_t generation) const
{
	return state == State::Ended && decoderGeneration == generation && generation == getGeneration();
}

uint64_t VideoPlayback::getGeneration() const
{
	return async ? async->generation : decoder->getGeneration();
}

const uint8_t* VideoPlayback::getFrame() const
{
	if (async)
	{
		const auto frame = worker ? worker->presentedFrame() : nullptr;
		return frame ? frame->rgba.get() : nullptr;
	}
	return decoderGeneration == decoder->getGeneration() ? pixels : nullptr;
}

PlaybackUpdate VideoPlayback::seekFrame(uint32_t frame)
{
	if (async)
	{
		if (!worker)
			return PlaybackUpdate::NoFrame;
		const auto request = worker->seek(frame);
		if (!request)
			return PlaybackUpdate::NoFrame;
		async->generation = decoderGeneration = *request;
		async->state = AsyncVideoState::Seeking;
		async->error = AsyncVideoError::None;
		awaitingLanding = true;
		pendingManualAdvance = false;
		atStart = frame == 0;
		if (state == State::Ended || state == State::Failed)
			state = State::Stopped;
		return PlaybackUpdate::NoFrame;
	}
	const auto ok = decoder->seek(frame);
	syncDecoderGeneration();
	if (!ok)
		return PlaybackUpdate::NoFrame;

	uint8_t* decoded = nullptr;
	if (decoder->readFrame(&decoded) != Decoder::ReadResult::FrameReady)
		return PlaybackUpdate::NoFrame;

	pixels = decoded;
	mediaTime = decoder->getFrameTime();
	atStart = frame == 0;
	return PlaybackUpdate::FrameReady;
}

PlaybackUpdate VideoPlayback::tick(double seconds)
{
	if (async)
		return worker ? tickAsync(seconds) : PlaybackUpdate::NoFrame;
	if (state != State::Playing)
		return PlaybackUpdate::NoFrame;
	return advanceImpl(mode == PlayMode::STEP ? step : seconds, mode == PlayMode::FRAME);
}

PlaybackUpdate VideoPlayback::advance(double seconds)
{
	if (async)
		return worker && mode == PlayMode::MANUAL && !awaitingLanding && !pendingManualAdvance
			? readAsync(seconds, false, true) : PlaybackUpdate::NoFrame;
	return mode == PlayMode::MANUAL ? advanceImpl(seconds, false) : PlaybackUpdate::NoFrame;
}

PlaybackUpdate VideoPlayback::advanceFrame()
{
	if (async)
		return worker && mode == PlayMode::MANUAL && !awaitingLanding && !pendingManualAdvance
			? readAsync(0.0, true, true) : PlaybackUpdate::NoFrame;
	return mode == PlayMode::MANUAL ? advanceImpl(0.0, true) : PlaybackUpdate::NoFrame;
}

bool VideoPlayback::needsTick() const
{
	return async ? worker && (state == State::Playing || awaitingLanding || pendingManualAdvance) : wantsTicks();
}

std::optional<AsyncVideoSnapshot> VideoPlayback::getAsyncSnapshot() const
{
	if (!async)
		return async;
	if (!worker)
	{
		auto info = *async;
		if (closeCompletion->load())
		{
			if (info.state == AsyncVideoState::Closing)
				info.state = AsyncVideoState::Closed;
			info.allocatedFrameBytes = 0;
		}
		return info;
	}
	auto info = worker->snapshot();
	info.state = async->state;
	info.error = async->error;
	info.frame = async->frame;
	info.seconds = async->seconds;
	info.skippedFrames = async->skippedFrames;
	return info;
}

void VideoPlayback::closeAsync(AsyncVideoError error)
{
	if (!worker)
		return;
	async = getAsyncSnapshot();
	closeCompletion = worker->completion();
	worker.reset();
	++async->generation;
	async->state = error == AsyncVideoError::None ? AsyncVideoState::Closing : AsyncVideoState::Failed;
	async->error = error;
	async->bufferedFrames = 0;
	state = error == AsyncVideoError::None ? State::Stopped : State::Failed;
}

PlaybackUpdate VideoPlayback::tickAsync(double seconds)
{
	if (awaitingLanding)
	{
		const auto read = worker->take();
		if (read.status == VideoDecodeWorker::ReadStatus::Waiting)
			return PlaybackUpdate::NoFrame;
		awaitingLanding = false;
		if (read.status == VideoDecodeWorker::ReadStatus::FrameReady)
		{
			mediaTime = worker->presentedFrame()->seconds;
			async->state = AsyncVideoState::Ready;
			return PlaybackUpdate::FrameReady;
		}
		return failAsyncRead();
	}
	if (pendingManualAdvance)
		return readAsync(0.0, pendingManualFrame, true);
	if (state != State::Playing)
		return PlaybackUpdate::NoFrame;
	return readAsync(mode == PlayMode::STEP ? step : seconds, mode == PlayMode::FRAME, false);
}

PlaybackUpdate VideoPlayback::readAsync(double seconds, bool nextFrame, bool manual)
{
	using Status = VideoDecodeWorker::ReadStatus;
	if (state == State::Ended || state == State::Failed)
		return PlaybackUpdate::NoFrame;
	const double target = mediaTime + seconds;
	if (!nextFrame && (seconds < 0 || !std::isfinite(seconds) || !std::isfinite(target)))
		return PlaybackUpdate::NoFrame;

	const auto read = worker->take(nextFrame ? std::nullopt : std::optional<double>{target},
		!manual && mode == PlayMode::REALTIME);
	if (!nextFrame && (read.status != Status::Waiting || manual || mode == PlayMode::REALTIME))
		mediaTime = target;
	atStart = false;
	pendingManualAdvance = manual && read.status == Status::Waiting;
	pendingManualFrame = nextFrame;
	switch (read.status)
	{
	case Status::FrameReady:
		async->skippedFrames += read.skipped;
		if (nextFrame)
			mediaTime = worker->presentedFrame()->seconds;
		async->state = AsyncVideoState::Ready;
		return PlaybackUpdate::FrameReady;
	case Status::Waiting:
		async->state = AsyncVideoState::Buffering;
		return PlaybackUpdate::NoFrame;
	case Status::Error:
	case Status::Closed:
		return failAsyncRead();
	case Status::EndOfStream:
		if (!nextFrame)
		{
			const auto frame = worker->presentedFrame();
			if (frame && std::nextafter(mediaTime, std::numeric_limits<double>::infinity()) < frame->seconds + frame->duration)
			{
				async->state = AsyncVideoState::Ready;
				return PlaybackUpdate::NoFrame;
			}
		}
		state = State::Ended;
		async->state = AsyncVideoState::Ended;
		return PlaybackUpdate::Ended;
	case Status::NotDue:
		async->state = AsyncVideoState::Ready;
		return PlaybackUpdate::NoFrame;
	}
	return PlaybackUpdate::NoFrame;
}

PlaybackUpdate VideoPlayback::failAsyncRead()
{
	state = State::Failed;
	async->state = AsyncVideoState::Failed;
	const auto workerError = worker->snapshot().error;
	async->error = workerError == AsyncVideoError::None ? AsyncVideoError::Decode : workerError;
	return PlaybackUpdate::Error;
}

void VideoPlayback::onFramePresented()
{
	if (!worker)
		return;
	const auto frame = worker->presentedFrame();
	async->frame = frame->index;
	async->seconds = frame->seconds;
}

PlaybackUpdate VideoPlayback::advanceImpl(double seconds, bool nextFrame)
{
	syncDecoderGeneration();
	if (state == State::Ended || state == State::Failed)
		return PlaybackUpdate::NoFrame;

	if (!nextFrame)
	{
		const auto target = mediaTime + seconds;
		if (seconds < 0 || !std::isfinite(seconds) || !std::isfinite(target))
			return PlaybackUpdate::NoFrame;
		mediaTime = target;
	}

	atStart = false;
	uint8_t* decoded = nullptr;
	switch (nextFrame ? decoder->readFrame(&decoded) : decoder->readFrameAt(mediaTime, &decoded))
	{
	case Decoder::ReadResult::FrameReady:
		pixels = decoded;
		if (nextFrame)
			mediaTime = decoder->getFrameTime();
		return PlaybackUpdate::FrameReady;
	case Decoder::ReadResult::EndOfStream:
		state = State::Ended;
		return PlaybackUpdate::Ended;
	case Decoder::ReadResult::Error:
		pixels = nullptr;
		state = State::Failed;
		return PlaybackUpdate::Error;
	case Decoder::ReadResult::NeedInput:
		return PlaybackUpdate::NoFrame;
	}
	return PlaybackUpdate::Error;
}
