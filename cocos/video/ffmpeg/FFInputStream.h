#pragma once
#include "base/CCRef.h"
#include "video/VideoCommon.h"
#include "video/FFInfo.h"
#include "FFFrameReceiver.h"
#include "FFCodec.h"

namespace ffmpeg
{
	struct ContainerInfo;

	class InputStream : public cocos2d::Ref
	{
	protected:
		InputStream();
		virtual ~InputStream();
		bool init(Decoder* decoder, AVFormatContext* format, AVStream* stream, bool useHardware = true);
	public:
		void setFrameReceiver(FrameReceiver* newReceiver);
		FrameReceiver* getFrameReceiver() const { return receiver; }
		bool drain();
		void onSeek();
		virtual void addToContainerInfo(ContainerInfo* info) = 0;

		Decoder* getDecoder() const { return decoder; }
		AVStream* getStream() const { return stream; }

		bool decodePacket(AVPacket* pkt);
	protected:
		int receiveFrames(bool& received);
		virtual AVFrame* prepareFrame();

		virtual void configureCodecContext();
		static int64_t calculateBitRate(AVCodecContext* ctx);
		void discoverMetaData();
		virtual void clean();

		AVCodecContext* codecContext = nullptr;
		AVFormatContext* format = nullptr;
		AVStream* stream = nullptr;

		FrameReceiver* receiver = nullptr;
		Decoder* decoder = nullptr;
		AVFrame* frame = nullptr;
		MetaData* metaData = nullptr;
		bool drained = false;
	};

	class VideoInputStream : public InputStream
	{
		virtual ~VideoInputStream();
	public:
		// Returns an owned reference.
		static VideoInputStream* create(
			VideoDecoder* decoder, AVFormatContext* format, AVStream* stream, bool useHardware = true);
		void addToContainerInfo(ContainerInfo* info) override;
	protected:
		AVFrame* prepareFrame() override;
		void clean() override;
		AVFrame* frameSW = nullptr;
	};

	class AudioInputStream : public InputStream
	{
		virtual ~AudioInputStream() = default;
	public:
		// Returns an owned reference.
		static AudioInputStream* create(
			AudioDecoder* decoder, AVFormatContext* format, AVStream* stream);
		void addToContainerInfo(ContainerInfo* info) override;
	protected:
		void configureCodecContext() override;
	};
}
