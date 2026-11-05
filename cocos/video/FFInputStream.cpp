#include "FFInputStream.h"
#include "FFInfo.h"
#include <new>

using namespace std;
using namespace ffmpeg;

InputStream::InputStream()
{
}

InputStream::~InputStream()
{
	InputStream::clean();
}

bool InputStream::init(Decoder* decoder, AVFormatContext* format, AVStream* stream, bool useHardware)
{
	if (!decoder || !format || !stream)
	{
		return false;
	}
	this->stream = stream;
	this->format = format;
	this->decoder = decoder;
	CC_SAFE_RETAIN(decoder);

	auto codec = decoder->getCodec();
	codecContext = decoder->getCodecContext();

	int ret;
	if ((ret = avcodec_parameters_to_context(codecContext, stream->codecpar)) < 0)
	{
		VERRO("failed to get parameters of codec %s: %d", codec->name, ret);
		return false;
	}

	codecContext->pkt_timebase = stream->time_base;
	configureCodecContext();

	if (!(useHardware ? decoder->open() : decoder->Codec::open()))
	{
		VERRO("failed to open codec %s", codec->name);
		return false;
	}

	if (!codecContext->codec)
		codecContext->codec = codec;

	frame = av_frame_alloc();
	if (!frame)
	{
		VERRO("can't allocate frame");
		return false;
	}
	return true;
}

void InputStream::setFrameReceiver(FrameReceiver* newReceiver)
{
	CC_SAFE_RELEASE_NULL(receiver);
	receiver = newReceiver;
	CC_SAFE_RETAIN(receiver);
}

bool InputStream::drain()
{
	if (drained)
		return true;
	if (!decodePacket(nullptr))
		return false;
	drained = true;
	if (receiver)
		receiver->end();
	return true;
}

void InputStream::onSeek()
{
	if (receiver)
		receiver->clear();
	av_frame_unref(frame);
	decoder->flushBuffers();
	drained = false;
}

bool InputStream::decodePacket(AVPacket* pkt)
{
	while (true)
	{
		const auto result = avcodec_send_packet(codecContext, pkt);
		if (result < 0 && result != AVERROR(EAGAIN))
		{
			VERRO("failed to send packet: %s", video::getErrorString(result).c_str());
			return false;
		}

		bool received = false;
		const auto receiveResult = receiveFrames(received);
		if (receiveResult != AVERROR(EAGAIN) && receiveResult != AVERROR_EOF)
			return false;

		if (result != AVERROR(EAGAIN))
		{
			// A flush packet transitions the codec to draining until receive reports EOF.
			const auto expected = pkt ? AVERROR(EAGAIN) : AVERROR_EOF;
			if (receiveResult == expected)
				return true;
		}
		else if (receiveResult == AVERROR(EAGAIN) && received)
		{
			// Output made room. Retry the same packet before reading more input.
			continue;
		}

		VERRO("unexpected codec state after %s", pkt ? "packet" : "drain");
		return false;
	}
}

int InputStream::receiveFrames(bool& received)
{
	while (true)
	{
		const auto result = avcodec_receive_frame(codecContext, frame);
		if (result < 0)
		{
			if (result != AVERROR(EAGAIN) && result != AVERROR_EOF)
				VERRO("failed to receive frame: %s", video::getErrorString(result).c_str());
			return result;
		}

		received = true;
		if (!receiver)
			continue;
		auto output = prepareFrame();
		if (!output)
			return AVERROR_EXTERNAL;
		if (!output->sample_aspect_ratio.num)
			output->sample_aspect_ratio = stream->sample_aspect_ratio;
		if (!metaData)
			discoverMetaData();

		const auto buffer = receiver->alloc();
		if (!buffer)
		{
			av_frame_unref(output);
			VERRO("failed to allocate receiver frame");
			return AVERROR(ENOMEM);
		}
		if (buffer != output)
		{
			av_frame_unref(buffer);
			av_frame_move_ref(buffer, output);
		}
		receiver->receive(buffer, metaData);
	}
}

AVFrame* InputStream::prepareFrame()
{
	return frame;
}

void InputStream::configureCodecContext()
{
}

int64_t InputStream::calculateBitRate(AVCodecContext* ctx)
{
	int64_t bit_rate;
	int bits_per_sample;

	switch (ctx->codec_type)
	{
	case AVMEDIA_TYPE_VIDEO:
	case AVMEDIA_TYPE_DATA:
	case AVMEDIA_TYPE_SUBTITLE:
	case AVMEDIA_TYPE_ATTACHMENT:
		bit_rate = ctx->bit_rate;
		break;
	case AVMEDIA_TYPE_AUDIO:
		bits_per_sample = av_get_bits_per_sample(ctx->codec_id);
		bit_rate = bits_per_sample ?
			ctx->sample_rate * (int64_t)ctx->ch_layout.nb_channels * bits_per_sample : ctx->bit_rate;
		break;
	default:
		bit_rate = 0;
		break;
	}
	return bit_rate;
}

void InputStream::discoverMetaData()
{
	AVRational overrideFrameRate;
	overrideFrameRate.num = 0;
	overrideFrameRate.den = 0;

	AVRational tb = overrideFrameRate.num ?
		av_inv_q(overrideFrameRate) : stream->time_base;
	AVRational fr = overrideFrameRate;
	if (!fr.num)
		fr = av_guess_frame_rate(format, stream, nullptr);

	if (!metaData)
		metaData = new MetaData();
	metaData->timeBase = tb;
	metaData->frameRate = fr;
	metaData->type = codecContext->codec->type;
}

void InputStream::clean()
{
	if (frame)
	{
		av_frame_free(&frame);
		frame = nullptr;
	}
	if (metaData)
	{
		delete metaData;
		metaData = nullptr;
	}
	CC_SAFE_RELEASE_NULL(receiver);
	CC_SAFE_RELEASE_NULL(decoder);
}

VideoInputStream::~VideoInputStream()
{
	VideoInputStream::clean();
}

VideoInputStream* VideoInputStream::create(
	VideoDecoder* decoder, AVFormatContext* format, AVStream* stream, bool useHardware)
{
	auto ret = new (std::nothrow) VideoInputStream();
	if (ret && ret->init(decoder, format, stream, useHardware))
	{
		if (!decoder->isHardware() || (ret->frameSW = av_frame_alloc()))
			return ret;
	}
	delete ret;
	return nullptr;
}

AVFrame* VideoInputStream::prepareFrame()
{
	const auto videoDecoder = static_cast<VideoDecoder*>(decoder);
	if (!videoDecoder->isHardware() || frame->format != videoDecoder->getHardwareFormat())
		return frame;

	av_frame_unref(frameSW);
	auto result = av_hwframe_transfer_data(frameSW, frame, 0);
	if (result >= 0)
		result = av_frame_copy_props(frameSW, frame);
	if (result < 0)
	{
		VERRO("failed to transfer hardware frame: %s", video::getErrorString(result).c_str());
		av_frame_unref(frameSW);
		return nullptr;
	}
	return frameSW;
}

void VideoInputStream::addToContainerInfo(ContainerInfo* containerInfo)
{
	VideoStreamInfo info{};

	info.index = stream->index;
	info.id = stream->id;
	info.numFrames = stream->nb_frames;
	info.timeBase = stream->time_base;

	auto fr = stream->avg_frame_rate;
	if (!fr.num || !fr.den)
		fr = av_guess_frame_rate(format, stream, nullptr);

	info.frameRate = fr;

	auto codecContext = decoder->getCodecContext();

	//codecContext->properties = stream->codec->properties;
	//codecContext->codec = stream->codec->codec;
	//codecContext->qmin = stream->codec->qmin;
	//codecContext->qmax = stream->codec->qmax;
	//codecContext->coded_width = stream->codec->coded_width;
	//codecContext->coded_height = stream->codec->coded_height;

	info.bitRate = calculateBitRate(codecContext);

	info.codec = avcodec_find_decoder(codecContext->codec_id);
	info.format = codecContext->pix_fmt;
	info.formatName = av_get_pix_fmt_name(info.format);
	info.width = codecContext->width;
	info.height = codecContext->height;
	containerInfo->videoStreams.push_back(info);
}

void VideoInputStream::clean()
{
	if (frameSW)
	{
		av_frame_free(&frameSW);
		frameSW = nullptr;
	}
}

AudioInputStream* AudioInputStream::create(
	AudioDecoder* decoder, AVFormatContext* format, AVStream* stream)
{
	auto ret = new (std::nothrow) AudioInputStream();
	if (ret && ret->init(decoder, format, stream))
		return ret;
	delete ret;
	return nullptr;
}

void AudioInputStream::addToContainerInfo(ContainerInfo* containerInfo)
{
	AudioStreamInfo info{};

	info.index = stream->index;
	info.id = stream->id;
	info.numFrames = stream->nb_frames;
	info.timeBase = stream->time_base;

	auto codecContext = decoder->getCodecContext();

	//codecContext->properties = stream->codec->properties;
	//codecContext->codec = stream->codec->codec;
	//codecContext->qmin = stream->codec->qmin;
	//codecContext->qmax = stream->codec->qmax;
	//codecContext->coded_width = stream->codec->coded_width;
	//codecContext->coded_height = stream->codec->coded_height;

	info.bitRate = calculateBitRate(codecContext);

	info.codec = avcodec_find_decoder(codecContext->codec_id);
	info.sampleRate = codecContext->sample_rate;
	const auto& layout = codecContext->ch_layout;
	info.channels = layout.nb_channels;
	info.channelLayout = layout.order == AV_CHANNEL_ORDER_NATIVE ? layout.u.mask : 0;
	av_channel_layout_describe(&layout, info.channelLayoutName, sizeof(info.channelLayoutName));
	containerInfo->audioStreams.push_back(info);
}

void AudioInputStream::configureCodecContext()
{
	// guess channel layout for the decoder
	auto& layout = codecContext->ch_layout;
	if (layout.order == AV_CHANNEL_ORDER_UNSPEC && layout.nb_channels > 0)
	{
		const auto channels = layout.nb_channels;
		av_channel_layout_uninit(&layout);
		av_channel_layout_default(&layout, channels);
	}
}
