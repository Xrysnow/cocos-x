#include "VideoPlayer.h"
#include "base/CCRefPtr.h"
#include "renderer/backend/Device.h"
#include <cmath>

using namespace video;

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

Player::Player()
{
}

Player::~Player()
{
	CC_SAFE_RELEASE_NULL(decoder);
}

bool Player::init_(const std::string& path)
{
	decoder = Decoder::create(path);
	if (!decoder)
		return false;
	decoder->retain();
	if (!decoder->setup())
		return false;
	const auto size = decoder->getVideoTargetSize();
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
	decoderGeneration = decoder->getGeneration();
	uint8_t* pixels = nullptr;
	const auto first = decoder->readFrame(&pixels);
	if (first == Decoder::ReadResult::Error || first == Decoder::ReadResult::EndOfStream)
		return false;
	if (first == Decoder::ReadResult::FrameReady)
	{
		presentFrame(pixels);
		currentTime = decoder->getFrameTime();
	}
	atStart = true;
	return true;
}

void Player::vplay()
{
	if (mode == PlayMode::MANUAL)
		return;
	syncDecoderGeneration();
	if (!decoder->isOpened() || (!atStart && !seekFrame(0)))
		return;
	atStart = false;
	if (!isPlaying && mode == PlayMode::REALTIME)
		scheduleUpdate();
	isPlaying = true;
	autoUpdate = true;
}

void Player::vstop()
{
	if (mode == PlayMode::MANUAL)
		return;
	if (mode == PlayMode::REALTIME)
		unscheduleUpdate();
	isPlaying = false;
	autoUpdate = false;
	syncDecoderGeneration();
	if (!atStart)
		seekFrame(0);
}

void Player::vpause()
{
	if (mode == PlayMode::MANUAL)
		return;
	if (isPlaying&&autoUpdate)
	{
		if (mode == PlayMode::REALTIME)
			unscheduleUpdate();
		isPlaying = false;
	}
}

void Player::vresume()
{
	if (mode == PlayMode::MANUAL)
		return;
	if (!isPlaying&&autoUpdate)
	{
		if (mode == PlayMode::REALTIME)
			scheduleUpdate();
		isPlaying = true;
	}
}

void Player::syncDecoderGeneration()
{
	if (decoderGeneration == decoder->getGeneration())
		return;
	decoderGeneration = decoder->getGeneration();
	vbuf = nullptr;
	finished = false;
	atStart = false;
	currentTime = 0.0;
	unschedule("video.remove");
}

bool Player::seekFrame(uint32_t frame)
{
	const auto ok = decoder->seek(frame);
	syncDecoderGeneration();
	if (!ok)
		return false;
	uint8_t* pixels = nullptr;
	if (decoder->readFrame(&pixels) != Decoder::ReadResult::FrameReady)
		return false;
	presentFrame(pixels);
	currentTime = decoder->getFrameTime();
	atStart = frame == 0;
	return true;
}

void Player::seek(uint32_t frame)
{
	seekFrame(frame);
}

void Player::update(float dt)
{
	cocos2d::RefPtr<Player> keepAlive(this);
	cocos2d::Sprite::update(dt);
	syncDecoderGeneration();
	if (finished || !std::isfinite(dt))
		return;
	atStart = false;
	uint8_t* pixels = nullptr;
	if (dt >= 0)
		currentTime += dt;
	const auto result = dt < 0
		? decoder->readFrame(&pixels)
		: decoder->readFrameAt(currentTime, &pixels);
	switch (result)
	{
	case Decoder::ReadResult::FrameReady:
		presentFrame(pixels);
		if (dt < 0)
			currentTime = decoder->getFrameTime();
		break;
	case Decoder::ReadResult::EndOfStream:
		finishPlayback();
		break;
	case Decoder::ReadResult::Error:
		vbuf = nullptr;
		finished = true;
		isPlaying = false;
		autoUpdate = false;
		if (mode == PlayMode::REALTIME)
			unscheduleUpdate();
		break;
	case Decoder::ReadResult::NeedInput:
		break;
	}
}

void Player::finishPlayback()
{
	finished = true;
	isPlaying = false;
	autoUpdate = false;

	const auto generation = decoderGeneration;
	auto callback = videoEndCallback;
	if (callback)
		callback();
	if (!isPlaying && mode == PlayMode::REALTIME)
		unscheduleUpdate();
	if (autoRemove && getParent() && finished && generation == decoder->getGeneration())
	{
		// Removal during visit could invalidate the parent's child iteration.
		scheduleOnce([this, generation](float)
		{
			if (finished && generation == decoder->getGeneration())
				removeFromParentAndCleanup(true);
		}, 0, "video.remove");
	}
}

void Player::setPlayMode(PlayMode m)
{
	if (mode == m)
		return;
	if (mode == PlayMode::REALTIME)
		unscheduleUpdate();
	mode = m;
	if (mode == PlayMode::REALTIME && isPlaying)
		scheduleUpdate();
	if (mode == PlayMode::MANUAL)
	{
		isPlaying = false;
		autoUpdate = false;
	}
}

void Player::presentFrame(uint8_t* pixels)
{
	const auto size = decoder->getVideoTargetSize();
	if (!_texture)
		return;
	const auto width = _texture->getPixelsWide();
	const auto height = _texture->getPixelsHigh();
	if (size.width != width || size.height != height)
		return;
	vbuf = pixels;
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

void Player::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	if (!_texture)
		return;
	cocos2d::RefPtr<Player> keepAlive(this);
	const auto wasRunning = isRunning();
	if (isPlaying)
	{
		if (mode == PlayMode::STEP)
			update(step);
		else if (mode == PlayMode::FRAME)
			update(-1);
	}
	if (!wasRunning || isRunning())
		cocos2d::Sprite::draw(renderer, transform, flags);
}

void Player::setVideoEndCallback(const std::function<void()>& func)
{
	videoEndCallback = func;
}

void Player::saveCurrentFrame(const std::string& path)
{
	if (!vbuf || decoderGeneration != decoder->getGeneration())
		return;
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
