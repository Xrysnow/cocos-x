#include "VideoDecoder.h"
#include "platform/CCFileUtils.h"
#include <climits>
#include <cmath>
#include <limits>

using namespace std;
using namespace cocos2d;
using namespace video;

Decoder* Decoder::create(const std::string& path)
{
	auto ret = new (std::nothrow) Decoder();
	if (ret&&ret->open(path))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool Decoder::open(const std::string& path)
{
	if (opened)
		return false;

	const auto filePath = FileUtils::getInstance()->fullPathForFilename(path);
	if (filePath.empty())
	{
		VERRO("no file: %s", path.c_str());
		return false;
	}

	demuxer = ffmpeg::Demuxer::create(filePath);
	if (!demuxer)
		return false;

	idxVideo = demuxer->getBestVideoStream();
	if (idxVideo >= 0)
		videoQueue = ffmpeg::VideoFrameQueue::create(false);
	if (!videoQueue || !demuxer->setVideoReceiver(videoQueue, idxVideo))
	{
		close();
		return false;
	}

	idxAudio = demuxer->getBestAudioStream();
	if (idxAudio >= 0)
	{
		audioQueue = ffmpeg::AudioFrameQueue::create(false);
		if (!audioQueue)
		{
			close();
			return false;
		}
		audioQueue->setMaxSize(64);
		// Audio is optional for this silent player. Retain only an opened receiver.
		if (!demuxer->setAudioReceiver(audioQueue, idxAudio))
		{
			CC_SAFE_RELEASE_NULL(audioQueue);
			idxAudio = -1;
		}
	}

	const auto format = demuxer->getAVFormatContext();
	const auto videoStream = format->streams[idxVideo];
	const auto videoDecoder = demuxer->getDecoder(idxVideo);
	const auto codec = videoDecoder->getCodecContext();
	pCodecV = videoDecoder->getCodec();
	rawWidth = codec->width;
	rawHeight = codec->height;
	timeBaseV = videoStream->time_base;
	if (timeBaseV.num <= 0 || timeBaseV.den <= 0)
	{
		VERRO("invalid video time base");
		close();
		return false;
	}
	startTimestamp = videoStream->start_time;
	if (startTimestamp == AV_NOPTS_VALUE && format->start_time != AV_NOPTS_VALUE)
		startTimestamp = av_rescale_q(format->start_time, AV_TIME_BASE_Q, timeBaseV);

	videoInfo = demuxer->getInfo();
	for (size_t i = 0; i < videoInfo.videoStreams.size(); ++i)
	{
		if (videoInfo.videoStreams[i].index == idxVideo)
			idxVideoAtInfo = static_cast<int>(i);
	}
	for (size_t i = 0; i < videoInfo.audioStreams.size(); ++i)
	{
		if (videoInfo.audioStreams[i].index == idxAudio)
			idxAudioAtInfo = static_cast<int>(i);
	}
	opened = true;
	return true;
}

bool Decoder::open(VideoStream*, double, double)
{
	VERRO("VideoStream input is not supported");
	return false;
}

bool Decoder::setup()
{
	return setup(Size(rawWidth, rawHeight));
}

bool Decoder::setup(const Size& target_size)
{
	if (!opened || sws_pointers[0])
		return false;

	const auto width = static_cast<double>(target_size.width);
	const auto height = static_cast<double>(target_size.height);
	if (!std::isfinite(width) || !std::isfinite(height) ||
		width < 1 || height < 1 || width > INT_MAX || height > INT_MAX)
		return false;

	const auto w = static_cast<int>(width);
	const auto h = static_cast<int>(height);
	if (av_image_alloc(sws_pointers, sws_linesizes, w, h, swsFormat, 1) < 0)
	{
		VERRO("can't allocate converted image");
		return false;
	}
	targetSize = Size(w, h);
	return true;
}

bool Decoder::isOpened() const
{
	return opened;
}

void Decoder::resetFrameState()
{
	pendingFrame.reset();
	pendingTime = 0.0;
	pendingDuration = 0.0;
	currentFrame = -1;
	nextFrame = 0;
	frameTime = -1.0;
	frameDuration = 0.0;
	readError = false;
}

void Decoder::close()
{
	if (opened)
		++generation;
	opened = false;
	resetFrameState();
	initialPosition = true;
	pCodecV = nullptr;
	CC_SAFE_RELEASE_NULL(demuxer);
	CC_SAFE_RELEASE_NULL(videoQueue);
	CC_SAFE_RELEASE_NULL(audioQueue);
	sws_freeContext(img_convert_ctx);
	img_convert_ctx = nullptr;
	av_freep(&sws_pointers[0]);
	for (auto& ptr : sws_pointers)
		ptr = nullptr;
	for (auto& linesize : sws_linesizes)
		linesize = 0;

	rawWidth = rawHeight = 0;
	targetSize = Size::ZERO;
	timeBaseV = {};
	startTimestamp = AV_NOPTS_VALUE;
	idxVideo = idxAudio = idxVideoAtInfo = idxAudioAtInfo = -1;
	videoInfo = {};
}

Decoder::ReadResult Decoder::fillPendingFrame()
{
	if (readError)
		return ReadResult::Error;
	if (pendingFrame)
		return ReadResult::FrameReady;

	while (videoQueue->empty())
	{
		switch (demuxer->step())
		{
		case ffmpeg::Demuxer::StepResult::Progress:
			continue;
		case ffmpeg::Demuxer::StepResult::NeedInput:
			return ReadResult::NeedInput;
		case ffmpeg::Demuxer::StepResult::Error:
			readError = true;
			return ReadResult::Error;
		case ffmpeg::Demuxer::StepResult::EndOfStream:
			if (videoQueue->empty())
				return ReadResult::EndOfStream;
			break;
		}
		break;
	}

	pendingFrame = videoQueue->pop();
	if (!pendingFrame)
	{
		VERRO("video queue did not return a frame");
		readError = true;
		return ReadResult::Error;
	}
	const auto pts = pendingFrame->best_effort_timestamp;
	if (pts != AV_NOPTS_VALUE)
	{
		if (startTimestamp == AV_NOPTS_VALUE)
			startTimestamp = pts;
		const auto ticks = av_sat_sub64(pts, startTimestamp);
		pendingTime = static_cast<double>(ticks) * av_q2d(timeBaseV);
	}
	else
	{
		// Missing timestamps still allow sequential playback on a nominal timeline.
		pendingTime = currentFrame < 0 ? 0.0 : frameTime + frameDuration;
	}
	pendingDuration = pendingFrame->duration > 0
		? pendingFrame->duration * av_q2d(timeBaseV)
		: 1.0 / getVideoFrameRateForPlayer();
	return ReadResult::FrameReady;
}

Decoder::ReadResult Decoder::outputPendingFrame(uint8_t** vbuf)
{
	const auto frame = pendingFrame.get();
	img_convert_ctx = sws_getCachedContext(img_convert_ctx,
		frame->width, frame->height, static_cast<AVPixelFormat>(frame->format),
		static_cast<int>(targetSize.width), static_cast<int>(targetSize.height),
		swsFormat, SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
	if (!img_convert_ctx || sws_scale(img_convert_ctx, frame->data, frame->linesize,
		0, frame->height, sws_pointers, sws_linesizes) <= 0)
	{
		VERRO("failed to convert video frame");
		readError = true;
		return ReadResult::Error;
	}
	currentFrame = nextFrame;
	if (nextFrame < INT64_MAX)
		++nextFrame;
	frameTime = pendingTime;
	frameDuration = pendingDuration;
	initialPosition = false;
	pendingFrame.reset();
	*vbuf = sws_pointers[0];
	return ReadResult::FrameReady;
}

Decoder::ReadResult Decoder::readFrame(uint8_t** vbuf)
{
	if (!vbuf)
		return ReadResult::Error;
	*vbuf = nullptr;
	if (!opened || !sws_pointers[0])
		return ReadResult::Error;
	const auto result = fillPendingFrame();
	return result == ReadResult::FrameReady ? outputPendingFrame(vbuf) : result;
}

Decoder::ReadResult Decoder::readFrameAt(double seconds, uint8_t** vbuf)
{
	if (!vbuf)
		return ReadResult::Error;
	*vbuf = nullptr;
	if (!opened || !sws_pointers[0] || !std::isfinite(seconds))
		return ReadResult::Error;
	const auto result = fillPendingFrame();
	// Comparing the next representable time avoids missing an equal PTS due to rounding.
	const auto limit = std::nextafter(seconds, std::numeric_limits<double>::infinity());
	if (result == ReadResult::FrameReady)
		return pendingTime <= limit ? outputPendingFrame(vbuf) : ReadResult::NeedInput;
	if (result == ReadResult::EndOfStream && currentFrame >= 0 && limit < frameTime + frameDuration)
		return ReadResult::NeedInput;
	return result;
}

uint32_t Decoder::read(uint8_t** vbuf)
{
	return readFrame(vbuf) == ReadResult::FrameReady ? 1 : 0;
}

AVPixelFormat Decoder::getReadFormat()
{
	return swsFormat;
}

bool Decoder::seekTime(double seconds, double& actualSeconds)
{
	if (!opened || !std::isfinite(seconds) || seconds < 0)
		return false;

	const bool primeFirstFrame = initialPosition && seconds == 0;
	if (!primeFirstFrame)
	{
		if (startTimestamp == AV_NOPTS_VALUE && initialPosition)
			fillPendingFrame();
		const auto origin = startTimestamp == AV_NOPTS_VALUE ? 0 : startTimestamp;
		const auto ticks = std::floor(static_cast<long double>(seconds) * timeBaseV.den / timeBaseV.num);
		constexpr long double timestampLimit = 9223372036854775808.0L;
		if (ticks >= timestampLimit)
			return false;
		const auto offset = static_cast<int64_t>(ticks);
		if (origin > INT64_MAX - offset || !demuxer->seekTimestamp(idxVideo, origin + offset))
			return false;
		resetFrameState();
		++generation;
		initialPosition = false;
	}

	const auto limit = std::nextafter(seconds, -std::numeric_limits<double>::infinity());
	while (fillPendingFrame() == ReadResult::FrameReady)
	{
		// Zero means the first decoded video frame, including preroll with negative PTS.
		if (seconds == 0 || (pendingFrame->best_effort_timestamp != AV_NOPTS_VALUE && pendingTime >= limit))
		{
			actualSeconds = pendingTime;
			return true;
		}
		pendingFrame.reset();
	}
	return false;
}

bool Decoder::seek(int64_t frameOffset)
{
	if (frameOffset < 0)
		return false;
	const auto rate = getVideoFrameRate();
	if (frameOffset != 0 && (rate.num <= 0 || rate.den <= 0))
		return false;

	const auto time = frameOffset == 0 ? 0.0 : static_cast<double>(frameOffset) * av_q2d(av_inv_q(rate));
	double actualTime;
	if (!seekTime(time, actualTime))
		return false;
	nextFrame = frameOffset;
	return true;
}

int64_t Decoder::tell() const
{
	return currentFrame;
}

int64_t Decoder::getTotalFrames() const
{
	return getVideoFrameCount();
}

double Decoder::getVideoFrameRateForPlayer()
{
	const auto rate = getVideoFrameRate();
	return rate.num > 0 && rate.den > 0 ? av_q2d(rate) : 60.0;
}

Decoder::Decoder() = default;

Decoder::~Decoder()
{
	close();
}

int64_t Decoder::getVideoFrameCount(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return 0;
	return videoInfo.videoStreams.at(index).numFrames;
}

AVRational Decoder::getVideoFrameRate(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return av_make_q(0, 0);
	return videoInfo.videoStreams.at(index).frameRate;
}

AVRational Decoder::getVideoTimeBase(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return av_make_q(0, 0);
	return videoInfo.videoStreams.at(index).timeBase;
}

int64_t Decoder::getVideoBitRate(int index) const {
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return 0;
	return videoInfo.videoStreams.at(index).bitRate;
}

AVPixelFormat Decoder::getVideoFormat(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return AV_PIX_FMT_NONE;
	return videoInfo.videoStreams.at(index).format;
}

std::string Decoder::getVideoFormatName(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return "";
	const auto ret = videoInfo.videoStreams.at(index).formatName;
	return ret ? ret : "";
}

Size Decoder::getVideoSize(int index) const
{
	if (index == -1) index = idxVideoAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.videoStreams.size())
		return { 0,0 };
	auto& v = videoInfo.videoStreams.at(index);
	return { (float)v.width,(float)v.height };
}

int64_t Decoder::getAudioFrameCount(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return 0;
	return videoInfo.audioStreams.at(index).numFrames;
}

AVRational Decoder::getAudioTimeBase(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return av_make_q(0, 0);
	return videoInfo.audioStreams.at(index).timeBase;
}

int64_t Decoder::getAudioBitRate(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return 0;
	return videoInfo.audioStreams.at(index).bitRate;
}

int Decoder::getAudioSampleRate(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return 0;
	return videoInfo.audioStreams.at(index).sampleRate;
}

int Decoder::getAudioChannelCount(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return 0;
	return videoInfo.audioStreams.at(index).channels;
}

std::string Decoder::getAudioChannelLayoutName(int index) const
{
	if (index == -1) index = idxAudioAtInfo;
	if (index < 0 || static_cast<size_t>(index) >= videoInfo.audioStreams.size())
		return "";
	auto& info = videoInfo.audioStreams.at(index);
	const auto ret = info.channelLayoutName;
	if (ret[sizeof(info.channelLayoutName) - 1] != 0) {
		return { ret, sizeof(info.channelLayoutName) };
	}
	return ret;
}

double Decoder::getContainerDuration() const
{
	return videoInfo.duration;
}

double Decoder::getContainerStartTime() const
{
	return videoInfo.start;
}

int64_t Decoder::getContainerBitRate() const
{
	return videoInfo.bitRate;
}

size_t Decoder::getVideoStreamCount() const
{
	return videoInfo.videoStreams.size();
}

size_t Decoder::getAudioStreamCount() const
{
	return videoInfo.audioStreams.size();
}

std::string Decoder::getVideoDecoderName() const
{
	return pCodecV && pCodecV->name ? pCodecV->name : "";
}

AVPixelFormat Decoder::getVideoDecoderHardwareFormat() const
{
	const auto decoder = demuxer ? static_cast<ffmpeg::VideoDecoder*>(demuxer->getDecoder(idxVideo)) : nullptr;
	return decoder ? decoder->getHardwareFormat() : AV_PIX_FMT_NONE;
}

AVPixelFormat Decoder::getVideoDecoderSoftwareFormat() const
{
	const auto decoder = demuxer ? static_cast<ffmpeg::VideoDecoder*>(demuxer->getDecoder(idxVideo)) : nullptr;
	return decoder ? decoder->getSoftwareFormat() : AV_PIX_FMT_NONE;
}

bool Decoder::isVideoDecoderHardware() const
{
	const auto decoder = demuxer ? static_cast<ffmpeg::VideoDecoder*>(demuxer->getDecoder(idxVideo)) : nullptr;
	return decoder ? decoder->isHardware() : false;
}

std::string Decoder::getAudioDecoderName() const
{
	const auto decoder = demuxer ? demuxer->getDecoder(idxAudio) : nullptr;
	if (!decoder)
		return "";
	const auto ret = decoder->getCodec()->name;
	return ret ? ret : "";
}

std::string Decoder::getPixelFormatName(AVPixelFormat format)
{
	const auto desc = av_pix_fmt_desc_get(format);
	if (!desc)
		return "";
	return desc->name;
}

std::vector<std::string> Decoder::getAllDecoderNames()
{
	std::vector<std::string> ret;
	for (auto&& c : ffmpeg::Codec::getAllDecoders())
		ret.emplace_back(c->name);
	return ret;
}

std::string Decoder::queryDecoderLongName(const std::string& name)
{
	const auto codec = avcodec_find_decoder_by_name(name.c_str());
	if (!codec)
		return "";
	return codec->long_name ? codec->long_name : "";
}

std::string Decoder::queryDecoderType(const std::string& name)
{
	const auto codec = avcodec_find_decoder_by_name(name.c_str());
	if (!codec)
		return "";
	const auto ret = av_get_media_type_string(codec->type);
	return ret ? ret : "";
}

std::string Decoder::queryDecoderID(const std::string& name)
{
	const auto codec = avcodec_find_decoder_by_name(name.c_str());
	if (!codec)
		return "";
	return avcodec_get_name(codec->id);
}

bool Decoder::queryDecoderSupportsHardware(const std::string& name)
{
	const auto codec = avcodec_find_decoder_by_name(name.c_str());
	if (!codec)
		return false;
	return avcodec_get_hw_config(codec, 0);
}
