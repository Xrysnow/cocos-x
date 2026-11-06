#include "FFDemuxer.h"
#include "FFPointer.h"
#include <new>

using namespace std;
using namespace ffmpeg;

std::vector<const AVInputFormat*> Demuxer::getInputFormats()
{
	std::vector<const AVInputFormat*> ret;
	void* opaque = nullptr;
	auto inputFormat = av_demuxer_iterate(&opaque);
	while (inputFormat)
	{
		ret.push_back(inputFormat);
		inputFormat = av_demuxer_iterate(&opaque);
	}
	return ret;
}

Demuxer::Demuxer()
{
}

Demuxer::~Demuxer()
{
	clean();
}

bool Demuxer::init(const std::string& url)
{
	this->url = url;

	int ret;
	if ((ret = avformat_open_input(&containerContext, url.c_str(), nullptr, nullptr)) < 0)
	{
		VERRO("Failed to open %s: %d", url.c_str(), ret);
		return false;
	}
	if ((ret = avformat_find_stream_info(containerContext, nullptr)) < 0)
	{
		VERRO("Failed to read streams from %s: %d", url.c_str(), ret);
		return false;
	}

	return true;
}

Demuxer* Demuxer::create(const std::string& url)
{
	auto ret = new (std::nothrow) Demuxer();
	if (ret && ret->init(url))
		return ret;
	delete ret;
	return nullptr;
}

bool Demuxer::setAudioReceiver(FrameReceiver* receiver, int streamIndex)
{
	if (!receiver || receiver->getMediaType() != AVMEDIA_TYPE_AUDIO)
	{
		VERRO("invalid receiver");
		return false;
	}
	return setReceiver(receiver, AVMEDIA_TYPE_AUDIO, streamIndex);
}

bool Demuxer::setVideoReceiver(FrameReceiver* receiver, int streamIndex)
{
	if (!receiver || receiver->getMediaType() != AVMEDIA_TYPE_VIDEO)
	{
		VERRO("invalid receiver");
		return false;
	}
	return setReceiver(receiver, AVMEDIA_TYPE_VIDEO, streamIndex);
}

Demuxer::StepResult Demuxer::step()
{
	if (state != StepResult::Progress)
		return state;

	auto packet = newPacketPtr();
	if (!packet)
	{
		VERRO("failed to allocate packet");
		return state = StepResult::Error;
	}

	const auto ret = av_read_frame(containerContext, packet.get());
	if (ret == AVERROR_EOF)
	{
		bool drained = true;
		for (auto& it : inputStreams)
		{
			if (!it.second->drain())
				drained = false;
		}
		return state = drained ? StepResult::EndOfStream : StepResult::Error;
	}
	if (ret == AVERROR(EAGAIN))
		return StepResult::NeedInput;
	if (ret < 0)
	{
		VERRO("failed to read packet: %d", ret);
		return state = StepResult::Error;
	}

	const auto stream = getInputStream(packet->stream_index);
	if (stream && !stream->decodePacket(packet.get()))
		return state = StepResult::Error;
	return StepResult::Progress;
}

bool Demuxer::seekTimestamp(int streamIndex, int64_t timestamp)
{
	// Bound the seek to a keyframe at or before the requested stream timestamp.
	auto ret = avformat_seek_file(containerContext,
		streamIndex, INT64_MIN, timestamp, timestamp, 0);
	if (ret < 0)
		ret = av_seek_frame(containerContext, streamIndex, timestamp, AVSEEK_FLAG_BACKWARD);
	if (ret < 0)
	{
		VERRO("failed to seek input: %d", ret);
		return false;
	}

	for (auto& it : inputStreams)
		it.second->onSeek();
	state = StepResult::Progress;
	return true;
}

int Demuxer::getBestAudioStream()
{
	if (bestAudioStream < 0)
	{
		const auto ret = av_find_best_stream(
			containerContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
		if (ret < 0)
			return -1;
		bestAudioStream = ret;
	}
	return bestAudioStream;
}

int Demuxer::getBestVideoStream()
{
	if (bestVideoStream < 0)
	{
		const auto ret = av_find_best_stream(
			containerContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
		if (ret < 0)
			return -1;
		bestVideoStream = ret;
	}
	return bestVideoStream;
}

ContainerInfo Demuxer::getInfo()
{
	ContainerInfo info{};
	if (containerContext->duration != AV_NOPTS_VALUE)
		info.duration = static_cast<double>(containerContext->duration) / AV_TIME_BASE;
	if (containerContext->start_time != AV_NOPTS_VALUE)
		info.start = static_cast<double>(containerContext->start_time) / AV_TIME_BASE;
	info.bitRate = containerContext->bit_rate;
	info.format = containerContext->iformat;

	for (auto& it : inputStreams)
	{
		it.second->addToContainerInfo(&info);
	}
	return info;
}

FrameReceiver* Demuxer::getFrameReceiver(int streamIndex)
{
	const auto s = inputStreams.at(streamIndex);
	if(s)
		return s->getFrameReceiver();
	return nullptr;
}

Decoder* Demuxer::getDecoder(int streamIndex)
{
	const auto stream = getInputStream(streamIndex);
	return stream ? stream->getDecoder() : nullptr;
}

bool Demuxer::setReceiver(FrameReceiver* receiver, AVMediaType type, int streamIndex)
{
	if (streamIndex < 0)
	{
		int ret = av_find_best_stream(containerContext, type, -1, -1, nullptr, 0);
		if (ret < 0)
		{
			VERRO("can't find stream in input %s: %d", url.c_str(), ret);
			return false;
		}
		streamIndex = ret;
	}
	if (streamIndex >= containerContext->nb_streams ||
		containerContext->streams[streamIndex]->codecpar->codec_type != type)
	{
		VERRO("invalid stream index");
		return false;
	}
	auto inputStream = getOrCreateInputStream(streamIndex);
	if (!inputStream)
	{
		VERRO("failed to create input stream");
		return false;
	}
	inputStream->setFrameReceiver(receiver);
	return true;
}

InputStream* Demuxer::getOrCreateInputStream(int streamIndex)
{
	if (const auto input = getInputStream(streamIndex))
		return input;

	const auto stream = containerContext->streams[streamIndex];
	const auto codecID = stream->codecpar->codec_id;
	InputStream* input = nullptr;
	switch (stream->codecpar->codec_type)
	{
	case AVMEDIA_TYPE_VIDEO:
		if (auto decoder = VideoDecoder::createById(codecID, false))
		{
			input = VideoInputStream::create(decoder, containerContext, stream);
			decoder->release();
			if (!input)
			{
				// Start software fallback with a fresh context and stream parameters.
				if (auto software = VideoDecoder::createById(codecID, false))
				{
					input = VideoInputStream::create(software, containerContext, stream, false);
					software->release();
				}
			}
		}
		break;
	case AVMEDIA_TYPE_AUDIO:
		if (auto decoder = AudioDecoder::createById(codecID, false))
		{
			input = AudioInputStream::create(decoder, containerContext, stream);
			decoder->release();
		}
		break;
	default:
		break;
	}
	if (input)
	{
		inputStreams.insert(streamIndex, input);
		input->release();
	}
	return input;
}

void Demuxer::clean()
{
	inputStreams.clear();
	avformat_close_input(&containerContext);
}
