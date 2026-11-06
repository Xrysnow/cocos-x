#pragma once
#include "base/CCRef.h"
#include "base/CCMap.h"
#include "video/VideoCommon.h"
#include "video/FFInfo.h"
#include "FFFrameReceiver.h"
#include "FFInputStream.h"

namespace ffmpeg
{
	class Demuxer : public cocos2d::Ref
	{
	public:
		static std::vector<const AVInputFormat*> getInputFormats();
	protected:
		Demuxer();
		virtual ~Demuxer();
		bool init(const std::string& url);
	public:
		// Returns an owned reference.
		static Demuxer* create(const std::string& url);

		bool setAudioReceiver(FrameReceiver* receiver, int streamIndex = -1);
		bool setVideoReceiver(FrameReceiver* receiver, int streamIndex = -1);
		enum class StepResult { Progress, NeedInput, EndOfStream, Error };
		StepResult step();
		bool seekTimestamp(int streamIndex, int64_t timestamp);

		int getBestAudioStream();
		int getBestVideoStream();
		ContainerInfo getInfo();
		std::string getUrl() const { return url; }

		AVFormatContext* getAVFormatContext() const { return containerContext; }
		InputStream* getInputStream(int streamIndex) { return inputStreams.at(streamIndex); }
		Decoder* getDecoder(int streamIndex);
		FrameReceiver* getFrameReceiver(int streamIndex);
	protected:

		bool setReceiver(FrameReceiver* receiver, AVMediaType type, int streamIndex = -1);
		InputStream* getOrCreateInputStream(int index);
		void clean();

		StepResult state = StepResult::Progress;
		std::string url;
		AVFormatContext* containerContext = nullptr;
		int bestAudioStream = -1;
		int bestVideoStream = -1;
		cocos2d::Map<int, InputStream*> inputStreams;
	};
}
