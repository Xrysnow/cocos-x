#include "AudioRecordingDevice.h"
#include "AudioEngine.h"
#include "AudioSoundData.h"

NS_CC_BEGIN
using namespace AudioInternal;

AudioRecordingDevice::AudioRecordingDevice(const char *name)
	: name(name)
{
}

AudioRecordingDevice::~AudioRecordingDevice()
{
	AudioRecordingDevice::stop();
}

bool AudioRecordingDevice::start(int samples, int sampleRate, int bitDepth, int channels)
{
	const ALenum format = AudioEngine::getFormat(bitDepth, channels);
	if (format == AL_NONE)
	{
		lastError = string_format("Recording %d channels with %d bits per sample is not supported.", channels, bitDepth);
		return false;
	}

	if (samples <= 0)
	{
		lastError = "Invalid number of samples.";
		return false;
	}

	if (sampleRate <= 0)
	{
		lastError = "Invalid sample rate.";
		return false;
	}

	if (isRecording())
		stop();

	device = alcCaptureOpenDevice(name.c_str(), sampleRate, format, samples);
	if (device == nullptr)
		return false;

	alcCaptureStart(device);

	this->samples = samples;
	this->sampleRate = sampleRate;
	this->bitDepth = bitDepth;
	this->channels = channels;

	return true;
}

void AudioRecordingDevice::stop()
{
	if (!isRecording())
		return;

	alcCaptureStop(device);
	alcCaptureCloseDevice(device);
	device = nullptr;
}

AudioSoundData* AudioRecordingDevice::getData()
{
	if (!isRecording())
		return nullptr;

	int samples = getSampleCount();
	if (samples == 0)
		return nullptr;

	AudioSoundData* soundData = new AudioSoundData(samples, sampleRate, bitDepth, channels);

	alcCaptureSamples(device, soundData->getData(), samples);

	return soundData;
}

int AudioRecordingDevice::getSampleCount() const
{
	if (!isRecording())
		return 0;

	ALCint samples;
	alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, sizeof(ALCint), &samples);
	return (int)samples;
}

int AudioRecordingDevice::getMaxSamples() const
{
	return samples;
}

int AudioRecordingDevice::getSampleRate() const
{
	return sampleRate;
}

int AudioRecordingDevice::getBitDepth() const
{
	return bitDepth;
}

int AudioRecordingDevice::getChannelCount() const
{
	return channels;
}

std::string AudioRecordingDevice::getName() const
{
	return name;
}

bool AudioRecordingDevice::isRecording() const
{
	return device != nullptr;
}

NS_CC_END
