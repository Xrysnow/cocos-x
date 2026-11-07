#pragma once
#include "VideoPlayMode.h"
#include "VideoAsync.h"
#include "2d/CCSprite.h"
#include "io/Stream.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace video
{
	class Decoder;
	class VideoPlayback;
	enum class PlaybackUpdate;

	class CC_DLL Player : public cocos2d::Sprite
	{
	public:
		static Player* create(const std::string& path);
		// The input must support seeking and have a dedicated cursor at offset zero.
		static Player* createFromStream(cocos2d::io::StreamPtr source);
		// Shutdown cooperatively waits for the current stream operation to return.
		// An optional prompt, thread-safe cancel hook can unblock that operation.
		static Player* createAsync(cocos2d::io::StreamPtr source, std::function<void()> cancel = {});
		std::optional<AsyncVideoSnapshot> getAsyncSnapshot() const;
		void closeAsync();

		void startPlayback();
		void stopPlayback();
		void pausePlayback();
		void resumePlayback();
		/** Seek to a frame using the decoder's frame-rate estimate. */
		void seekFrame(uint32_t frame);
		/** In MANUAL mode, advance by a finite nonnegative number of seconds. */
		void advance(double dt);
		/** In MANUAL mode, try to publish the next decoded frame. */
		void advanceFrame();
		void cleanup() override;

		/** see PlayMode */
		void setPlayMode(PlayMode m);
		/** used for PlayMode::STEP mode */
		void setStep(double seconds);
		/** auto invoke removeFromParentAndCleanup when finished */
		void setAutoRemove(bool b) { autoRemove = b; }
		/** set callback when finished */
		void setVideoEndCallback(const std::function<void()>& func);
		/** save current frame to file */
		void saveCurrentFrame(const std::string& path);

		// Async players expose a snapshot instead of a worker-owned decoder.
		Decoder* getDecoder() const;

	protected:
		Player();
		~Player() override;

	private:
		static Player* createWithDecoder(Decoder* source);
		bool initPlayback(Decoder* source);
		bool initVideoTexture(const cocos2d::Size& size, bool replace);
		cocos2d::Size getFrameSize() const;
		void applyPlaybackUpdate(PlaybackUpdate update);
		void syncPlaybackSchedule();
		bool presentFrame(const uint8_t* pixels);
		void finishPlayback();

		std::unique_ptr<VideoPlayback> playback;
		bool autoRemove = false;
		bool asyncTextureReady = false;
		std::function<void()> videoEndCallback;
	};
}
