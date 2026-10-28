#include "AudioPool.h"
#include "AudioSource.h"
#include <new>

NS_CC_BEGIN
using namespace AudioInternal;

AudioPool* AudioPool::instance = nullptr;

AudioPool::AudioPool()
	: sources()
	, totalSources(0)
{
}

AudioPool::~AudioPool()
{
}

bool AudioPool::init()
{
	// Reset state so it can be called again
	totalSources = 0;
	while (!available.empty())
		available.pop();
	playing.clear();

	// Clear errors.
	alGetError();

	// Generate sources.
	for (int i = 0; i < MAX_SOURCES; i++)
	{
		alGenSources(1, &sources[i]);

		// We might hit an implementation-dependent limit on the total number
		// of sources before reaching MAX_SOURCES.
		if (alGetError() != AL_NO_ERROR)
			break;

		totalSources++;
	}

	if (totalSources < 4)
	{
		AINFO("can not generate enough sources, got %d", totalSources);
		if (totalSources > 0)
			alDeleteSources(totalSources, sources);
		totalSources = 0;
		return false;
	}

#ifdef AL_SOFT_direct_channels
	ALboolean hasext = alIsExtensionPresent("AL_SOFT_direct_channels");
#endif

	// Make all sources available initially.
	for (int i = 0; i < totalSources; i++)
	{
#ifdef AL_SOFT_direct_channels
		if (hasext)
		{
			// Bypass virtualization of speakers for multi-channel sources in OpenAL Soft.
			alSourcei(sources[i], AL_DIRECT_CHANNELS_SOFT, AL_TRUE);
		}
#endif

		available.push(sources[i]);
	}
	return true;
}

void AudioPool::end()
{
	AudioSource::stopAll();
	auto lk = lock();
	// Free all sources.
	if (totalSources > 0)
		alDeleteSources(totalSources, sources);
	totalSources = 0;
	while (!available.empty())
		available.pop();
	playing.clear();
}

AudioPool* AudioPool::getInstance()
{
	if (!instance)
		instance = new (std::nothrow) AudioPool();
	return instance;
}

void AudioPool::destroyInstance()
{
	if (instance)
		instance->end();
	delete instance;
	instance = nullptr;
}

bool AudioPool::isAvailable()
{
	auto lk = lock();
	return !available.empty();
}

bool AudioPool::isPlaying(AudioSource *s)
{
	auto lk = lock();
	return playing.find(s) != playing.end();
}

void AudioPool::update()
{
	auto lk = lock();

	std::vector<AudioSource*> torelease;

	for (const auto &i : playing)
	{
		// finished source will be released
		if (!i.first->update())
			torelease.push_back(i.first);
	}
	for (auto& s : torelease)
		releaseSource(s);
}

int AudioPool::getActiveSourceCount() const
{
	std::lock_guard<std::mutex> lk(mutex);
	return (int)playing.size();
}

int AudioPool::getMaxSources() const
{
	std::lock_guard<std::mutex> lk(mutex);
	return totalSources;
}

std::unique_lock<std::mutex> AudioPool::lock()
{
	return std::unique_lock<std::mutex>{mutex};
}

bool AudioPool::assignSource(AudioSource *source, ALuint &out, char &wasPlaying)
{
	out = 0;

	if (findSource(source, out))
		return wasPlaying = true;

	wasPlaying = false;

	if (available.empty())
		return false;

	out = available.front();
	available.pop();

	playing.insert(std::make_pair(source, out));
	return true;
}

bool AudioPool::releaseSource(AudioSource *source, bool stop)
{
	ALuint s;
	if (findSource(source, s))
	{
		if (stop)
			source->stopAtomic();
		available.push(s);
		playing.erase(source);
		return true;
	}
	return false;
}

bool AudioPool::findSource(AudioSource *source, ALuint &out)
{
	const auto i = playing.find(source);
	if (i == playing.end())
		return false;
	out = i->second;
	return true;
}

std::vector<AudioSource*> AudioPool::getPlayingSources()
{
	std::vector<AudioSource*> sources;
	sources.reserve(playing.size());
	for (auto &i : playing)
		sources.push_back(i.first);
	return sources;
}

NS_CC_END
