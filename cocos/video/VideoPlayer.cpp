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
	return createWithDecoder(Decoder::create(path));
}

Player* Player::createFromStream(cocos2d::io::StreamPtr source)
{
	using namespace cocos2d::io;
	if (!source || !hasCapability(source->capabilities(), Capability::Seek))
		return nullptr;
	return createWithDecoder(Decoder::createFromStream(std::move(source)));
}

Player* Player::createAsync(cocos2d::io::StreamPtr source, std::function<void()> cancel)
{
	return createAsync(std::move(source), std::move(cancel), PlaybackOptions{});
}

Player* Player::createAsync(cocos2d::io::StreamPtr source, std::function<void()> cancel,
	const PlaybackOptions& options)
{
	auto player = new (std::nothrow) Player();
	if (!player)
		return nullptr;
	player->playback = VideoPlayback::createAsync(std::move(source), std::move(cancel), options);
	if (!player->playback || !player->init())
	{
		delete player;
		return nullptr;
	}
	player->autorelease();
	player->playback->setSceneActive(player->isRunning());
	player->syncPlaybackSchedule();
	return player;
}

Player* Player::createWithDecoder(Decoder* source)
{
	if (!source)
		return nullptr;
	auto ret = new (std::nothrow) Player();
	if (ret && ret->initPlayback(source))
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

std::optional<AsyncVideoSnapshot> Player::getAsyncSnapshot() const
{
	return playback ? playback->getAsyncSnapshot() : std::nullopt;
}

void Player::closeAsync()
{
	if (playback && !getDecoder())
	{
		playback->closeAsync();
		unschedule(removalKey);
		syncPlaybackSchedule();
	}
}

bool Player::initPlayback(Decoder* source)
{
	playback = VideoPlayback::create(source);
	if (!playback)
		return false;
	if (!initVideoTexture(getFrameSize(), false))
		return false;
	if (auto frame = playback->getFrame())
		presentFrame(frame);
	return true;
}

bool Player::initVideoTexture(const cocos2d::Size& size, bool replace)
{
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
	if (replace)
	{
		setTexture(texture);
		setTextureRect(cocos2d::Rect(cocos2d::Vec2::ZERO, texture->getContentSize()));
	}
	else if (!initWithTexture(texture))
		return false;
	setContentSize(size);
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
	syncPlaybackSchedule();
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

bool Player::seekTime(double seconds)
{
	if (!playback->seekTime(seconds))
		return false;
	if (getDecoder() && playback->getFrame())
		applyPlaybackUpdate(PlaybackUpdate::FrameReady);
	else
	{
		unschedule(removalKey);
		syncPlaybackSchedule();
	}
	return true;
}

void Player::setAudioVolume(float volume)
{
	playback->setAudioVolume(volume);
}

float Player::getAudioVolume() const
{
	return playback->getAudioVolume();
}

void Player::setAudioMuted(bool muted)
{
	playback->setAudioMuted(muted);
}

bool Player::isAudioMuted() const
{
	return playback->isAudioMuted();
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
	{
		if (getDecoder())
			playback->cancelAutomaticPlayback();
		else
			playback->closeAsync();
	}
}

void Player::onEnter()
{
	cocos2d::Sprite::onEnter();
	if (playback)
	{
		playback->setSceneActive(true);
		syncPlaybackSchedule();
	}
}

void Player::onExit()
{
	if (playback)
		playback->setSceneActive(false);
	cocos2d::Sprite::onExit();
}

void Player::syncPlaybackSchedule()
{
	if (!playback->needsTick())
	{
		unschedule(playbackKey);
		return;
	}
	if (!isScheduled(playbackKey))
	{
		schedule([this](float dt)
		{
			if (isRunning() && (!getDecoder() || playback->getState() == VideoPlayback::State::Playing))
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
		if (presentFrame(playback->getFrame()))
			playback->onFramePresented();
		else
			playback->closeAsync(AsyncVideoError::Present);
	}
	else if (update == PlaybackUpdate::Ended)
	{
		finishPlayback();
	}
	syncPlaybackSchedule();
}

void Player::finishPlayback()
{
	const auto generation = playback->getGeneration();
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

cocos2d::Size Player::getFrameSize() const
{
	if (const auto decoder = getDecoder())
		return decoder->getVideoTargetSize();
	const auto async = getAsyncSnapshot();
	return {static_cast<float>(async->width), static_cast<float>(async->height)};
}

bool Player::presentFrame(const uint8_t* pixels)
{
	const auto decoder = getDecoder();
	const auto size = getFrameSize();
	if (!decoder && !asyncTextureReady)
	{
		asyncTextureReady = initVideoTexture(size, true);
		if (!asyncTextureReady)
			return false;
	}
	if (!_texture || !pixels)
		return false;
	const auto width = _texture->getPixelsWide();
	const auto height = _texture->getPixelsHigh();
	if (size.width != width || size.height != height)
		return false;
#ifdef CC_VERSION
	const auto rgba = !decoder || decoder->getReadFormat() == AV_PIX_FMT_RGBA;
	const size_t dataSize = static_cast<size_t>(width) * height * (rgba ? 4 : 3);
	return _texture->updateWithData(pixels, dataSize,
		rgba ? cocos2d::PixelFormat::RGBA8 : cocos2d::PixelFormat::RGB8,
		cocos2d::PixelFormat::RGBA8888, width, height, false);
#else
	_texture->updateWithData(const_cast<uint8_t*>(pixels), 0, 0, width, height);
	return true;
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
	const auto size = getFrameSize();
	const size_t length = static_cast<size_t>(size.width) * static_cast<size_t>(size.height);
	const size_t dataSize = length * 4;
	std::vector<uint8_t> buffer;
	const uint8_t* buf = vbuf;
	if (decoder && decoder->getReadFormat() != AV_PIX_FMT_RGBA)
	{
		buffer.resize(dataSize);
		for (size_t i = 0; i < length; ++i)
		{
			buffer[i * 4] = vbuf[i * 3];
			buffer[i * 4 + 1] = vbuf[i * 3 + 1];
			buffer[i * 4 + 2] = vbuf[i * 3 + 2];
			buffer[i * 4 + 3] = 255;
		}
		buf = buffer.data();
	}
	cocos2d::Image image;
	if (image.initWithRawData(buf, dataSize, size.width, size.height, 32))
		image.saveToFile(path);
}
