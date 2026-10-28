#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioPool.h"
#include "AudioFilter.h"
#include "AudioCommon.h"
#include "base/CCRef.h"
#include "math/Vec3.h"
#include <array>
#include <cstdint>
#include <limits>
#include <stack>
#include <vector>

NS_CC_BEGIN

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	// OpenAL on iOS barfs if the max distance is +inf.
	static const float MAX_ATTENUATION_DISTANCE = 1000000.0f;
#else
	static const float MAX_ATTENUATION_DISTANCE = std::numeric_limits<float>::max();
#endif

	class CC_DLL AudioEngine;
	class CC_DLL AudioPool;
	class CC_DLL AudioSoundData;
	class CC_DLL AudioDecoder;

	// Basically just a reference-counted non-streaming OpenAL buffer object.
	class CC_DLL AudioStaticDataBuffer : public cocos2d::Ref
	{
	public:
		AudioStaticDataBuffer(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
		virtual ~AudioStaticDataBuffer();
		ALuint getBuffer() const {
			return buffer;
		}
		ALsizei getSize() const {
			return size;
		}

		/**
		 * Re-uploads the buffer after the OpenAL context was recreated
		 * (audio device disconnect recovery): the previous AL id died with
		 * the context, so a fresh id is generated and the retained PCM copy
		 * is uploaded again. Updates the generation, so later calls are
		 * cheap no-ops.
		 */
		void reload();

		/**
		 * The AudioEngine device generation this buffer was created/uploaded for.
		 * If it differs from AudioEngine::getDeviceGeneration(), the stored AL id
		 * is stale and the buffer must be reloaded (see reload()).
		 */
		int getGeneration() const {
			return generation;
		}
	private:
		ALuint buffer;
		ALsizei size;
		// Retained data copy for re-uploading after a context recreation
		std::vector<uint8_t> data;
		ALenum format;
		ALsizei freq;
		int generation;
	};

	/**
	 * A AudioSource represents audio you can play back.
	 * 
	 * You can do interesting things with Sources, like set the volume, pitch, and its position relative to the listener.
	 * Please note that positional audio only works for mono (i.e. non-stereo) sources.
	 * Initialize AudioEngine before creating or playing Sources. Factories return
	 * nullptr while the engine is stopped; retain autoreleased Sources for the
	 * entire playback lifetime (AudioPool does not retain them).
	 */
	class CC_DLL AudioSource : public cocos2d::Ref
	{
		friend class AudioPool;
		friend class AudioEngine;
	public:

		enum class Type
		{
			STATIC, // play from AudioSoundData
			STREAM, // play from AudioDecoder
			QUEUE,  // play with queue
			MAX_ENUM
		};

	private:

		AudioSource();
		bool initWithSoundData(AudioSoundData *soundData);
		bool initWithDecoder(AudioDecoder *decoder);
		bool init(int sampleRate, int bitDepth, int channels, int buffers);
		bool initWithOther(const AudioSource &s);

	public:

		virtual ~AudioSource();

		/**
		 * Creates AudioSource from a AudioSoundData, which holds the whole audio data.
		 */
		static AudioSource* createFromSoundData(AudioSoundData* soundData);
		/**
		 * Creates AudioSource from a AudioDecoder. The audio is decoded in chunks when needed.
		 */
		static AudioSource* createFromDecoder(AudioDecoder* decoder);
		/**
		 * Creates AudioSource from without data source. The audio data must be manually queued by the user.
		 */
		static AudioSource* create(int sampleRate, int bitDepth, int channels, int buffers);
		/**
		 * Creates an identical copy of the AudioSource in the stopped state.
		 * Will save memory and time when the AudioSource is static.
		 * @note Cloned Sources inherit all the set-able state of the original AudioSource, but they are initialized stopped.
		 * @return The new identical copy of this AudioSource.
		 */
		virtual AudioSource* clone();
		/**
		 * Starts playing the AudioSource.
		 * @return Whether the AudioSource was able to successfully start playing.
		 */
		virtual bool play();
		/** Stops the AudioSource. */
		virtual void stop();
		/** Pauses the AudioSource. */
		virtual void pause();
		/**
		 * Returns whether the AudioSource is playing.
		 * @return True if the AudioSource is playing, false otherwise.
		 */
		virtual bool isPlaying() const;
		virtual bool isFinished() const;
		// run in a seperate thread
		virtual bool update();
		/**
		 * Sets the pitch of the AudioSource.
		 * @param value Calculated with regard to 1 being the base pitch.
		 *  Each reduction by 50 percent equals a pitch shift of -12 semitones (one octave reduction).
		 *  Each doubling equals a pitch shift of 12 semitones (one octave increase).
		 *  Zero is not a legal value.
		 */
		virtual void setPitch(float value);
		/**
		 * Gets the current pitch of the AudioSource.
		 * @return The pitch, where 1.0 is normal.
		 */
		virtual float getPitch() const;
		/**
		 * Sets the current volume of the AudioSource.
		 * @param value The volume for a AudioSource, where 1.0 is normal volume. Volume cannot be raised above 1.0.
		 */
		virtual void setVolume(float value);
		/**
		 * Gets the current volume of the AudioSource.
		 * @return The volume of the AudioSource, where 1.0 is normal volume.
		 */
		virtual float getVolume() const;
		/**
		 * Sets the currently playing position of the AudioSource.
		 * @param offset The position to seek to in frames.
		 */
		virtual void seek(int64_t offset);
		/**
		 * Gets the currently playing position of the AudioSource.
		 * @return The currently playing position of the AudioSource in frames.
		 */
		virtual int64_t tell();
		/** Gets total frames of the AudioSource. */
		virtual int64_t getTotalFrames();
		/**
		 * Sets the currently playing position of the AudioSource.
		 * @param seconds The position to seek to in seconds.
		 */
		virtual void setTime(double seconds);
		/**
		 * Gets the currently playing position of the AudioSource.
		 * @return The currently playing position of the AudioSource in seconds.
		 */
		virtual double getTime();
		/** Gets total seconds of the AudioSource. */
		virtual double getTotalTime();
		/**
		 * Sets the position of the AudioSource.
		 * @note This only works for mono (i.e. non-stereo) sound files.
		 * @param v The position of the AudioSource.
		 */
		virtual void setPosition(const cocos2d::Vec3& v);
		/**
		 * Gets the position of the AudioSource.
		 * @return The position of the AudioSource.
		 */
		virtual cocos2d::Vec3 getPosition();
		/**
		 * Sets the velocity of the AudioSource.
		 * This does not change the position of the AudioSource, but lets the application know
		 * how it has to calculate the doppler effect.
		 * @param v The velocity vector.
		 */
		virtual void setVelocity(const cocos2d::Vec3& v);
		/**
		 * Gets the velocity of the AudioSource.
		 * @return The velocity vector.
		 */
		virtual cocos2d::Vec3 getVelocity();
		/**
		 * Sets the direction vector of the AudioSource.
		 * A zero vector makes the source non-directional.
		 * @param v The direction vector.
		 */
		virtual void setDirection(const cocos2d::Vec3& v);
		/**
		 * Gets the direction of the AudioSource.
		 * @return The direction vector.
		 */
		virtual cocos2d::Vec3 getDirection();
		/**
		 * Sets the AudioSource's directional volume cones. Together with AudioSource:setDirection,
		 * the cone angles allow for the AudioSource's volume to vary depending on its direction.
		 * @param innerAngle The inner angle from the AudioSource's direction, in radians.
		 *  The AudioSource will play at normal volume if the listener is inside the cone defined by this angle.
		 * @param outerAngle The outer angle from the AudioSource's direction, in radians.
		 *  The AudioSource will play at a volume between the normal and outer volumes, if the listener is in between the cones defined by the inner and outer angles.
		 * @param outerVolume The AudioSource's volume when the listener is outside both the inner and outer cone angles.
		 * @param outerHighGain AL_CONE_OUTER_GAINHF in exf.
		 */
		virtual void setCone(float innerAngle, float outerAngle, float outerVolume, float outerHighGain);
		virtual void setCone(const std::array<float, 4>& param);
		/**
		 * Gets the AudioSource's directional volume cones.
		 * @return An array contains innerAngle, outerAngle, outerVolume, outerHighGain. 
		 */
		virtual std::array<float, 4> getCone();
		/**
		 * Sets whether the AudioSource's position, velocity, direction, and cone angles are relative to the listener, or absolute.
		 *
		 * By default, all sources are absolute and therefore relative to the origin of love's coordinate system [0, 0, 0].
		 * Only absolute sources are affected by the position of the listener. Please note that positional audio only works for mono (i.e. non-stereo) sources.
		 * @param enable True to make the position, velocity, direction and cone angles relative to the listener, false to make them absolute.
		 */
		virtual void setRelative(bool enable);
		/**
		 * Gets whether the AudioSource's position, velocity, direction, and cone angles are relative to the listener.
		 * @return True if the position, velocity, direction and cone angles are relative to the listener, false if they're absolute.
		 */
		virtual bool isRelative();
		/**
		 * Sets whether the AudioSource should loop.
		 * When music loops, it will play forever until stopped or paused.
		 * @param enable True if the source should loop, false otherwise.
		 */
		void setLooping(bool enable);
		/**
		 * Returns whether the AudioSource will loop.
		 * @return True if the AudioSource will loop, false otherwise.
		 */
		bool isLooping() const;
		/**
		 * Sets start and end points for looping of the AudioSource.
		 * When music loops, it will play until tEnd and then rewind to tStart.
		 * @param tStart Looping start time in seconds. Default is 0.
		 * @param tEnd  Looping end time in seconds. Default is total time of the AudioSource.
		 */
		void setLoopingPoint(double tStart, double tEnd);
		/**
		 * Returns whether the AudioSource supports looping point.
		 * @return True if the AudioSource supports looping point, false otherwise.
		 */
		bool isSupportLoopingPoint() const;
		/**
		 * Returns the looping start time of the AudioSource.
		 * @return The looping start time in seconds.
		 */
		double getLoopingStart() const;
		/**
		 * Returns the looping end time of the AudioSource.
		 * @return The looping end time in seconds.
		 */
		double getLoopingEnd() const;
		/**
		 * Sets the volume limits of the AudioSource. The limits have to be numbers from 0 to 1.
		 * @param v The minimum volume.
		 */
		virtual void setMinVolume(float v);
		/**
		 * Returns the volume limits of the AudioSource.
		 * @return The minimum volume.
		 */
		virtual float getMinVolume() const;
		/**
		 * Sets the volume limits of the AudioSource. The limits have to be numbers from 0 to 1.
		 * @param v The maximum volume.
		 */
		virtual void setMaxVolume(float v);
		/**
		 * Returns the volume limits of the AudioSource.
		 * @return The maximum volume.
		 */
		virtual float getMaxVolume() const;

		/**
		 * Sets the rolloff factor which affects the strength of the used distance attenuation.
		 * @param value The rolloff factor.
		 */
		virtual void setRolloffFactor(float value);
		/**
		 * Returns the rolloff factor of the AudioSource.
		 * @return The rolloff factor.
		 */
		virtual float getRolloffFactor();
		/**
		 * Sets the reference attenuation distances of the AudioSource.
		 * 
		 * The parameters, combined with the current DistanceModel, affect how the AudioSource's volume attenuates based on distance.
		 * Distance attenuation is only applicable to Sources based on mono (rather than stereo) audio.
		 * @param value The new reference attenuation distance. If the current DistanceModel is clamped,
		 * this is the minimum distance before the AudioSource is no longer attenuated.
		 */
		virtual void setReferenceDistance(float value);
		/**
		 * Gets the reference attenuation distances of the AudioSource.
		 * @see setReferenceDistance
		 * @return The current reference attenuation distance.
		 */
		virtual float getReferenceDistance();
		/**
		 * Sets the maximum attenuation distances of the AudioSource.
		 *
		 * The parameters, combined with the current DistanceModel, affect how the AudioSource's volume attenuates based on distance.
		 * Distance attenuation is only applicable to Sources based on mono (rather than stereo) audio.
		 * @param value The new maximum attenuation distance.
		 */
		virtual void setMaxDistance(float value);
		/**
		 * Gets the maximum attenuation distances of the AudioSource.
		 * @see setMaxDistance
		 * @return The current maximum attenuation distance.
		 */
		virtual float getMaxDistance();
		/**
		 * Sets the amount of air absorption applied to the AudioSource.
		 *
		 * By default the value is set to 0 which means that air absorption effects are disabled.
		 * A value of 1 will apply high frequency attenuation to the AudioSource at a rate of 0.05 dB per meter.
		 *
		 * Air absorption can simulate sound transmission through foggy air, dry air, smoky atmosphere, etc.
		 * It can be used to simulate different atmospheric conditions within different locations in an area.
		 * @param value The amount of air absorption applied to the AudioSource. Must be between 0 and 10.
		 */
		virtual void setAirAbsorptionFactor(float value);
		/**
		 * Gets the amount of air absorption applied to the AudioSource.
		 * @see setAirAbsorptionFactor
		 * @return The amount of air absorption applied to the AudioSource.
		 */
		virtual float getAirAbsorptionFactor();

		virtual int getChannelCount() const;
		virtual int getSampleRate() const;
		virtual int getBitDepth() const;
		virtual int getBytesPerFrame() const;

		/**
		 * Sets a low-pass, high-pass, or band-pass filter to apply when playing the AudioSource.
		 * @note While the cutoff frequency cannot be set directly, changing high/lowgain has the effect of altering the cutoff.
		 * @param params The filter settings to use for this AudioSource.
		 * @return Whether the filter was successfully applied to the AudioSource.
		 */
		virtual bool setFilter(const AudioFilter::ParamMap& params);
		/**
		 * Disables filtering on this AudioSource.
		 */
		virtual bool removeFilter();
		/**
		 * Gets the filter settings currently applied to the AudioSource.
		 * @return The filter settings to use for this AudioSource, or empty map if the AudioSource has no active filter.
		 */
		virtual AudioFilter::ParamMap getFilter();

		/**
		 * Applies the given previously defined effect to this AudioSource.
		 * @param name The name of the effect previously set up with AudioEngine::setEffect.
		 * @return Whether the effect was successfully applied to this AudioSource.
		 */
		virtual bool setEffect(const std::string& name);
		/**
		 * Applies the given previously defined effect to this AudioSource,
		 * and applies a filter to the AudioSource which affects the sound fed into the effect.
		 * @param name The name of the effect previously set up with AudioEngine::setEffect.
		 * @param filterParams The filter settings to apply prior to the effect.
		 * @return Whether the effect and filter were successfully applied to this AudioSource.
		 */
		virtual bool setEffect(const std::string& name, const AudioFilter::ParamMap& filterParams);
		/**
		 * Disables the effect.
		 * @param name The name of the effect previously set up with AudioEngine::setEffect.
		 */
		virtual bool removeEffect(const std::string& name);
		/**
		 * Gets the filter settings associated to a specific effect.
		 *
		 * This function returns empty map if the effect was applied with no filter settings associated to it.
		 * @param name The name of the effect.
		 * @return The settings for the filter associated to this effect.
		 */
		virtual AudioFilter::ParamMap getEffect(const std::string& name);
		/**
		 * Gets a list of the AudioSource's active effect names.
		 * @return A list of the source's active effect names.
		 */
		virtual std::vector<std::string> getActiveEffects() const;

		/**
		 * Gets the number of free buffer slots in a queueable AudioSource.
		 * 
		 * If the queueable AudioSource is playing, this value will increase up to the amount the AudioSource was created with.
		 *
		 * If the queueable AudioSource is stopped, it will process all of its internal buffers first, in which case this
		 * function will always return the amount it was created with.
		 * @return How many more AudioSoundData objects can be queued up.
		 */
		virtual int getFreeBufferCount() const;

		virtual bool queueData(void* data, size_t length, int dataSampleRate, int dataBitDepth, int dataChannels);

		/**
		 * Queues AudioSoundData for playback in a queueable AudioSource.
		 * @param data The data to queue. The AudioSoundData's sample rate, bit depth, and channel count must match the AudioSource's.
		 * @param offset 
		 * @param length 
		 * @return True if the data was successfully queued for playback, false if there were no available buffers to use for queueing.
		 */
		virtual bool queue(AudioSoundData* data, ssize_t offset = -1, ssize_t length = -1);

	protected:

		void prepareAtomic();
		void teardownAtomic();
		/** Recreates all AL objects after the context was recreated (device
		 *  disconnect recovery); updates bufferGeneration. */
		void regenerateBuffers();

		bool playAtomic(ALuint source);
		void stopAtomic();
		void pauseAtomic();
		void resumeAtomic();

	public:

		/**
		 * Gets the type of the AudioSource.
		 * @return The type of the source.
		 */
		Type getType() const { return sourceType; }

		size_t copyBuffer(char* dst, size_t size, size_t offset);
		int64_t getBufferOffset();

		std::string getLastError() const { return lastError; }

		/**
		 * Starts playing multiple Sources simultaneously.
		 * @param sources Sources to play.
		 * @return True if all sources successfully played, false if there is error.
		 */
		static bool playBatch(const std::vector<AudioSource*>& sources);
		/**
		 * Simultaneously stops all given Sources.
		 * @param sources Sources to stop.
		 */
		static void stopBatch(const std::vector<AudioSource*>& sources);
		/**
		 * Pauses the given Sources.
		 * @param sources Sources to pause.
		 */
		static void pauseBatch(const std::vector<AudioSource*>& sources);

		static std::vector<AudioSource*> pauseAll();
		static void stopAll();

	private:

		// Caller holds the pool lock, including across device recovery.
		static bool playBatchAtomic(AudioPool* pool, const std::vector<AudioSource*>& sources);

		bool releaseSource(bool stop = true);

		void reset();

		int streamAtomic(ALuint buffer, AudioDecoder *d);

		void InvalidFormatException(int channelCount, int bitDepth);
		void SpatialSupportException();
		void QueueLoopingException();
		void QueueTypeMismatchException();
		void QueueFormatMismatchException();
		void QueueMalformedLengthException(int bytesPerSample);

		Type sourceType;
		AudioPool* pool = nullptr;
		ALuint source = 0;
		bool valid = false;
		std::string lastError;

		// The AudioEngine device generation the current AL ids (buffers, stream
		// buffers) were created for. prepareAtomic() compares it with
		// AudioEngine::getDeviceGeneration() and regenerates the ids when the
		// context was recreated (device disconnect recovery).
		int bufferGeneration = 0;

		const static int DEFAULT_BUFFERS = 8;
		const static int MAX_BUFFERS = 64;
		std::queue<ALuint> streamBuffers;
		std::stack<ALuint> unusedBuffers;

		AudioStaticDataBuffer* staticBuffer = nullptr;

		float pitch = 1.0f;
		float volume = 1.0f;
		cocos2d::Vec3 position;
		cocos2d::Vec3 velocity;
		cocos2d::Vec3 direction;
		bool relative = false;
		bool looping = false;
		float minVolume = 0.0f;
		float maxVolume = 1.0f;
		float referenceDistance = 1.0f;
		float rolloffFactor = 1.0f;
		float absorptionFactor = 0.0f;
		float maxDistance = MAX_ATTENUATION_DISTANCE;

		struct Cone
		{
			int innerAngle = 360; // degrees
			int outerAngle = 360; // degrees
			float outerVolume = 0.0f;
			float outerHighGain = 1.0f;
		} cone;

		int64_t offsetSamples = 0;

		int sampleRate = 0;
		int channels = 0;
		int bitDepth = 0;

		AudioDecoder* decoder = nullptr;

		uint64_t toLoop = 0;
		int64_t bufferedBytes = 0;
		int buffers = 0;

		AudioFilter* directfilter = nullptr;

		struct EffectMapStorage
		{
			AudioFilter* filter;
			ALuint slot, target;
		};
		std::map<std::string, EffectMapStorage> effectmap;
		std::stack<ALuint> slotlist;
	};	
NS_CC_END
