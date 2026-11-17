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

cc::IntrusivePtr<Player> Player::create(const std::string& path)
{
	return createWithDecoder(Decoder::create(path).get());
}

cc::IntrusivePtr<Player> Player::createFromStream(cc::io::StreamPtr source)
{
	using namespace cc::io;
	if (!source || !hasCapability(source->capabilities(), Capability::Seek))
		return nullptr;
	return createWithDecoder(Decoder::createFromStream(std::move(source)).get());
}

cc::IntrusivePtr<Player> Player::createAsync(cc::io::StreamPtr source, std::function<void()> cancel)
{
	return createAsync(std::move(source), std::move(cancel), PlaybackOptions{});
}

cc::IntrusivePtr<Player> Player::createAsync(cc::io::StreamPtr source, std::function<void()> cancel,
	const PlaybackOptions& options)
{
	cc::IntrusivePtr player{new (std::nothrow) Player()};
	if (!player)
		return nullptr;
	player->playback = VideoPlayback::createAsync(std::move(source), std::move(cancel), options);
	if (!player->playback || !player->init())
	{
		return nullptr;
	}

	player->playback->setSceneActive(player->isRunning());
	player->syncPlaybackSchedule();
	return player;
}

cc::IntrusivePtr<Player> Player::createWithDecoder(Decoder* source)
{
	if (!source)
		return nullptr;
	cc::IntrusivePtr ret{new (std::nothrow) Player()};
	if (ret && ret->initPlayback(source))
	{
		return ret;
	}
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

bool Player::initVideoTexture(const cc::Size& size, bool replace)
{
	cc::IntrusivePtr texture{new (std::nothrow) cc::Texture2D()};
	if (!texture)
		return false;
	cc::backend::TextureDescriptor desc;
	desc.width = size.width;
	desc.height = size.height;
	desc.textureUsage = cc::TextureUsage::WRITE;
	desc.textureFormat = cc::backend::PixelFormat::RGBA8888;
#ifdef CC_VERSION
	texture->updateTextureDescriptor(desc);
#else
	cc::IntrusivePtr<cc::backend::TextureBackend> tex{cc::backend::Device::getInstance()->newTexture(desc), cc::adopt_ref};
	texture->initWithBackendTexture(tex);
#endif // CC_VERSION
	if (replace)
	{
		setTexture(texture.get());
		setTextureRect(cc::Rect(cc::Vec2::ZERO, texture->getContentSize()));
	}
	else if (!initWithTexture(texture.get()))
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
	cc::Sprite::cleanup();
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
	cc::Sprite::onEnter();
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
	cc::Sprite::onExit();
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
	cc::IntrusivePtr<Player> keepAlive(this);
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

cc::Size Player::getFrameSize() const
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
		rgba ? cc::PixelFormat::RGBA8 : cc::PixelFormat::RGB8,
		cc::PixelFormat::RGBA8888, width, height, false);
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
	cc::Image image;
	if (image.initWithRawData(buf, dataSize, size.width, size.height, 32))
		image.saveToFile(path);
}
