#include "VideoPlayer.h"
#include "VideoDecoder.h"
#include "VideoPlayback.h"
#include "base/CCRefPtr.h"
#include "renderer/backend/Device.h"

using namespace video;

namespace
{
	constexpr auto playbackKey = "video.playback";
	constexpr auto removalKey = "video.remove";
}

Player* Player::create(const std::string& path)
{
	auto ret = new (std::nothrow) Player();
	if (ret&&ret->init_(path))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

Player::Player() = default;
Player::~Player() = default;

Decoder* Player::getDecoder() const
{
	return playback ? playback->getDecoder() : nullptr;
}

bool Player::init_(const std::string& path)
{
	playback = VideoPlayback::create(path);
	if (!playback)
		return false;
	const auto size = getDecoder()->getVideoTargetSize();
	auto texture = new (std::nothrow) cocos2d::Texture2D();
	if (!texture)
		return false;
	texture->autorelease();
	cocos2d::backend::TextureDescriptor desc;
	desc.width = size.width;
	desc.height = size.height;
	desc.textureUsage = cocos2d::TextureUsage::WRITE;
	desc.textureFormat = cocos2d::backend::PixelFormat::RGBA8888;
#ifdef CC_VERSION
	texture->updateTextureDescriptor(desc);
#else
	auto tex = cocos2d::backend::Device::getInstance()->newTexture(desc);
	tex->autorelease();
	texture->initWithBackendTexture(tex);
#endif // CC_VERSION
	if (!initWithTexture(texture))
		return false;
	setContentSize(size);
	if (auto frame = playback->getFrame())
		presentFrame(frame);
	return true;
}

void Player::startPlayback()
{
	applyPlaybackUpdate(playback->start());
}

void Player::stopPlayback()
{
	applyPlaybackUpdate(playback->stop());
}

void Player::pausePlayback()
{
	playback->pause();
}

void Player::resumePlayback()
{
	playback->resume();
	syncPlaybackSchedule();
}

void Player::seekFrame(uint32_t frame)
{
	applyPlaybackUpdate(playback->seekFrame(frame));
}

void Player::advance(double seconds)
{
	applyPlaybackUpdate(playback->advance(seconds));
}

void Player::advanceFrame()
{
	applyPlaybackUpdate(playback->advanceFrame());
}

void Player::setPlayMode(PlayMode mode)
{
	playback->setMode(mode);
	syncPlaybackSchedule();
}

void Player::setStep(double seconds)
{
	playback->setStep(seconds);
}

void Player::cleanup()
{
	cocos2d::Sprite::cleanup();
	if (playback)
		playback->cancelAutomaticPlayback();
}

void Player::syncPlaybackSchedule()
{
	if (!playback->wantsTicks())
	{
		unschedule(playbackKey);
		return;
	}
	if (!isScheduled(playbackKey))
	{
		schedule([this](float dt)
		{
			if (isRunning() && playback->getState() == VideoPlayback::State::Playing)
				applyPlaybackUpdate(playback->tick(dt));
		}, playbackKey);
	}
}

void Player::applyPlaybackUpdate(PlaybackUpdate update)
{
	cocos2d::RefPtr<Player> keepAlive(this);
	if (update == PlaybackUpdate::FrameReady)
	{
		unschedule(removalKey);
		presentFrame(playback->getFrame());
	}
	else if (update == PlaybackUpdate::Ended)
	{
		finishPlayback();
	}
	syncPlaybackSchedule();
}

void Player::finishPlayback()
{
	const auto generation = getDecoder()->getGeneration();
	auto callback = videoEndCallback;
	if (callback)
		callback();
	if (autoRemove && getParent() && playback->endedAt(generation))
	{
		// A manual advance may run during scene traversal. Defer removal.
		scheduleOnce([this, generation](float)
		{
			if (autoRemove && playback->endedAt(generation))
				removeFromParentAndCleanup(true);
		}, 0, removalKey);
	}
}

void Player::presentFrame(uint8_t* pixels)
{
	const auto decoder = getDecoder();
	const auto size = decoder->getVideoTargetSize();
	if (!_texture || !pixels)
		return;
	const auto width = _texture->getPixelsWide();
	const auto height = _texture->getPixelsHigh();
	if (size.width != width || size.height != height)
		return;
#ifdef CC_VERSION
	const auto rgba = decoder->getReadFormat() == AV_PIX_FMT_RGBA;
	const size_t dataSize = static_cast<size_t>(width) * height * (rgba ? 4 : 3);
	_texture->updateWithData(pixels, dataSize,
		rgba ? cocos2d::PixelFormat::RGBA8 : cocos2d::PixelFormat::RGB8,
		cocos2d::PixelFormat::RGBA8888, width, height, false);
#else
	_texture->updateWithData(pixels, 0, 0, width, height);
#endif // CC_VERSION
}

void Player::setVideoEndCallback(const std::function<void()>& func)
{
	videoEndCallback = func;
}

void Player::saveCurrentFrame(const std::string& path)
{
	const auto vbuf = playback->getFrame();
	if (!vbuf)
		return;
	const auto decoder = getDecoder();
	auto im = new cocos2d::Image();
	const auto size = decoder->getVideoTargetSize();
	const size_t length = static_cast<size_t>(size.width) * static_cast<size_t>(size.height);
	const size_t dataSize = length * 4;
	std::vector<uint8_t> buffer;
	uint8_t* buf;
	if (decoder->getReadFormat() == AV_PIX_FMT_RGBA)
	{
		buf = vbuf;
	}
	else
	{
		buffer.resize(dataSize);
		buf = buffer.data();
		for (size_t i = 0; i < length; ++i)
		{
			buf[i * 4] = vbuf[i * 3];
			buf[i * 4 + 1] = vbuf[i * 3 + 1];
			buf[i * 4 + 2] = vbuf[i * 3 + 2];
			buf[i * 4 + 3] = 255;
		}
	}
	im->initWithRawData(buf, dataSize,
		size.width, size.height, 32);
	im->saveToFile(path);
	delete im;
}
