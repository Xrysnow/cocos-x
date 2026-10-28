#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioSource.h"
#include "AudioEffect.h"
#include "AudioPool.h"
#include "AudioDecoder.h"
#include "AudioRecordingDevice.h"
#include "base/CCVector.h"
#include <functional>
#include <vector>
#include <stack>
#include <array>
#include <string>
#include <map>
#include <atomic>

NS_CC_BEGIN
	class CC_DLL AudioEngine
	{
	public:
		/** Configure host logging during initialization or complete shutdown. */
		static void setLoggingFunction(const std::function<void(const std::string&)>& callback);
		/** Configure the Android recording-permission request callback. */
		static void setOnRequestRecordPermission(const std::function<bool()>& callback);

		/**
		 * The different distance models.
		 */
		enum class DistanceModel
		{
			/** Sources do not get attenuated. */
			NONE,
			/** Inverse distance attenuation. */
			INVERSE,
			/** Inverse distance attenuation. Gain is clamped. */
			INVERSE_CLAMPED,
			/** Linear attenuation. */
			LINEAR,
			/** Linear attenuation. Gain is clamped. */
			LINEAR_CLAMPED,
			/** Exponential attenuation. */
			EXPONENT,
			/** Exponential attenuation. Gain is clamped. */
			EXPONENT_CLAMPED,
			MAX_ENUM
		};

		/**
		 * Gets the OpenAL format identifier based on number of
		 * channels and bits.
		 * @param channels Number of channels
		 * @param bitDepth Either 8-bit samples, or 16-bit samples.
		 * @return One of AL_FORMAT_*, or AL_NONE if unsupported format.
		 */
		static ALenum getFormat(int bitDepth, int channels);

		/**
		 * Gets the current number of simultaneous playing sources.
		 * @return The current number of simultaneous playing sources.
		 */
		static int getActiveSourceCount();

		/**
		 * Gets the maximum supported number of simultaneous playing sources.
		 * @return The maximum supported number of simultaneous playing sources.
		 */
		static int getMaxSourceCount();

		/**
		 * Simultaneously plays all given Sources.
		 * @param sources A list containing Sources to play.
		 */
		static bool play(const std::vector<AudioSource*> &sources);

		/**
		 * Simultaneously stops all given Sources.
		 * @param sources A list containing Sources to stop.
		 */
		static void stop(const std::vector<AudioSource*> &sources);

		/**
		 * Stops all currently active sources.
		 */
		static void stop();

		/**
		 * Pauses the given Sources.
		 * @param sources A list containing Sources to pause.
		 */
		static void pause(const std::vector<AudioSource*> &sources);

		/**
		 * Pauses all currently active Sources and returns them.
		 * @return A list containing Sources that were paused by this call.
		 */
		static std::vector<AudioSource*> pause();

		/**
		 * Sets the master volume, where 0.0f is min (off) and 1.0f is max.
		 * @param volume The new master volume.
		 */
		static void setVolume(float volume);

		/**
		 * Gets the master volume.
		 * @return The current master volume.
		 */
		static float getVolume();

		/**
		 * Gets the position of the listener.
		 * @note Positional audio only works for mono (i.e. non-stereo) sources.
		 * @return The position of the listener.
		 */
		static cocos2d::Vec3 getPosition();

		/**
		 * Sets the position of the listener.
		 * @param v The position of the listener.
		 */
		static void setPosition(const cocos2d::Vec3& v);

		/**
		 * Gets the orientation of the listener.
		 * @return A vector array of size 2 containing the forward
		 * vector and the up vector of the listener orientation.
		 */
		static std::array<cocos2d::Vec3, 2> getOrientation();

		/**
		 * Sets the orientation of the listener.
		 * @param forward Forward vector of the listener orientation.
		 * @param up Up vector of the listener orientation.
		 */
		static void setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up);

		/**
		 * Gets the velocity of the listener.
		 * @return The velocity of the listener.
		 */
		static cocos2d::Vec3 getVelocity();

		/**
		 * Sets the velocity of the listener.
		 * @param v The velocity of the listener.
		 */
		static void setVelocity(const cocos2d::Vec3& v);

		/**
		 * Sets a global scale factor for velocity-based doppler effects. The default scale value is 1.
		 * @param scale The new doppler scale factor. The scale must be greater than 0.
		 */
		static void setDopplerScale(float scale);

		/**
		 * Gets the current global scale factor for velocity-based doppler effects.
		 * @return The current doppler scale factor.
		 */
		static float getDopplerScale();

		//void setMeter(float scale);

		//float getMeter() const;

		/**
		 * Gets a list of RecordingDevices on the system.
		 *
		 * The first device in the list is the user's default recording device. The list may be empty
		 * if there are no microphones connected to the system.
		 * @return The list of connected recording devices.
		 */
		static std::vector<AudioRecordingDevice*> getRecordingDevices();

		/**
		 * Gets the distance attenuation model. The default is 'INVERSE_CLAMPED'.
		 * @return The current distance model.
		 */
		static DistanceModel getDistanceModel();

		/**
		 * Sets the distance attenuation model.
		 * @param distanceModel The new distance model.
		 */
		static void setDistanceModel(DistanceModel distanceModel);

		/**
		 * Defines an effect that can be applied to a AudioSource.
		 * @note Not all system supports audio effects. Use isEffectsSupported to check.
		 * @param name Name of the effect.
		 * @param params The parameters to use for the effect.
		 * @return Whether the effect was successfully created.
		 */
		static bool setEffect(const std::string& name, const AudioEffect::ParamMap& params);

		/**
		 * Removes the specific effect.
		 * @param name Name of the effect.
		 * @return Whether the effect was successfully removed.
		 */
		static bool removeEffect(const std::string& name);

		/**
		 * Gets parameters of the specific effect.
		 * @param name Name of the effect.
		 * @return AudioEffect parameters.
		 */
		static AudioEffect::ParamMap getEffect(const std::string& name);

		/**
		 * Gets a list of the names of the currently enabled effects.
		 * @return The list of the names of the currently enabled effects.
		 */
		static std::vector<std::string> getActiveEffects();

		/**
		 * Gets maximum number of active effects supported by the system.
		 * @return The maximum number of active effects.
		 */
		static int getMaxEffectCount();

		/**
		 * Gets maximum number of active Effects in a single AudioSource.
		 * @note This function return 0 for system that doesn't support audio effects.
		 * @return The maximum number of active Effects per AudioSource.
		 */
		static int getMaxSourceEffectCount();

		/**
		 * Gets whether audio effects are supported in the system.
		 * @note Older Linux distributions that ship with older OpenAL library may not support audio effects.
		 * Furthermore, iOS doesn't support audio effects.
		 * @return True if effects are supported, false otherwise.
		 */
		static bool isEffectSupported();

		static bool getEffectID(const std::string& name, ALuint &id);

		static void onEnterBackground();
		static void onEnterForeground();
		/** Platform audio-session suspension, independent of app background state. */
		static void onAudioSessionInterruption(bool interrupted);

		static std::string getLastError() { return lastError; }
		static bool isValid() { return valid; }

		/** Initialize once; repeated successful calls keep the existing context.
		 * Lifecycle and suspension notifications must be serialized on the main thread.
		 */
		static bool init();
		/** Stop/join the worker before deleting context objects; safe to repeat. */
		static void end();

		/**
		 * The "device generation": incremented whenever the OpenAL context is
		 * (re)created or destroyed.
		 */
		static int getDeviceGeneration();

		// ---------------------------------------------------------------------
		// Audio device management overview
		// ---------------------------------------------------------------------
		//
		// Problem: OpenAL Soft fixes the output endpoint when the device is
		// opened. When the OS default changes or the device is unplugged, the
		// context keeps mixing into the old (silent) endpoint.
		//
		// Detection (checkDeviceChange(), run ~200ms from the AudioPoolThread):
		//  1. ALC_SOFT_system_events notifications (callback only raises an
		//     atomic flag - it is not allowed to call any OpenAL function);
		//  2. polling alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
		//  3. ALC_EXT_disconnect/ALC_CONNECTED, i.e. the CURRENT open device
		//     was physically removed.
		//
		// Handling:
		//  * Default changed, device still present -> reopenDevice(""):
		//    alcReopenDeviceSOFT(device, NULL, attribs) replaces the device
		//    under the existing context - context, Sources, buffers, effects
		//    and playback positions survive; sound moves over seamlessly.
		//    deviceName NULL is mandatory here: the ALC_DEFAULT*_DEVICE_
		//    SPECIFIER strings are cached snapshots on Windows and still name
		//    the OLD endpoint right after a change - pre-resolving them (or
		//    skipping on "name == lastAppliedDevice") is exactly what made
		//    the audio never switch.
		//  * Current device unplugged -> recoverDisconnectedDevice(): a dead
		//    ALCdevice cannot be revived by alcReopenDeviceSOFT (it keeps
		//    reporting ALC_CONNECTED == ALC_FALSE), so the device+context is
		//    recreated - this makes the audio come back at all. The device
		//    generation is bumped; Sources that were playing/paused before
		//    the teardown are replayed automatically and regenerate their AL
		//    objects lazily (statics re-upload a retained PCM copy, streams
		//    continue from their decoder position; queue sources must be
		//    re-queued by the application).
		//  * Extension unavailable or reopen failed -> the current device is
		//    kept untouched, playback continues there (pre-fix behavior); a
		//    pinned device (reopenDevice with a name) is never overridden by
		//    default changes.
		// ---------------------------------------------------------------------

		/**
		 * Switches the playback device in place (ALC_SOFT_reopen_device).
		 * @param name Empty: follow the current system default (NULL is passed
		 *             to alcReopenDeviceSOFT, see overview); non-empty: switch
		 *             to that exact device name and pin it.
		 * @return True on success; otherwise the current device is kept.
		 */
		static bool reopenDevice(const std::string& name = std::string());

		/**
		 * Periodically checks for device changes and transparently follows the
		 * default device (see the overview above). Called from the AudioPoolThread.
		 */
		static void checkDeviceChange();

	private:

		static void initializeEFX();
		static void resetEFX();
		static void updateSuspension();
		/** Allocates the context's EFX aux effect slots. */
		static void createEffectSlots();
		/** Registers the ALC_SOFT_system_events callback. */
		static void initializeDeviceEvents();
		/**
		 * Recreation path for an unplugged/failed device (see overview):
		 * builds a fresh device+context on the current default, restores the
		 * engine state and auto-resumes the captured Sources. QUEUE sources
		 * are skipped (payloads are not retained; re-queue to play again).
		 */
		static bool recoverDisconnectedDevice();

		static std::atomic<bool> valid;
		// The OpenAL device.
		static ALCdevice *device;

		// The OpenAL context.
		static ALCcontext *context;

		// The OpenAL capture devices.
		static cocos2d::Vector<AudioRecordingDevice*> capture;

		// The OpenAL effects
		struct EffectMapStorage
		{
			AudioEffect *effect;
			ALuint slot;
		};
		static std::map<std::string, struct EffectMapStorage> effectmap;
		static std::stack<ALuint> slotlist;
		static int MAX_SCENE_EFFECTS;
		static int MAX_SOURCE_EFFECTS;

		// The AudioPool.
		static AudioPool *pool;

		static cocos2d::Vector<AudioSource*> tempSources;

		static DistanceModel distanceModel;
		//static float metersPerUnit = 1.0;

		static std::string lastError;

		// Audio device management

		static LPALCREOPENDEVICESOFT alcReopenDeviceSoft;
		static ALint initAttribs[4];
		static bool hasInitAttribs;
		static std::string lastAppliedDevice;
		static std::string lastDefaultName;
		static bool devicePinned;
	};

#ifdef ALC_EXT_EFX
namespace AudioInternal
{
	// AudioEffect objects
	extern CC_DLL LPALGENEFFECTS alGenEffects;
	extern CC_DLL LPALDELETEEFFECTS alDeleteEffects;
	extern CC_DLL LPALISEFFECT alIsEffect;
	extern CC_DLL LPALEFFECTI alEffecti;
	extern CC_DLL LPALEFFECTIV alEffectiv;
	extern CC_DLL LPALEFFECTF alEffectf;
	extern CC_DLL LPALEFFECTFV alEffectfv;
	extern CC_DLL LPALGETEFFECTI alGetEffecti;
	extern CC_DLL LPALGETEFFECTIV alGetEffectiv;
	extern CC_DLL LPALGETEFFECTF alGetEffectf;
	extern CC_DLL LPALGETEFFECTFV alGetEffectfv;

	//AudioFilter objects
	extern CC_DLL LPALGENFILTERS alGenFilters;
	extern CC_DLL LPALDELETEFILTERS alDeleteFilters;
	extern CC_DLL LPALISFILTER alIsFilter;
	extern CC_DLL LPALFILTERI alFilteri;
	extern CC_DLL LPALFILTERIV alFilteriv;
	extern CC_DLL LPALFILTERF alFilterf;
	extern CC_DLL LPALFILTERFV alFilterfv;
	extern CC_DLL LPALGETFILTERI alGetFilteri;
	extern CC_DLL LPALGETFILTERIV alGetFilteriv;
	extern CC_DLL LPALGETFILTERF alGetFilterf;
	extern CC_DLL LPALGETFILTERFV alGetFilterfv;

	// Auxiliary slot object
	extern CC_DLL LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
	extern CC_DLL LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
	extern CC_DLL LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
	extern CC_DLL LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
	extern CC_DLL LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
	extern CC_DLL LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
	extern CC_DLL LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
	extern CC_DLL LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
	extern CC_DLL LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
	extern CC_DLL LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
	extern CC_DLL LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
}
#endif

NS_CC_END
