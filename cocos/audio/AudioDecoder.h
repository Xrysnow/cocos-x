#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioStream.h"
#include "base/CCRef.h"
#include <cstdint>
#include <string>
#include <vector>

NS_CC_BEGIN
	class CC_DLL AudioDecoder : public cocos2d::Ref
	{
	public:
		enum class DecoderType
		{
			UNKNOWN,
			WAV,
			VORBIS,
			FLAC,
			MP3
		};

		struct AudioInfo
		{
			int64_t totalFrames = 0;
			int64_t bytesPerFrame = 4;
			int64_t sampleRate = 44100;
			int64_t channelCount = 2;
			bool operator==(const AudioInfo& other) const {
				return totalFrames == other.totalFrames&&bytesPerFrame == other.bytesPerFrame&&
					sampleRate == other.sampleRate&&channelCount == other.channelCount;
			}
			bool operator!=(const AudioInfo& other) const {
				return !(*this == other);
			}
			double getTotalTime() const {
				return (double)totalFrames / sampleRate;
			}
			int64_t getBitDepth() const {
				return bytesPerFrame / channelCount * 8;
			}
			std::string toString();
		};

	protected:
		AudioDecoder(size_t bufferSize, DecoderType type);
		virtual ~AudioDecoder();
	public:

		static DecoderType getDecoderTypeFromPath(const std::string& path);

		static AudioDecoder* createFromStream(AudioStream* s, size_t bufferSize, DecoderType type);
		static AudioDecoder* createFromFile(const std::string& path, size_t bufferSize, DecoderType type = DecoderType::UNKNOWN);
		static AudioDecoder* createFromLocalFile(const std::string& path, size_t bufferSize, DecoderType type = DecoderType::UNKNOWN);

		/**
		 * Indicates how many bytes of raw data should be generated at each
		 * call to Decode.
		 **/
		static constexpr int DEFAULT_BUFFER_SIZE = 16384;

		/**
		 * Indicates the quality of the sound.
		 **/
		static constexpr int DEFAULT_SAMPLE_RATE = 44100;

		/**
		 * Default is stereo.
		 **/
		static constexpr int DEFAULT_CHANNELS = 2;

		/**
		 * 16 bit audio is the default.
		 **/
		static constexpr int DEFAULT_BIT_DEPTH = 16;

		/**
		 * Creates a deep of itself. The sound stream can (and should) be
		 * rewound, and does not have to be at the same place.
		 * @return A new AudioDecoder object.
		 **/
		AudioDecoder* clone();

		/**
		 * Decodes the next chunk of the music stream, this will usually be
		 * bufferSize amount of bytes, unless EOF occurs. Zero or negative values
		 * indicate EOF or errors.
		 * @return The number of bytes actually decoded.
		 **/
		virtual int64_t decode();

		virtual int64_t decode(char* dst, uint64_t bytesToRead) = 0;

		/**
		 * Gets the size of the buffer (NOT the size of the entire stream).
		 * @return The size of the buffer.
		 **/
		virtual int getBufferSize() const;

		/**
		 * Gets a pointer to the actual data. The contents of this buffer will
		 * change with each call to decode, so the client must copy the data.
		 * The buffer is owned by the AudioDecoder and is read-only for callers.
		 * @return A read-only view of the raw sound data.
		 **/
		virtual const uint8_t* getBuffer() const;

		/**
		 * Seeks to the specified position, if possible.
		 * @param seconds The position in the stream in seconds.
		 * @return True if success, false on fail/unsupported.
		 **/
		virtual bool seekTime(double seconds);

		/**
		 * Seeks to the specified position, if possible.
		 * @param frameOffset The position in the stream in frames.
		 * @return True if success, false on fail/unsupported.
		 **/
		virtual bool seek(int64_t frameOffset) = 0;

		/**
		 * @brief Tells the current frame offset.
		 * @return The current frame offset.
		 */
		virtual int64_t tell() = 0;

		/**
		 * Rewinds the stream to the start.
		 * @return True if success, false on fail/unsupported.
		 **/
		virtual bool rewind();

		/**
		 * Checks whether a stream is seekable.
		 * @return True if seekable, false otherwise.
		 **/
		virtual bool isSeekable() = 0;

		/**
		 * Checks whether a stream has more data to decode or not. Use
		 * rewind to start the stream again.
		 * @return False if there is more data, true on EOF.
		 **/
		virtual bool isFinished();

		/**
		 * Gets the number of channels in a stream. Supported values are 1 (mono) or 2 (stereo).
		 * @return Either 1 for mono, 2 for stereo, or 0 on errors.
		 **/
		int64_t getChannelCount() const { return audioInfo.channelCount; }

		/**
		 * Gets the number of bits per sample. Supported values are 8 or 16.
		 * @return Either 8, 16, or 0 if unsupported.
		 **/
		int64_t getBitDepth() const { return audioInfo.getBitDepth(); }

		/**
		 * Gets the sample rate for the AudioDecoder, that is, samples per second.
		 * @return The sample rate, eg. 44100.
		 **/
		int64_t getSampleRate() const { return audioInfo.sampleRate; }

		/**
		 * Gets the estimated total duration of the stream. in seconds. May return
		 * -1 if the duration cannot be determined.
		 **/
		double getDuration() const { return audioInfo.getTotalTime(); }

		int64_t getTotalFrames() const { return audioInfo.totalFrames; }
		int64_t getBytesPerFrame() const { return audioInfo.bytesPerFrame; }
		int64_t getBufferOffset() const { return bufferPosition; }

		void setLoopingPoint(double tStart, double tEnd);

		double getLoopingStart();
		double getLoopingEnd();

	protected:

		int64_t getLoopStart() const;
		int64_t getLoopEnd() const;

		AudioStream* stream = nullptr;
		DecoderType decoderType;

		// When the decoder decodes data incrementally, it writes
		// this many bytes at a time (at most).
		int bufferSize;

		// Decode scratch buffer
		std::vector<uint8_t> buffer;
		int64_t bufferPosition = 0;

		AudioInfo audioInfo;
		uint64_t loopStart = 0;
		uint64_t loopEnd = 0;
		// Set this to true when eof has been reached.
		bool eof = false;
	};
NS_CC_END
