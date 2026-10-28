#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioCommon.h"
#include <vector>
#include <mutex>
#include <queue>
#include <map>

NS_CC_BEGIN
	class CC_DLL AudioSource;

	class CC_DLL AudioPool
	{
		friend class AudioEngine;
		friend class AudioSource;
		AudioPool();
		virtual ~AudioPool();
		bool init();
		void end();
	public:

		static AudioPool* getInstance();
		static void destroyInstance();

		/**
		 * Checks whether an OpenAL source is available.
		 * @return True if at least one is available, false otherwise.
		 **/
		bool isAvailable();

		/**
		 * Checks whether a AudioSource is currently in the playing list.
		 **/
		bool isPlaying(AudioSource *s);

		void update();

		int getActiveSourceCount() const;
		int getMaxSources() const;

	private:

		std::unique_lock<std::mutex> lock();
		std::vector<AudioSource*> getPlayingSources();

		/**
		 * Makes the specified OpenAL source available for use.
		 * @param source The OpenAL source.
		 **/
		bool releaseSource(AudioSource *source, bool stop = true);

		bool assignSource(AudioSource *source, ALuint &out, char &wasPlaying);
		bool findSource(AudioSource *source, ALuint &out);

		static AudioPool* instance;

		// Maximum possible number of OpenAL sources the pool attempts to generate.
		static const int MAX_SOURCES = 64;

		// OpenAL sources
		ALuint sources[MAX_SOURCES];

		// Total number of created sources in the pool.
		int totalSources;

		// A queue of available sources.
		std::queue<ALuint> available;

		// A map of playing sources.
		std::map<AudioSource*, ALuint> playing;

		// Only one thread can access this object at the same time. This mutex will
		// make sure of that.
		mutable std::mutex mutex;
	};	
NS_CC_END
