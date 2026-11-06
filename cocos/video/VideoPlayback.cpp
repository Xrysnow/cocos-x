#include "VideoPlayback.h"
#include <cmath>

using namespace video;

VideoPlayback::VideoPlayback(Decoder* source)
	: decoder(source), decoderGeneration(source->getGeneration())
{
}

VideoPlayback::~VideoPlayback() = default;

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
	return state == State::Ended && decoderGeneration == generation &&
		generation == decoder->getGeneration();
}

uint8_t* VideoPlayback::getFrame() const
{
	return decoderGeneration == decoder->getGeneration() ? pixels : nullptr;
}

PlaybackUpdate VideoPlayback::seekFrame(uint32_t frame)
{
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
	if (state != State::Playing)
		return PlaybackUpdate::NoFrame;
	return advanceImpl(mode == PlayMode::STEP ? step : seconds, mode == PlayMode::FRAME);
}

PlaybackUpdate VideoPlayback::advance(double seconds)
{
	return mode == PlayMode::MANUAL ? advanceImpl(seconds, false) : PlaybackUpdate::NoFrame;
}

PlaybackUpdate VideoPlayback::advanceFrame()
{
	return mode == PlayMode::MANUAL ? advanceImpl(0.0, true) : PlaybackUpdate::NoFrame;
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
