#include "VideoPlayback.h"
#include <cmath>
#include "VideoDecodeWorker.h"
#include "VideoCommon.h"
#include <algorithm>
#include <limits>

using namespace video;

VideoPlayback::VideoPlayback(Decoder* source)
	: decoder(source), decoderGeneration(source->getGeneration())
{
}

VideoPlayback::~VideoPlayback() = default;

VideoPlayback::VideoPlayback(std::unique_ptr<VideoDecodeWorker> source, const PlaybackOptions& options)
	: worker(std::move(source)), async(AsyncVideoSnapshot{}), awaitingLanding(true),
	  audioEnabled(options.audioEnabled), mode(options.mode)
{
}

std::unique_ptr<VideoPlayback> VideoPlayback::createAsync(cocos2d::io::StreamPtr source,
	std::function<void()> cancel)
{
	return createAsync(std::move(source), std::move(cancel), PlaybackOptions{});
}

std::unique_ptr<VideoPlayback> VideoPlayback::createAsync(cocos2d::io::StreamPtr source,
	std::function<void()> cancel, const PlaybackOptions& options)
{
	if (options.audioEnabled && options.mode != PlayMode::REALTIME)
	{
		VERRO("audio playback requires REALTIME mode");
		return nullptr;
	}
	auto worker = VideoDecodeWorker::create(std::move(source), std::move(cancel), options);
	return worker ? std::unique_ptr<VideoPlayback>(new (std::nothrow) VideoPlayback(std::move(worker), options)) : nullptr;
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
		syncPlaybackPermission();
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
	syncPlaybackPermission();
}

void VideoPlayback::resume()
{
	if (state == State::Paused)
		state = State::Playing;
	syncPlaybackPermission();
}

void VideoPlayback::cancelAutomaticPlayback()
{
	if (wantsTicks())
		state = State::Stopped;
	syncPlaybackPermission();
}

void VideoPlayback::setMode(PlayMode newMode)
{
	if (mode == newMode)
		return;
	if (newMode != PlayMode::STEP && newMode != PlayMode::REALTIME &&
		newMode != PlayMode::FRAME && newMode != PlayMode::MANUAL)
		return;
	const bool rebaseAudio = audioEnabled && (mode == PlayMode::REALTIME || newMode == PlayMode::REALTIME);
	if (worker && usesDeviceClock())
	{
		const auto info = worker->snapshot();
		if (info.clockValid)
			mediaTime = info.mediaSeconds;
	}
	pendingManualAdvance = false;
	mode = newMode;
	if (mode == PlayMode::MANUAL)
		cancelAutomaticPlayback();
	if (worker)
	{
		worker->setMode(mode);
		if (rebaseAudio)
			seekTime(mediaTime);
		syncPlaybackPermission();
	}
}

void VideoPlayback::syncPlaybackPermission()
{
	if (worker)
		worker->setPlaybackActive(state == State::Playing && sceneActive);
}

void VideoPlayback::setSceneActive(bool active)
{
	sceneActive = active;
	syncPlaybackPermission();
}

void VideoPlayback::setAudioVolume(float volume)
{
	if (!std::isfinite(volume))
		return;
	audioVolume = std::clamp(volume, 0.0f, 1.0f);
	if (worker)
		worker->setAudioVolume(audioVolume);
}

void VideoPlayback::setAudioMuted(bool muted)
{
	audioMuted = muted;
	if (worker)
		worker->setAudioMuted(muted);
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
	return worker ? worker->snapshot().generation : async ? async->generation : decoder->getGeneration();
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
		beginAsyncSeek(*request, frame == 0);
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

void VideoPlayback::beginAsyncSeek(uint64_t generation, bool atOrigin)
{
	async->generation = decoderGeneration = generation;
	async->state = AsyncVideoState::Seeking;
	async->error = AsyncVideoError::None;
	awaitingLanding = true;
	pendingManualAdvance = false;
	atStart = atOrigin;
	if (state == State::Ended || state == State::Failed)
		state = State::Stopped;
	syncPlaybackPermission();
}

bool VideoPlayback::seekTime(double seconds)
{
	if (!std::isfinite(seconds) || seconds < 0.0)
		return false;
	if (async)
	{
		if (!worker)
			return false;
		const auto request = worker->seekTime(seconds);
		if (!request)
			return false;
		mediaTime = seconds;
		beginAsyncSeek(*request, seconds == 0.0);
		return true;
	}
	const double duration = decoder->getContainerDuration();
	if (duration > 0.0 && seconds > duration)
		return false;
	double actual = 0.0;
	const bool landed = decoder->seekTime(seconds, actual);
	syncDecoderGeneration();
	if (!landed)
	{
		// Decoder's legacy seek contract requires a landing frame. The time-based
		// playback API also accepts a verified seek to the known end of the file.
		uint8_t* unused = nullptr;
		if (duration <= 0.0 || seconds != duration ||
			decoder->readFrame(&unused) != Decoder::ReadResult::EndOfStream)
			return false;
		pixels = nullptr;
		mediaTime = seconds;
		atStart = false;
		return true;
	}
	uint8_t* decoded = nullptr;
	if (decoder->readFrame(&decoded) != Decoder::ReadResult::FrameReady)
		return false;
	pixels = decoded;
	mediaTime = actual;
	atStart = seconds == 0.0;
	return true;
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
	if (info.error == AsyncVideoError::None && info.generation == async->generation)
	{
		if (info.state != AsyncVideoState::Opening && info.state != AsyncVideoState::Seeking &&
			!(usesDeviceClock() && info.state == AsyncVideoState::Buffering) &&
			info.state != AsyncVideoState::Closing && info.state != AsyncVideoState::Closed)
			info.state = async->state;
		if (async->error != AsyncVideoError::None)
			info.error = async->error;
	}
	info.frame = async->frame;
	info.seconds = async->seconds;
	info.skippedFrames += async->skippedFrames;
	if (!usesDeviceClock())
	{
		info.mediaSeconds = mediaTime;
		info.clock = MediaClock::Scheduler;
		info.clockValid = true;
	}
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
	async->bufferedAudioSeconds = 0;
	async->clockValid = false;
	state = error == AsyncVideoError::None ? State::Stopped : State::Failed;
}

PlaybackUpdate VideoPlayback::tickAsync(double seconds)
{
	const auto info = worker->snapshot();
	if (info.error != AsyncVideoError::None)
		return failAsyncRead();
	// Device recovery can replace a decode generation without a public seek.
	if (info.generation != async->generation)
	{
		async->generation = decoderGeneration = info.generation;
		awaitingLanding = true;
		pendingManualAdvance = false;
		mediaTime = info.mediaSeconds;
	}
	if (usesDeviceClock() && info.clockValid)
		mediaTime = info.mediaSeconds;
	if (awaitingLanding)
	{
		const bool timed = usesDeviceClock() && state == State::Playing;
		if (timed && !info.clockValid)
			return PlaybackUpdate::NoFrame;
		const auto read = worker->take(timed ? std::optional<double>{mediaTime} : std::nullopt);
		if (read.status == VideoDecodeWorker::ReadStatus::Waiting ||
			read.status == VideoDecodeWorker::ReadStatus::NotDue)
			return PlaybackUpdate::NoFrame;
		awaitingLanding = false;
		if (read.status == VideoDecodeWorker::ReadStatus::FrameReady)
		{
			if (!usesDeviceClock())
				mediaTime = worker->presentedFrame()->seconds;
			async->state = AsyncVideoState::Ready;
			return PlaybackUpdate::FrameReady;
		}
		if (read.status == VideoDecodeWorker::ReadStatus::EndOfStream)
		{
			if (state == State::Playing)
			{
				state = State::Ended;
				async->state = AsyncVideoState::Ended;
				syncPlaybackPermission();
				return PlaybackUpdate::Ended;
			}
			async->state = AsyncVideoState::Ready;
			return PlaybackUpdate::NoFrame;
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
	const bool deviceClock = usesDeviceClock() && !manual;
	const auto info = worker->snapshot();
	if (info.error != AsyncVideoError::None)
		return failAsyncRead();
	if (deviceClock && !info.clockValid)
		return PlaybackUpdate::NoFrame;
	const double target = deviceClock ? info.mediaSeconds : mediaTime + seconds;
	if (!nextFrame && (!std::isfinite(target) || (!deviceClock && (seconds < 0 || !std::isfinite(seconds)))))
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
		// A video tail waiting for audio is normal playback, not audio starvation.
		async->state = deviceClock && info.videoEnded && info.state != AsyncVideoState::Buffering
			? AsyncVideoState::Ready : AsyncVideoState::Buffering;
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
		syncPlaybackPermission();
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
	syncPlaybackPermission();
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
