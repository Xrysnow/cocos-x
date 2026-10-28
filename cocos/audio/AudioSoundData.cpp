#include "AudioSoundData.h"
#include "AudioDecoder.h"
#include "AudioEngine.h"

#include <cstring>
#include <limits>
#include <new>
#include <vector>

NS_CC_BEGIN
using namespace AudioInternal;

#define Exception(STR, ...) lastError = string_format(STR, ##__VA_ARGS__); return

/*
AudioSoundData::AudioSoundData(AudioDecoder *decoder)
	: data(0)
	, size(0)
	, sampleRate(AudioDecoder::DEFAULT_SAMPLE_RATE)
	, bitDepth(0)
	, channels(0)
{
	if (decoder->getBitDepth() != 8 && decoder->getBitDepth() != 16)
	{
		Exception("Invalid bit depth: %d", decoder->getBitDepth());
	}

	size_t bufferSize = 524288; // 0x80000
	int decoded = decoder->decode();

	while (decoded > 0)
	{
		// Expand or allocate buffer. Note that realloc may move
		// memory to other locations.
		if (!data || bufferSize < size + decoded)
		{
			while (bufferSize < size + decoded)
				bufferSize <<= 1;
			data = (uint8_t *)realloc(data, bufferSize);
		}

		if (!data)
		{
			Exception("Not enough memory.");
		}

		// Copy memory into new part of memory.
		memcpy(data + size, decoder->getBuffer(), decoded);

		// Overflow check.
		if (size > std::numeric_limits<size_t>::max() - decoded)
		{
			free(data);
			Exception("Not enough memory.");
		}

		// Keep this up to date.
		size += decoded;

		decoded = decoder->decode();
	}

	// Shrink buffer if necessary.
	if (data && bufferSize > size)
		data = (uint8_t *)realloc(data, size);

	channels = decoder->getChannelCount();
	bitDepth = decoder->getBitDepth();
	sampleRate = decoder->getSampleRate();
}
*/

AudioSoundData::AudioSoundData(int samples, int sampleRate, int bitDepth, int channels)
	: data()
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(samples, sampleRate, bitDepth, channels);
}

AudioSoundData::AudioSoundData(void *d, int samples, int sampleRate, int bitDepth, int channels)
	: data()
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(samples, sampleRate, bitDepth, channels, d);
}

AudioSoundData::AudioSoundData(const AudioSoundData &c)
	: data()
	, sampleRate(0)
	, bitDepth(0)
	, channels(0)
{
	load(c.getSampleCount(), c.getSampleRate(), c.getBitDepth(), c.getChannelCount(), c.getData());
}

AudioSoundData::~AudioSoundData()
{
}

AudioSoundData *AudioSoundData::clone() const
{
	return new AudioSoundData(*this);
}

void AudioSoundData::load(int samples, int sampleRate, int bitDepth, int channels, void *newData)
{
	if (samples <= 0)
	{
		Exception("Invalid sample count: %d", samples);
	}

	if (sampleRate <= 0)
	{
		Exception("Invalid sample rate: %d", sampleRate);
	}

	if (bitDepth != 8 && bitDepth != 16)
	{
		Exception("Invalid bit depth: %d", bitDepth);
	}

	if (channels <= 0)
	{
		Exception("Invalid channel count: %d", channels);
	}

	this->sampleRate = sampleRate;
	this->bitDepth = bitDepth;
	this->channels = channels;

	const size_t bytes = (size_t)samples * (size_t)(bitDepth / 8) * (size_t)channels;

	double realsize = samples;
	realsize *= (double)bitDepth / 8 * channels;
	if (realsize > (double)std::numeric_limits<size_t>::max())
	{
		Exception("Data is too big!");
	}

	try
	{
		data.resize(bytes);
	}
	catch (const std::bad_alloc&)
	{
		Exception("Not enough memory.");
	}

	if (newData)
		memcpy(data.data(), newData, bytes);
	else
		memset(data.data(), bitDepth == 8 ? 128 : 0, bytes);
}

void *AudioSoundData::getData() const
{
	return (void *)data.data();
}

size_t AudioSoundData::getSize() const
{
	return data.size();
}

int AudioSoundData::getChannelCount() const
{
	return channels;
}

int AudioSoundData::getBitDepth() const
{
	return bitDepth;
}

int AudioSoundData::getSampleRate() const
{
	return sampleRate;
}

int AudioSoundData::getSampleCount() const
{
	return (int)((data.size() / channels) / (bitDepth / 8));
}

double AudioSoundData::getDuration() const
{
	return double(data.size()) / (double(channels) * sampleRate * bitDepth / 8);
}

void AudioSoundData::setSample(int i, float sample)
{
	// Check range.
	if (i < 0 || (size_t)i >= data.size() / (bitDepth / 8))
	{
		Exception("Attempt to set out-of-range sample!");
	}

	if (bitDepth == 16)
	{
		// 16-bit sample values are signed.
		int16_t *s = (int16_t *)data.data();
		s[i] = (int16_t)(sample * (float)INT16_MAX);
	}
	else
	{
		// 8-bit sample values are unsigned internally.
		data[i] = (uint8_t)((sample * 127.0f) + 128.0f);
	}
}

void AudioSoundData::setSample(int i, int channel, float sample)
{
	if (channel < 1 || channel > channels)
	{
		Exception("Attempt to set sample from out-of-range channel!");
	}

	return setSample(i * channels + (channel - 1), sample);
}

float AudioSoundData::getSample(int i)
{
	// Check range.
	if (i < 0 || (size_t)i >= data.size() / (bitDepth / 8))
	{
		lastError = string_format("Attempt to get out-of-range sample!");
		return 0;
	}

	if (bitDepth == 16)
	{
		// 16-bit sample values are signed.
		int16_t *s = (int16_t *)data.data();
		return (float)s[i] / (float)INT16_MAX;
	}
	else
	{
		// 8-bit sample values are unsigned internally.
		return ((float)data[i] - 128.0f) / 127.0f;
	}
}

float AudioSoundData::getSample(int i, int channel)
{
	if (channel < 1 || channel > channels)
	{
		lastError = string_format("Attempt to get sample from out-of-range channel!");
		return 0;
	}

	return getSample(i * channels + (channel - 1));
}

NS_CC_END
