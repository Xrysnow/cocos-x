#pragma once
#include "VideoDecoder.h"
#include "2d/CCSprite.h"
#include <functional>

namespace video
{
	class CC_DLL Player : public cocos2d::Sprite
	{
	public:
		enum class PlayMode
		{
			/** step a const time per frame */
			STEP,
			/** realtime time -> video time, not recommended */
			REALTIME,
			/** game frame -> video frame */
			FRAME,
			/** advance explicitly */
			MANUAL,
		};
		static Player* create(const std::string& path);
	protected:
		bool init_(const std::string& path);
	public:
		void vplay();
		void vstop();
		void vpause();
		void vresume();
		/** Seek to a frame using the decoder's frame-rate estimate. */
		void seek(uint32_t frame);
		/** In MANUAL mode, advance by a finite nonnegative number of seconds. */
		void advance(double dt);
		/** In MANUAL mode, try to publish the next decoded frame. */
		void advanceFrame();
		/** Compatibility for MANUAL mode: negative dt requests the next frame. */
		void update(float dt) override;
		void cleanup() override;

		/** see PlayMode */
		void setPlayMode(PlayMode m);
		/** used for PlayMode::STEP mode */
		void setStep(double v) { step = v; }
		/** auto invoke removeFromParentAndCleanup when finished */
		void setAutoRemove(bool b) { autoRemove = b; }
		/** set callback when finished */
		void setVideoEndCallback(const std::function<void()>& func);
		/** save current frame to file */
		void saveCurrentFrame(const std::string& path);

		Decoder* getDecoder() const { return decoder; }

	protected:
		bool seekFrame(uint32_t frame);
		void syncDecoderGeneration();
		void presentFrame(uint8_t* pixels);
		void finishPlayback();
		Decoder* decoder = nullptr;
		uint8_t* vbuf = nullptr;

		double currentTime = 0.0;
		double step = 1.0 / 60;
		bool autoUpdate = false;
		bool autoRemove = false;
		bool isPlaying = false;
		bool finished = false;
		bool atStart = false;
		uint64_t decoderGeneration = 0;
		PlayMode mode = PlayMode::STEP;

		std::function<void()> videoEndCallback;

		Player();
		~Player() override;

	private:
		void schedulePlayback();
		void advancePlayback(double dt, bool nextFrame);
	};
}
