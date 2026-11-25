#pragma once
#include "base/Ref.h"
#include "base/Map.h"
#include "io/core/Stream.h"
#include <atomic>
#include <memory>
#include "video/VideoCommon.h"
#include "video/FFInfo.h"
#include "FFFrameReceiver.h"
#include "FFInputStream.h"

namespace ffmpeg
{
	class AvioInput;

	class Demuxer : public cc::Ref
	{
	public:
		static std::vector<const AVInputFormat*> getInputFormats();
	protected:
		Demuxer();
		virtual ~Demuxer();
		bool init(cc::io::StreamPtr source, const char* name, const std::atomic<bool>* stop);
	public:
		// Returns an owned reference.
		static cc::IntrusivePtr<Demuxer> create(cc::io::StreamPtr source, const char* name, const std::atomic<bool>* stop);

		bool setAudioReceiver(FrameReceiver* receiver, int streamIndex = -1);
		bool setVideoReceiver(FrameReceiver* receiver, int streamIndex = -1);
		enum class StepResult { Progress, NeedInput, EndOfStream, Error };
		StepResult step();
		bool seekTimestamp(int streamIndex, int64_t timestamp);

		int getBestAudioStream();
		int getBestVideoStream();
		ContainerInfo getInfo();
		bool isSeekable() const;
		bool isCancelled() const;

		AVFormatContext* getAVFormatContext() const { return containerContext; }
		InputStream* getInputStream(int streamIndex) { return inputStreams.at(streamIndex); }
		Decoder* getDecoder(int streamIndex);
		FrameReceiver* getFrameReceiver(int streamIndex);
	protected:

		bool setReceiver(FrameReceiver* receiver, AVMediaType type, int streamIndex = -1);
		InputStream* getOrCreateInputStream(int index);
		void clean();

		StepResult state = StepResult::Progress;
		std::unique_ptr<AvioInput> input;
		AVFormatContext* containerContext = nullptr;
		int bestAudioStream = -1;
		int bestVideoStream = -1;
		cc::Map<int, InputStream*> inputStreams;
	};
}
