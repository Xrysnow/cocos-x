#pragma once
#include "VideoCommon.h"
#include "VideoStream.h"
#include "FFDemuxer.h"
#include "FFFrameQueue.h"
#include "math/Vec2.h"
#include <cstdint>

namespace video
{
	class CC_DLL Decoder : public cocos2d::Ref
	{
		friend class Player;
	public:
		static Decoder* create(const std::string& path);

		bool open(const std::string& path);
		bool open(VideoStream* stream_, double loopA = 0, double loopB = -1);

		bool setup();
		bool setup(const cocos2d::Size& target_size);

		bool isOpened() const;
		void close();
		enum class ReadResult { FrameReady, NeedInput, EndOfStream, Error };
		// A returned buffer is borrowed until the next frame read, seek or close.
		ReadResult readFrame(uint8_t** vbuf);
		// At most one frame is returned. NeedInput also means the next frame is not due yet.
		ReadResult readFrameAt(double seconds, uint8_t** vbuf);
		uint32_t read(uint8_t** vbuf);
		AVPixelFormat getReadFormat();

		// Seek to the first decoded frame at or after seconds, relative to the video start.
		// On success the next read returns the landing frame and actualSeconds gives its time.
		bool seekTime(double seconds, double& actualSeconds);
		// Frame-rate estimate for nonzero offsets. Use seekTime for VFR.
		bool seek(int64_t frameOffset);

		int64_t tell() const;
		double getFrameTime() const { return frameTime; }
		double getFrameDuration() const { return frameDuration; }
		uint64_t getGeneration() const { return generation; }

	protected:
		int64_t getTotalFrames() const;
		double getVideoFrameRateForPlayer();

	public:
		ffmpeg::ContainerInfo getInfo() const { return videoInfo; }
		/** video size after convert */
		cocos2d::Size getVideoTargetSize() const { return targetSize; }

		// video stream info

		int64_t getVideoFrameCount(int index = -1) const;
		AVRational getVideoFrameRate(int index = -1) const;
		AVRational getVideoTimeBase(int index = -1) const;
		int64_t getVideoBitRate(int index = -1) const;
		AVPixelFormat getVideoFormat(int index = -1) const;
		std::string getVideoFormatName(int index = -1) const;
		cocos2d::Size getVideoSize(int index = -1) const;

		// audio stream info

		int64_t getAudioFrameCount(int index = -1) const;
		AVRational getAudioTimeBase(int index = -1) const;
		int64_t getAudioBitRate(int index = -1) const;
		int getAudioSampleRate(int index = -1) const;
		int getAudioChannelCount(int index = -1) const;
		std::string getAudioChannelLayoutName(int index = -1) const;

		// container info

		double getContainerDuration() const;
		double getContainerStartTime() const;
		int64_t getContainerBitRate() const;
		size_t getVideoStreamCount() const;
		size_t getAudioStreamCount() const;

		// decoder info

		std::string getVideoDecoderName() const;
		AVPixelFormat getVideoDecoderHardwareFormat() const;
		AVPixelFormat getVideoDecoderSoftwareFormat() const;
		bool isVideoDecoderHardware() const;

		std::string getAudioDecoderName() const;

		// utils

		static std::string getPixelFormatName(AVPixelFormat format);
		static std::vector<std::string> getAllDecoderNames();
		static std::string queryDecoderLongName(const std::string& name);
		static std::string queryDecoderType(const std::string& name);
		static std::string queryDecoderID(const std::string& name);
		static bool queryDecoderSupportsHardware(const std::string& name);

	protected:
		Decoder();
		~Decoder() override;
		bool opened = false;
		ffmpeg::Demuxer* demuxer = nullptr;
		ffmpeg::AudioFrameQueue* audioQueue = nullptr;
		ffmpeg::VideoFrameQueue* videoQueue = nullptr;

		uint32_t rawWidth = 0;
		uint32_t rawHeight = 0;
		cocos2d::Size targetSize;

		AVRational timeBaseV{};
		const AVCodec* pCodecV = nullptr;
		int idxVideo = -1;
		int idxAudio = -1;
		int idxVideoAtInfo = -1;
		int idxAudioAtInfo = -1;

		SwsContext* img_convert_ctx = nullptr;
		uint8_t* sws_pointers[4] = { nullptr };
		int sws_linesizes[4] = { 0 };
		AVPixelFormat swsFormat = AV_PIX_FMT_RGBA;

		ffmpeg::ContainerInfo videoInfo{};

	private:
		ReadResult fillPendingFrame();
		ReadResult outputPendingFrame(uint8_t** vbuf);
		void resetFrameState();

		ffmpeg::frame_ptr pendingFrame;
		int64_t startTimestamp = AV_NOPTS_VALUE;
		int64_t currentFrame = -1;
		int64_t nextFrame = 0;
		double pendingTime = 0.0;
		double pendingDuration = 0.0;
		double frameTime = -1.0;
		double frameDuration = 0.0;
		bool readError = false;
		bool initialPosition = true;
		uint64_t generation = 0;
	};
}
