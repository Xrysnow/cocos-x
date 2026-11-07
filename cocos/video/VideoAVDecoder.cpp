#include <cerrno>
// Stream.h reaches CCConsole/yasio on Windows, which replaces C errno macros
// with socket error values. Capture FFmpeg's native C errno before that include.
namespace { constexpr int codecAgain = EAGAIN; constexpr int ioNotImplemented = ENOSYS; }

#include "VideoAVDecoder.h"
#include "VideoCommon.h"
#include "ffmpeg/FFAvio.h"
#include "ffmpeg/FFPointer.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <limits>
#include <string>

using namespace video;

namespace
{
	constexpr size_t packetBudget = 16 * 1024 * 1024;
	constexpr size_t packetLimit = 512;
	constexpr size_t rawBudget = 8 * 1024 * 1024;
	constexpr size_t videoBudget = 64 * 1024 * 1024;
	constexpr int outputRate = 48000;
	constexpr int chunkFrames = 960;
	constexpr AVRational sampleBase{1, outputRate};
	constexpr AVRational microBase{1, AV_TIME_BASE};

	int64_t timestamp(const AVFrame* frame)
	{
		return frame->best_effort_timestamp != AV_NOPTS_VALUE ? frame->best_effort_timestamp : frame->pts;
	}

	bool validTimeBase(AVRational value) { return value.num > 0 && value.den > 0; }

	bool checkedSubtract(int64_t a, int64_t b, int64_t& result)
	{
		if (b > 0 && a < std::numeric_limits<int64_t>::min() + b ||
			b < 0 && a > std::numeric_limits<int64_t>::max() + b)
			return false;
		result = a - b;
		return true;
	}

	bool checkedAdd(int64_t a, int64_t b, int64_t& result)
	{
		if (b > 0 && a > std::numeric_limits<int64_t>::max() - b ||
			b < 0 && a < std::numeric_limits<int64_t>::min() - b)
			return false;
		result = a + b;
		return true;
	}

	bool rescaleTimestamp(int64_t value, AVRational from, AVRational to, int64_t& result)
	{
		result = av_rescale_q(value, from, to);
		// av_rescale reports overflow with INT64_MIN. Neither limit is a usable
		// media timestamp, and rejecting both leaves safe room for arithmetic.
		return result != std::numeric_limits<int64_t>::min() && result != std::numeric_limits<int64_t>::max();
	}
}

struct VideoAVDecoder::Impl
{
	struct Packet
	{
		ffmpeg::packet_ptr packet;
		size_t bytes;
	};
	struct Track
	{
		AVCodecContext* codec = nullptr;
		AVStream* stream = nullptr;
		std::deque<Packet> packets;
		ffmpeg::frame_ptr frame = ffmpeg::newFramePtr();
		bool ready = false, draining = false, ended = false, seen = false;
	};

	~Impl()
	{
		swr_free(&swr);
		av_channel_layout_uninit(&inputLayout);
		sws_freeContext(sws);
		avcodec_free_context(&video.codec);
		avcodec_free_context(&audio.codec);
		avformat_close_input(&format);
	}

	bool fail(AsyncVideoError value, const char* where, const char* message, int code = 0)
	{
		if (error == AsyncVideoError::None)
		{
			error = value;
			stage = where;
			detail = message;
			backend = code;
			VERRO("%s: %s (%d)", where, message, code);
		}
		return false;
	}

	bool mediaTimestamp(int64_t value, AVRational base, int64_t& result)
	{
		int64_t absolute;
		return rescaleTimestamp(value, base, microBase, absolute) && checkedSubtract(absolute, origin, result) ||
			fail(AsyncVideoError::Timestamp, "timestamp", "Media timestamp exceeds signed 64-bit timeline range");
	}

	bool openTrack(Track& track, int index, AsyncVideoError failure)
	{
		track.stream = format->streams[index];
		if (!validTimeBase(track.stream->time_base))
			return fail(failure, "codec", "Invalid stream time base");
		const auto codec = avcodec_find_decoder(track.stream->codecpar->codec_id);
		if (!codec || !(track.codec = avcodec_alloc_context3(codec)) || !track.frame)
			return fail(failure, "codec", "Selected stream has no available decoder");
		int result = avcodec_parameters_to_context(track.codec, track.stream->codecpar);
		if (result >= 0)
		{
			track.codec->pkt_timebase = track.stream->time_base;
			result = avcodec_open2(track.codec, codec, nullptr);
		}
		if (result < 0)
			return fail(failure, "codec", "Could not open selected decoder", result);
		VINFO("FFmpeg %s, stream %d decoder %s", av_version_info(), index, codec->name);
		return true;
	}

	bool open(cocos2d::io::StreamPtr source, const std::atomic<bool>* cancellation)
	{
		stop = cancellation;
		input = ffmpeg::AvioInput::create(std::move(source), stop);
		format = avformat_alloc_context();
		if (!input || !format)
			return fail(AsyncVideoError::Open, "open", "Could not allocate demuxer");
		format->pb = input->get();
		format->flags |= AVFMT_FLAG_CUSTOM_IO;
		format->interrupt_callback.callback = [](void* opaque) {
			return static_cast<ffmpeg::AvioInput*>(opaque)->isCancelled() ? 1 : 0;
		};
		format->interrupt_callback.opaque = input.get();
		format->io_open = [](AVFormatContext*, AVIOContext**, const char*, int, AVDictionary**) {
			return AVERROR(ioNotImplemented);
		};
		int result = avformat_open_input(&format, nullptr, nullptr, nullptr);
		if (result >= 0)
			result = avformat_find_stream_info(format, nullptr);
		if (result < 0)
			return fail(AsyncVideoError::Open, "probe", "Could not probe media", result);
		const auto vi = av_find_best_stream(format, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
		if (vi < 0 || !openTrack(video, vi, AsyncVideoError::Decode))
			return fail(AsyncVideoError::Open, "video", "No playable video stream", vi);
		for (unsigned int i = 0; i < format->nb_streams; ++i)
			if (format->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
				++metadata.audioTracks;
		if (metadata.audioTracks)
		{
			metadata.audioStream = av_find_best_stream(format, AVMEDIA_TYPE_AUDIO, -1, vi, nullptr, 0);
			if (metadata.audioStream < 0 || !openTrack(audio, metadata.audioStream, AsyncVideoError::AudioDecode))
				return fail(AsyncVideoError::AudioDecode, "audio", "No playable recommended audio stream", metadata.audioStream);
		}
		else
			audio.ended = true;
		metadata.width = video.codec->width;
		metadata.height = video.codec->height;
		const auto rate = av_guess_frame_rate(format, video.stream, nullptr);
		metadata.frameRate = validTimeBase(rate) ? av_q2d(rate) : 0.0;
		if (format->duration > 0 && format->duration != AV_NOPTS_VALUE)
			metadata.duration = static_cast<double>(format->duration) / AV_TIME_BASE;
		if (format->start_time == std::numeric_limits<int64_t>::max())
			return fail(AsyncVideoError::Timestamp, "origin", "Container origin is outside the supported timestamp range");
		if (format->start_time != AV_NOPTS_VALUE)
			origin = format->start_time;
		else
		{
			for (const auto* track : {&video, &audio})
				if (track->stream && track->stream->start_time != AV_NOPTS_VALUE)
				{
					int64_t value;
					if (!rescaleTimestamp(track->stream->start_time, track->stream->time_base, microBase, value))
						return fail(AsyncVideoError::Timestamp, "origin", "Stream origin timestamp overflow");
					origin = origin == AV_NOPTS_VALUE ? value : std::min(origin, value);
				}
		}
		// With no metadata origin, retain the first actual output from both selected
		// tracks. An unseen track is never mistaken for a timestamp-less track.
		while (origin == AV_NOPTS_VALUE && (!video.seen && !video.ended || audio.codec && !audio.seen && !audio.ended))
		{
			if (stop && stop->load())
				return false;
			bool progress = false;
			if (!decode(video, !video.ready, progress, AsyncVideoError::Decode) ||
				!decode(audio, !audio.ready, progress, AsyncVideoError::AudioDecode))
				return false;
			if ((!video.seen && !video.ended) || (audio.codec && !audio.seen && !audio.ended))
				if (!readPacket(progress))
					return false;
			if (budgetBlocked)
				return fail(AsyncVideoError::BufferBudget, "origin probe", "Packet budget exhausted before both selected tracks produced their first decoded output");
		}
		if (origin == AV_NOPTS_VALUE)
		{
			for (const auto* track : {&video, &audio})
				if (track->ready && timestamp(track->frame.get()) != AV_NOPTS_VALUE)
				{
					int64_t value;
					if (!rescaleTimestamp(timestamp(track->frame.get()), track->stream->time_base, microBase, value))
						return fail(AsyncVideoError::Timestamp, "origin", "Decoded origin timestamp overflow");
					origin = origin == AV_NOPTS_VALUE ? value : std::min(origin, value);
				}
			if (origin == AV_NOPTS_VALUE)
			{
				origin = 0;
				estimated = true;
				VWARN("No usable media origin; estimating timestamp origin at zero");
			}
		}
		return true;
	}

	bool decode(Track& track, bool allowed, bool& progress, AsyncVideoError failure)
	{
		if (!track.codec || track.ended || track.ready || !allowed)
			return true;
		int result = avcodec_receive_frame(track.codec, track.frame.get());
		if (result >= 0)
		{
			track.ready = track.seen = true;
			progress = true;
			return true;
		}
		if (result == AVERROR_EOF)
		{
			track.ended = true;
			progress = true;
			return true;
		}
		if (result != AVERROR(codecAgain))
			return fail(failure, "receive", "Decoder receive failed", result);
		if (!track.packets.empty())
		{
			auto& front = track.packets.front();
			result = avcodec_send_packet(track.codec, front.packet.get());
			if (result >= 0)
			{
				bytes -= front.bytes;
				--packets;
				track.packets.pop_front();
				progress = true;
			}
			else if (result != AVERROR(codecAgain))
				return fail(failure, "send", "Decoder send failed", result);
		}
		else if (inputEnded && !track.draining)
		{
			result = avcodec_send_packet(track.codec, nullptr);
			if (result >= 0 || result == AVERROR_EOF)
			{
				track.draining = true;
				progress = true;
			}
			else if (result != AVERROR(codecAgain))
				return fail(failure, "drain", "Decoder drain failed", result);
		}
		return true;
	}

	bool readPacket(bool& progress)
	{
		if (inputEnded)
			return true;
		if (packets >= packetLimit || bytes >= packetBudget)
		{
			budgetBlocked = true;
			return true;
		}
		auto packet = ffmpeg::newPacketPtr();
		if (!packet)
			return fail(AsyncVideoError::BufferBudget, "demux", "Could not allocate packet");
		const int result = av_read_frame(format, packet.get());
		if (result == AVERROR(codecAgain))
		{
			needInput = true;
			return true;
		}
		if (result == AVERROR_EOF && !input->readError())
		{
			inputEnded = true;
			progress = true;
			return true;
		}
		if (result < 0)
			return fail(AsyncVideoError::Decode, "demux", "Media input failed", input->readError() ? input->readError() : result);
		progress = true;
		Track* track = packet->stream_index == video.stream->index ? &video :
			audio.stream && packet->stream_index == audio.stream->index && audioEnabled ? &audio : nullptr;
		if (!track)
			return true;
		if (packet->size < 0)
			return fail(AsyncVideoError::BufferBudget, "demux", "Invalid compressed packet length");
		size_t cost = static_cast<size_t>(packet->size);
		for (int i = 0; i < packet->side_data_elems; ++i)
		{
			if (packet->side_data[i].size > packetBudget - std::min(cost, packetBudget))
				return fail(AsyncVideoError::BufferBudget, "demux", "Compressed packet side data exceeds budget");
			cost += packet->side_data[i].size;
		}
		if (cost > packetBudget - bytes)
			return fail(AsyncVideoError::BufferBudget, "demux", "Compressed packet exceeds shared packet budget");
		bytes += cost;
		++packets;
		track->packets.push_back({std::move(packet), cost});
		return true;
	}

	bool prepareVideo()
	{
		if (!video.ready || videoPrepared)
			return true;
		const auto* frame = video.frame.get();
		if (frame->width != metadata.width || frame->height != metadata.height)
			return fail(AsyncVideoError::FrameBudget, "video", "Midstream video size changes are unsupported");
		const int rawBytes = av_image_get_buffer_size(static_cast<AVPixelFormat>(frame->format), frame->width, frame->height, 1);
		if (rawBytes <= 0 || static_cast<size_t>(rawBytes) > videoBudget)
			return fail(AsyncVideoError::FrameBudget, "video", "Pending raw video frame exceeds 64 MiB");
		size_t resident = 0;
		const auto account = [&](const AVBufferRef* buffer) {
			if (!buffer)
				return true;
			if (buffer->size > videoBudget - resident)
				return false;
			resident += buffer->size;
			return true;
		};
		for (const auto* buffer : frame->buf)
			if (!account(buffer))
				return fail(AsyncVideoError::FrameBudget, "video", "Pending raw video buffers exceed 64 MiB");
		for (int i = 0; i < frame->nb_extended_buf; ++i)
			if (!account(frame->extended_buf[i]))
				return fail(AsyncVideoError::FrameBudget, "video", "Pending raw video buffers exceed 64 MiB");
		const auto pts = timestamp(frame);
		if (pts == AV_NOPTS_VALUE)
		{
			estimated = true;
			if (target > 0 && lastVideoTime == AV_NOPTS_VALUE)
				return fail(AsyncVideoError::Seek, "video timestamp", "Exact nonzero seek requires video timestamps");
			if (lastVideoTime == AV_NOPTS_VALUE)
				videoTime = streamStart(video);
			else if (!checkedAdd(lastVideoTime, lastVideoDuration, videoTime))
				return fail(AsyncVideoError::Timestamp, "video timestamp", "Estimated video timestamp overflow");
		}
		else if (!mediaTimestamp(pts, video.stream->time_base, videoTime))
			return false;
		if (lastVideoTime != AV_NOPTS_VALUE && videoTime < lastVideoTime)
			return fail(AsyncVideoError::Timestamp, "video timestamp", "Video timestamp moved backwards after decoder reorder");
		videoDuration = frame->duration > 0 ? av_rescale_q(frame->duration, video.stream->time_base, microBase) :
			lastVideoDuration > 0 ? lastVideoDuration : metadata.frameRate > 0 ? static_cast<int64_t>(AV_TIME_BASE / metadata.frameRate) : 0;
		int64_t end;
		if (videoDuration < 0 || !checkedAdd(videoTime, videoDuration, end))
			return fail(AsyncVideoError::Timestamp, "video timestamp", "Video frame coverage timestamp overflow");
		lastVideoTime = videoTime;
		lastVideoDuration = videoDuration;
		videoEnd = std::max(videoEnd, end);
		if (indexAfterSeek && videoTime >= target)
		{
			// Preroll is decoded but is not counted twice on top of a target-frame
			// estimate. Establish the estimate once from the actual landing PTS.
			int64_t relative;
			if (!checkedSubtract(videoTime, streamStart(video), relative))
				return fail(AsyncVideoError::Timestamp, "video index", "Landing frame index timestamp overflow");
			const double estimate = relative > 0 && metadata.frameRate > 0 ?
				static_cast<double>(relative) / AV_TIME_BASE * metadata.frameRate : 0.0;
			videoIndex = std::isfinite(estimate) && estimate >= 0.0 &&
				estimate < static_cast<double>(std::numeric_limits<int64_t>::max()) ? std::llround(estimate) : 0;
			indexAfterSeek = false;
		}
		videoPrepared = true;
		return error == AsyncVideoError::None;
	}

	int64_t streamStart(const Track& track)
	{
		int64_t result = 0;
		if (track.stream->start_time != AV_NOPTS_VALUE)
			mediaTimestamp(track.stream->start_time, track.stream->time_base, result);
		return result;
	}

	bool buildResampler(const AVFrame* frame)
	{
		const int channels = frame->ch_layout.nb_channels;
		if (frame->sample_rate < 8000 || frame->sample_rate > 192000 || channels < 1 || channels > 8)
			return fail(AsyncVideoError::AudioDecode, "audio format", "Audio format must have 1-8 channels and 8-192 kHz");
		AVChannelLayout layout{};
		if (frame->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC || !av_channel_layout_check(&frame->ch_layout))
		{
			if (channels > 2)
				return fail(AsyncVideoError::AudioDecode, "audio layout", "Multichannel audio requires an explicit supported channel layout");
			av_channel_layout_default(&layout, channels);
		}
		else if (av_channel_layout_copy(&layout, &frame->ch_layout) < 0)
			return fail(AsyncVideoError::AudioDecode, "audio layout", "Could not copy audio channel layout");
		AVChannelLayout stereo = AV_CHANNEL_LAYOUT_STEREO;
		const int result = swr_alloc_set_opts2(&swr, &stereo, AV_SAMPLE_FMT_S16, outputRate,
			&layout, static_cast<AVSampleFormat>(frame->format), frame->sample_rate, 0, nullptr);
		// swr_build_matrix2 normalizes/scales SWR_CH_MAX rows and columns,
		// including unused channels (rematrix.c). A compact 2*channels matrix
		// is insufficient; stride must also cover the full 64-column traversal.
		constexpr int matrixStride = 64;
		std::array<double, matrixStride * matrixStride> matrix{};
		int matrixResult = 0;
		if (channels == 1)
		{
			matrix[0] = matrix[matrixStride] = 1.0;
		}
		else if (channels == 2 && av_channel_layout_compare(&layout, &stereo) == 0)
		{
			matrix[0] = matrix[matrixStride + 1] = 1.0;
		}
		else
			matrixResult = swr_build_matrix2(&layout, &stereo, std::sqrt(0.5), std::sqrt(0.5),
				0.0, 1.0, 1.0, matrix.data(), matrixStride, AV_MATRIX_ENCODING_NONE, nullptr);
		if (result < 0 || !swr || matrixResult < 0)
		{
			av_channel_layout_uninit(&layout);
			return fail(AsyncVideoError::AudioDecode, "resample", "Could not construct stereo resampler matrix", result < 0 ? result : matrixResult);
		}
		int configured = swr_set_matrix(swr, matrix.data(), matrixStride);
		if (configured >= 0)
			configured = swr_init(swr);
		if (configured < 0)
		{
			av_channel_layout_uninit(&layout);
			return fail(AsyncVideoError::AudioDecode, "resample", "Could not initialize resampler", configured);
		}
		av_channel_layout_uninit(&inputLayout);
		inputLayout = layout;
		inputRate = frame->sample_rate;
		inputFormat = static_cast<AVSampleFormat>(frame->format);
		return true;
	}

	bool sameAudioFormat(const AVFrame* frame) const
	{
		if (!swr || frame->sample_rate != inputRate || frame->format != inputFormat || frame->ch_layout.nb_channels != inputLayout.nb_channels)
			return false;
		if (frame->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC)
			return inputLayout.nb_channels <= 2;
		return av_channel_layout_compare(&frame->ch_layout, &inputLayout) == 0;
	}

	bool prepareAudio()
	{
		if (!audio.ready || audioPrepared)
			return true;
		const auto* frame = audio.frame.get();
		const int channels = frame->ch_layout.nb_channels;
		const auto bps = av_get_bytes_per_sample(static_cast<AVSampleFormat>(frame->format));
		if (frame->nb_samples < 0 || frame->sample_rate < 8000 || frame->sample_rate > 192000 || channels < 1 || channels > 8 || bps <= 0 ||
			frame->nb_samples > frame->sample_rate || static_cast<uint64_t>(frame->nb_samples) * channels * bps > rawBudget)
			return fail(AsyncVideoError::BufferBudget, "audio frame", "Raw audio frame exceeds one second or 8 MiB budget");
		const auto pts = timestamp(frame);
		int64_t start;
		if (pts == AV_NOPTS_VALUE)
		{
			estimated = true;
			if (target > 0 && expectedAudio == AV_NOPTS_VALUE)
				return fail(AsyncVideoError::Seek, "audio timestamp", "Exact nonzero seek requires audio timestamps");
			start = expectedAudio == AV_NOPTS_VALUE ? av_rescale_q(streamStart(audio), microBase, sampleBase) : expectedAudio;
		}
		else
		{
			int64_t absolute, originSample;
			if (!rescaleTimestamp(pts, audio.stream->time_base, sampleBase, absolute) ||
				!rescaleTimestamp(origin, microBase, sampleBase, originSample) || !checkedSubtract(absolute, originSample, start))
				return fail(AsyncVideoError::Timestamp, "audio timestamp", "Audio timestamp exceeds signed 64-bit sample timeline");
		}
		if (expectedAudio == AV_NOPTS_VALUE)
		{
			outputPosition = start;
			// The queue is anchored at the requested time. Known late audio starts
			// become small silence blocks; negative preroll is trimmed at delivery.
			if (start > targetSample)
			{
				silence = start - targetSample;
				silencePosition = targetSample;
			}
		}
		else
		{
			int64_t difference;
			if (!checkedSubtract(start, expectedAudio, difference) || difference > outputRate || difference < -outputRate)
				return fail(AsyncVideoError::Timestamp, "audio timestamp", "Audio timestamp discontinuity exceeds one second");
			if (difference > 1)
			{
				pendingGap = difference;
				gap += static_cast<uint64_t>(difference);
			}
			else if (difference < -1)
			{
				pendingOverlap = -difference;
				overlap += static_cast<uint64_t>(-difference);
			}
		}
		// Duration is calculated from decoded (already codec-trimmed) samples.
		if (!checkedAdd(start, av_rescale_q(frame->nb_samples, AVRational{1, frame->sample_rate}, sampleBase), expectedAudio))
			return fail(AsyncVideoError::Timestamp, "audio timestamp", "Audio sample endpoint overflow");
		audioOffset = 0;
		audioDiscontinuityHandled = false;
		audioPrepared = true;
		return error == AsyncVideoError::None;
	}

	bool emitConverted(int converted, bool applyOverlap = true)
	{
		if (converted < 0)
			return fail(AsyncVideoError::AudioDecode, "resample", "Audio conversion failed", converted);
		const int trimBeforeTarget = outputPosition >= targetSample ? 0 :
			outputPosition < targetSample - converted ? converted : static_cast<int>(targetSample - outputPosition);
		int trim = trimBeforeTarget;
		if (!checkedAdd(outputPosition, converted, outputPosition))
			return fail(AsyncVideoError::Timestamp, "resample timestamp", "Converted sample endpoint overflow");
		if (applyOverlap && pendingOverlap)
		{
			const auto count = std::min<int64_t>(converted - trim, pendingOverlap);
			trim += static_cast<int>(count);
			pendingOverlap -= count;
			// Overlapping samples do not advance the media output timeline.
			outputPosition -= count;
		}
		pcmFrames = converted - trim;
		if (trim && pcmFrames)
			std::move(pcm.begin() + trim * 2, pcm.begin() + converted * 2, pcm.begin());
		return true;
	}

	bool convertAudio(bool& progress)
	{
		if (pcmFrames)
			return true;
		if (silence)
		{
			pcmFrames = static_cast<int>(std::min<int64_t>(silence, chunkFrames));
			std::fill_n(pcm.begin(), pcmFrames * 2, int16_t{});
			silence -= pcmFrames;
			silencePosition += pcmFrames;
			progress = true;
			return true;
		}
		if (!audio.ready)
		{
			if (audio.ended && swr && !resamplerEnded)
			{
				uint8_t* output[] = {reinterpret_cast<uint8_t*>(pcm.data())};
				const int converted = swr_convert(swr, output, chunkFrames, nullptr, 0);
				if (!emitConverted(converted))
					return false;
				resamplerEnded = converted == 0;
				progress = true;
			}
			else if (audio.ended)
				resamplerEnded = true;
			return true;
		}
		if (!prepareAudio())
			return false;
		if (silence)
			return convertAudio(progress);
		// Drain an old format before changing it. The new frame remains held.
		if (!audioDiscontinuityHandled && swr && (!sameAudioFormat(audio.frame.get()) || pendingGap || pendingOverlap))
		{
			uint8_t* output[] = {reinterpret_cast<uint8_t*>(pcm.data())};
			const int converted = swr_convert(swr, output, chunkFrames, nullptr, 0);
			if (!emitConverted(converted, false))
				return false;
			progress = true;
			if (converted)
				return true;
			swr_free(&swr);
		}
		audioDiscontinuityHandled = true;
		if (pendingGap)
		{
			pcmFrames = static_cast<int>(std::min<int64_t>(pendingGap, chunkFrames));
			std::fill_n(pcm.begin(), pcmFrames * 2, int16_t{});
			pendingGap -= pcmFrames;
			if (!checkedAdd(outputPosition, pcmFrames, outputPosition))
				return fail(AsyncVideoError::Timestamp, "audio gap", "Gap sample endpoint overflow");
			progress = true;
			return true;
		}
		if (!swr && !buildResampler(audio.frame.get()))
			return false;
		const auto* frame = audio.frame.get();
		const int bytesPerSample = av_get_bytes_per_sample(inputFormat);
		const bool planar = av_sample_fmt_is_planar(inputFormat) != 0;
		const int count = std::min(frame->nb_samples - audioOffset,
			std::max(1, static_cast<int>(av_rescale_rnd(chunkFrames, inputRate, outputRate, AV_ROUND_DOWN))));
		std::array<const uint8_t*, 8> pointers{};
		for (int i = 0; i < (planar ? inputLayout.nb_channels : 1); ++i)
			pointers[i] = frame->extended_data[i] + static_cast<ptrdiff_t>(audioOffset) * bytesPerSample * (planar ? 1 : inputLayout.nb_channels);
		const auto delay = swr_get_delay(swr, inputRate);
		if (delay < 0 || delay > inputRate ||
			av_rescale_q(delay + frame->nb_samples, AVRational{1, inputRate}, sampleBase) > outputRate - chunkFrames ||
			static_cast<uint64_t>(delay) * inputLayout.nb_channels * bytesPerSample +
			static_cast<uint64_t>(frame->nb_samples) * inputLayout.nb_channels * bytesPerSample + sizeof(pcm) > rawBudget)
			return fail(AsyncVideoError::BufferBudget, "resample budget", "Audio frame and conversion delay exceed temporary budget");
		uint8_t* output[] = {reinterpret_cast<uint8_t*>(pcm.data())};
		const int converted = swr_convert(swr, output, chunkFrames, pointers.data(), count);
		if (!emitConverted(converted))
			return false;
		audioOffset += count;
		progress = true;
		if (audioOffset == frame->nb_samples)
		{
			av_frame_unref(audio.frame.get());
			audio.ready = audioPrepared = false;
		}
		return true;
	}

	Step step(bool wantVideo, bool wantAudio)
	{
		if (error != AsyncVideoError::None)
			return Step::Error;
		bool progress = false;
		needInput = false;
		budgetBlocked = false;
		if (wantAudio && audioEnabled && !convertAudio(progress))
			return Step::Error;
		if (!decode(audio, wantAudio && audioEnabled && !pcmFrames, progress, AsyncVideoError::AudioDecode) ||
			!decode(video, wantVideo, progress, AsyncVideoError::Decode) || !prepareVideo())
			return Step::Error;
		if (video.ready && videoPrepared && videoTime < target)
		{
			consumeVideo();
			progress = true;
		}
		if (progress)
			return Step::Progress;
		if (video.ended && (!audioEnabled || audio.ended && resamplerEnded) && !video.ready && !pcmFrames)
			return Step::End;
		// Do not read ahead merely because a caller has stopped consuming outputs.
		// When either track needs supply, the other track may accumulate packets.
		const bool videoNeedsInput = wantVideo && !video.ready && !video.ended;
		const bool audioNeedsInput = wantAudio && audioEnabled && !audio.ready && !pcmFrames && !audio.ended;
		if (!inputEnded && (videoNeedsInput || audioNeedsInput))
		{
			if (!readPacket(progress))
				return Step::Error;
			return needInput ? Step::NeedInput : progress ? Step::Progress : Step::Waiting;
		}
		return Step::Waiting;
	}

	void consumeVideo()
	{
		av_frame_unref(video.frame.get());
		video.ready = videoPrepared = false;
		if (videoIndex >= 0)
			videoIndex = videoIndex < std::numeric_limits<int64_t>::max() ? videoIndex + 1 : -1;
	}

	bool seek(double seconds, bool enableAudio)
	{
		error = AsyncVideoError::None;
		backend = 0;
		stage.clear();
		detail.clear();
		if (!std::isfinite(seconds) || seconds < 0 || seconds > static_cast<double>(std::numeric_limits<int64_t>::max() / AV_TIME_BASE) ||
			metadata.duration > 0 && seconds > metadata.duration)
			return fail(AsyncVideoError::Seek, "seek", "Invalid media seek target");
		const int64_t time = static_cast<int64_t>(std::llround(seconds * AV_TIME_BASE));
		int64_t absolute;
		if (!checkedAdd(origin, time, absolute))
			return fail(AsyncVideoError::Seek, "seek", "Media seek timestamp overflow");
		// Seek the shared demuxer before the target, preserving audio decoder preroll.
		const auto preroll = std::max<int64_t>(0, audio.codec ? av_rescale_q(audio.codec->seek_preroll,
			AVRational{1, std::max(1, audio.codec->sample_rate)}, microBase) : 0);
		const auto requiredPreroll = std::max<int64_t>(preroll, AV_TIME_BASE);
		int64_t position;
		if (!checkedSubtract(absolute, requiredPreroll, position))
			position = std::numeric_limits<int64_t>::min() + 1;
		// Do not clamp this to the common origin: MOV/AAC may carry a negative
		// priming packet even when both stream start_time values are zero.
		// Selecting the audio stream is also essential: a global seek may choose
		// the video keyframe at zero and discard that earlier audio packet.
		const auto* seekStream = enableAudio && audio.stream ? audio.stream : nullptr;
		const auto seekBase = seekStream ? seekStream->time_base : microBase;
		const int seekIndex = seekStream ? seekStream->index : -1;
		int64_t seekTimestamp, maxTimestamp;
		if (!rescaleTimestamp(position, microBase, seekBase, seekTimestamp) ||
			!rescaleTimestamp(absolute, microBase, seekBase, maxTimestamp))
			return fail(AsyncVideoError::Seek, "seek", "Seek timestamp cannot be represented in selected stream time base");
		if (seekStream && seekStream->start_time != AV_NOPTS_VALUE && audio.codec->initial_padding > 0)
		{
			int64_t padding, firstPacket;
			if (!rescaleTimestamp(audio.codec->initial_padding, AVRational{1, std::max(1, audio.codec->sample_rate)}, seekBase, padding) ||
				!checkedSubtract(seekStream->start_time, padding, firstPacket))
				return fail(AsyncVideoError::Seek, "seek", "Audio priming seek timestamp overflow");
			// A request earlier than the first indexed sample may be rejected.
			// Padding chooses the preroll seek point; libavcodec alone trims it.
			seekTimestamp = std::max(seekTimestamp, firstPacket);
		}
		int result = avformat_seek_file(format, seekIndex, std::numeric_limits<int64_t>::min(), seekTimestamp, maxTimestamp, AVSEEK_FLAG_BACKWARD);
		if (result < 0 && position < origin)
		{
			// Some containers reject a request before their legal seek range.
			// Retry its origin without inventing codec-delay sample trimming.
			int64_t originTimestamp;
			if (!rescaleTimestamp(origin, microBase, seekBase, originTimestamp))
				return fail(AsyncVideoError::Seek, "seek", "Seek origin timestamp overflow");
			result = avformat_seek_file(format, seekIndex, std::numeric_limits<int64_t>::min(), originTimestamp, maxTimestamp, AVSEEK_FLAG_BACKWARD);
		}
		if (result < 0)
			return fail(AsyncVideoError::Seek, "seek", "Demuxer could not seek to requested media time", result);
		for (auto* track : {&video, &audio})
		{
			track->packets.clear();
			av_frame_unref(track->frame.get());
			if (track->codec)
				avcodec_flush_buffers(track->codec);
			track->ready = track->draining = track->seen = false;
			track->ended = !track->codec;
		}
		swr_free(&swr);
		av_channel_layout_uninit(&inputLayout);
		bytes = packets = 0;
		inputEnded = false;
		audioEnabled = enableAudio;
		audioPrepared = videoPrepared = resamplerEnded = false;
		pcmFrames = audioOffset = 0;
		silence = pendingGap = pendingOverlap = 0;
		expectedAudio = lastVideoTime = AV_NOPTS_VALUE;
		lastVideoDuration = videoEnd = 0;
		target = time;
		targetSample = av_rescale_q(time, microBase, sampleBase);
		outputPosition = targetSample;
		videoIndex = 0;
		indexAfterSeek = true;
		error = AsyncVideoError::None;
		backend = 0;
		stage.clear();
		detail.clear();
		return true;
	}

	Info metadata;
	std::unique_ptr<ffmpeg::AvioInput> input;
	AVFormatContext* format = nullptr;
	const std::atomic<bool>* stop = nullptr;
	Track video, audio;
	SwsContext* sws = nullptr;
	SwrContext* swr = nullptr;
	AVChannelLayout inputLayout{};
	AVSampleFormat inputFormat = AV_SAMPLE_FMT_NONE;
	int inputRate = 0;
	size_t bytes = 0, packets = 0;
	bool inputEnded = false, audioEnabled = true, needInput = false, estimated = false;
	bool budgetBlocked = false;
	bool indexAfterSeek = false;
	bool videoPrepared = false, audioPrepared = false, resamplerEnded = false, audioDiscontinuityHandled = false;
	int64_t origin = AV_NOPTS_VALUE, target = 0, targetSample = 0;
	int64_t videoTime = 0, videoDuration = 0, videoIndex = 0, videoEnd = 0;
	int64_t lastVideoTime = AV_NOPTS_VALUE, lastVideoDuration = 0;
	int64_t expectedAudio = AV_NOPTS_VALUE, outputPosition = 0;
	int64_t silence = 0, silencePosition = 0, pendingGap = 0, pendingOverlap = 0;
	uint64_t gap = 0, overlap = 0;
	int audioOffset = 0, pcmFrames = 0;
	std::array<int16_t, chunkFrames * 2> pcm{};
	AsyncVideoError error = AsyncVideoError::None;
	int backend = 0;
	std::string stage, detail;
};

VideoAVDecoder::VideoAVDecoder() : impl(std::make_unique<Impl>()) {}
VideoAVDecoder::~VideoAVDecoder() = default;
bool VideoAVDecoder::open(cocos2d::io::StreamPtr source, const std::atomic<bool>* stop) { return impl->open(std::move(source), stop); }
bool VideoAVDecoder::seek(double seconds, bool audioEnabled) { return impl->seek(seconds, audioEnabled); }
VideoAVDecoder::Step VideoAVDecoder::step(bool video, bool audio) { return impl->step(video, audio); }
const VideoAVDecoder::Info& VideoAVDecoder::info() const { return impl->metadata; }
bool VideoAVDecoder::hasVideo() const { return impl->video.ready && impl->videoPrepared; }
VideoAVDecoder::Video VideoAVDecoder::video() const
{
	return {impl->videoIndex, static_cast<double>(impl->videoTime) / AV_TIME_BASE,
		static_cast<double>(impl->videoDuration) / AV_TIME_BASE};
}
bool VideoAVDecoder::convertVideo(uint8_t* rgba, int stride)
{
	const auto* frame = impl->video.frame.get();
	impl->sws = sws_getCachedContext(impl->sws, frame->width, frame->height, static_cast<AVPixelFormat>(frame->format),
		impl->metadata.width, impl->metadata.height, AV_PIX_FMT_RGBA, SWS_BILINEAR, nullptr, nullptr, nullptr);
	if (!impl->sws)
		return impl->fail(AsyncVideoError::Decode, "video convert", "Could not create RGBA converter");
	uint8_t* data[] = {rgba, nullptr, nullptr, nullptr};
	const int strides[] = {stride, 0, 0, 0};
	return sws_scale(impl->sws, frame->data, frame->linesize, 0, frame->height, data, strides) == impl->metadata.height ||
		impl->fail(AsyncVideoError::Decode, "video convert", "RGBA conversion failed");
}
void VideoAVDecoder::consumeVideo() { impl->consumeVideo(); }
VideoAVDecoder::Audio VideoAVDecoder::audio() const { return {impl->pcm.data(), static_cast<size_t>(impl->pcmFrames)}; }
void VideoAVDecoder::consumeAudio() { impl->pcmFrames = 0; }
bool VideoAVDecoder::videoEnded() const { return impl->video.ended && !impl->video.ready; }
bool VideoAVDecoder::audioEnded() const { return !impl->audio.codec || !impl->audioEnabled || impl->audio.ended && impl->resamplerEnded && !impl->pcmFrames; }
double VideoAVDecoder::videoEndSeconds() const { return static_cast<double>(impl->videoEnd) / AV_TIME_BASE; }
size_t VideoAVDecoder::packetBytes() const { return impl->bytes; }
size_t VideoAVDecoder::packetCount() const { return impl->packets; }
bool VideoAVDecoder::packetBudgetBlocked() const { return impl->budgetBlocked; }
bool VideoAVDecoder::timestampEstimated() const { return impl->estimated; }
uint64_t VideoAVDecoder::gapFrames() const { return impl->gap; }
uint64_t VideoAVDecoder::overlapFrames() const { return impl->overlap; }
AsyncVideoError VideoAVDecoder::error() const { return impl->error; }
int VideoAVDecoder::backendError() const { return impl->backend; }
const char* VideoAVDecoder::errorStage() const { return impl->stage.c_str(); }
const char* VideoAVDecoder::errorMessage() const { return impl->detail.c_str(); }
