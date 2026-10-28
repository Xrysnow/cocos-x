#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioSoundData.h"
#include "AudioCommon.h"
#include "base/CCRef.h"
#include <string>

NS_CC_BEGIN
	/**
	 * Represents an audio input device capable of recording sounds.
	 */
	class CC_DLL AudioRecordingDevice : public cocos2d::Ref
	{
	public:

		static constexpr int DEFAULT_SAMPLES = 8192;
		static constexpr int DEFAULT_SAMPLE_RATE = 8000;
		static constexpr int DEFAULT_BIT_DEPTH = 16;
		static constexpr int DEFAULT_CHANNELS = 1;

	protected:
		friend class AudioEngine;
		AudioRecordingDevice(const char *name);
	public:
		virtual ~AudioRecordingDevice();

		/**
		 * Begins recording audio using this device.
		 * @note A ring buffer is used internally to store recorded data before AudioRecordingDevice:getData or
		 * AudioRecordingDevice:stop are called; the former clears the buffer. If the buffer completely fills up
		 * before getData or stop are called, the oldest data that doesn't fit into the buffer will be lost.
		 * @param samples The maximum number of samples to store in an internal ring buffer when recording.
		 * AudioRecordingDevice:getData clears the internal buffer when called.
		 * @param sampleRate The number of samples per second to store when recording.
		 * @param bitDepth The number of bits per sample (8 or 16).
		 * @param channels Whether to record in mono or stereo. Most microphones don't support more than 1 channel.
		 * @return True if the device successfully began recording using the specified parameters, false if not.
		 */
		virtual bool start(int samples, int sampleRate, int bitDepth, int channels);

		/**
		 * Stops recording audio from this device. 
		 */
		virtual void stop();

		/**
		 * Gets all recorded audio AudioSoundData stored in the device's internal ring buffer.
		 * 
		 * The internal ring buffer is cleared when this function is called, so calling it again will only
		 * get audio recorded after the previous call. If the device's internal ring buffer completely fills up
		 * before getData is called, the oldest data that doesn't fit into the buffer will be lost.
		 * @return The recorded audio data, or null if the device isn't recording.
		 */
		virtual AudioSoundData* getData();

		/**
		 * Gets the name of the recording device.
		 * @return The name of the device.
		 */
		virtual std::string getName() const;

		/**
		 * Gets the number of currently recorded samples.
		 * @return The number of samples that have been recorded so far.
		 */
		virtual int getSampleCount() const;

		/**
		 * Gets the maximum number of samples that will be buffered, as set by start().
		 */
		virtual int getMaxSamples() const;

		/**
		 * Gets the number of samples per second currently being recorded.
		 * @return The number of samples being recorded per second (sample rate).
		 */
		virtual int getSampleRate() const;

		/**
		 * Gets the number of bits per sample in the data currently being recorded.
		 * @return The number of bits per sample in the data that's currently being recorded.
		 */
		virtual int getBitDepth() const;

		/**
		 * Gets the number of channels currently being recorded (mono or stereo).
		 * @return The number of channels being recorded (1 for mono, 2 for stereo).
		 */
		virtual int getChannelCount() const;

		/**
		 * Gets whether the device is currently recording.
		 * @return True if the AudioRecordingDevice is recording, false otherwise.
		 */
		virtual bool isRecording() const;

	private:

		int samples = DEFAULT_SAMPLES;
		int sampleRate = DEFAULT_SAMPLE_RATE;
		int bitDepth = DEFAULT_BIT_DEPTH;
		int channels = DEFAULT_CHANNELS;

		std::string name;
		ALCdevice *device = nullptr;

		std::string lastError;
	};
NS_CC_END
