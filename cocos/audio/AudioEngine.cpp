#include "AudioEngine.h"
#include "AudioALSupport.h"
#include "AudioPlatform.h"
#include <exception>
#include <atomic>
#include <chrono>
#include <algorithm>
#include <functional>
#include <thread>

using namespace std;
NS_CC_BEGIN
using namespace AudioInternal;

namespace
{
#ifdef ALC_SOFT_system_events
	LPALCEVENTCALLBACKSOFT sEventCallbackSOFT = nullptr;
	LPALCEVENTCONTROLSOFT  sEventControlSOFT  = nullptr;
#endif

	std::atomic<bool> sDeviceEventPending{ false };
	const std::chrono::milliseconds sDeviceCheckInterval{ 200 };
	const std::chrono::milliseconds sReopenThrottle{ 500 };
	std::chrono::steady_clock::time_point sLastDeviceCheck{
		std::chrono::steady_clock::now() - sDeviceCheckInterval };
	std::chrono::steady_clock::time_point sLastReopen{
		std::chrono::steady_clock::now() - sReopenThrottle };
	int sRecoveryFailures = 0;

	// "Device generation": incremented whenever the OpenAL context is
	// (re)created/destroyed; Sources use it to detect stale AL ids after a
	// context swap.
	std::atomic<int> sDeviceGeneration{ 0 };
	bool sAppBackground = false;
	bool sSessionInterrupted = false;
	std::atomic<bool> sSuspended{ false };
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(ALC_SOFT_pause_device)
	LPALCDEVICEPAUSESOFT sPauseDevice = nullptr;
	LPALCDEVICERESUMESOFT sResumeDevice = nullptr;
#endif
}

static std::string getDefaultDeviceName()
{
	const ALCchar* name = nullptr;
	// query the real endpoint name
	if (alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT") == ALC_TRUE)
		name = alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
	// fallback
	if (!name || name[0] == '\0')
		name = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	return name ? std::string(name) : std::string();
}

#ifdef ALC_SOFT_system_events
static void ALC_APIENTRY audioDeviceEventCallback(
	ALCenum eventType, ALCenum /*deviceType*/, ALCdevice* /*device*/,
	ALCsizei /*length*/, const ALCchar* /*message*/, void* /*userParam*/) noexcept
{
	switch (eventType)
	{
	case ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT:
	case ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT:
		sDeviceEventPending.store(true, std::memory_order_release);
		break;
	default:
		break;
	}
}
#endif // ALC_SOFT_system_events

class AudioPoolThread
{
protected:
	using _lock = std::unique_lock<std::mutex>;
	AudioPool *pool;
	// Set this to true when the thread should finish.
	// Main thread will write to this value, and AudioPoolThread
	// will read from it.
	volatile bool finish;
	// finish lock
	std::mutex mutex;
	std::thread* worker = nullptr;
public:
	static AudioPoolThread* Instance;

	void threadFunction()
	{
		// Device checks every 40 ticks (~200ms); checkDeviceChange() also
		// throttles internally.
		int deviceCheckTick = 0;
		while (true)
		{
			{
				_lock lock(mutex);
				if (finish)
					return;
			}

			if (++deviceCheckTick >= 40)
			{
				deviceCheckTick = 0;
				AudioEngine::checkDeviceChange();
			}

			pool->update();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	void setFinish()
	{
		_lock lock(mutex);
		finish = true;
	}
	AudioPoolThread(AudioPool *pool)
		: pool(pool)
		, finish(false)
	{
		worker = new std::thread([this] { threadFunction(); });
	}
	~AudioPoolThread()
	{
		//setFinish();
		worker->join();
		delete worker;
	}
};
AudioPoolThread* AudioPoolThread::Instance = nullptr;

std::atomic<bool> AudioEngine::valid{ false };
ALCdevice* AudioEngine::device = nullptr;
ALCcontext* AudioEngine::context = nullptr;
AudioPool* AudioEngine::pool = nullptr;
cocos2d::Vector<AudioRecordingDevice*> AudioEngine::capture{};
cocos2d::Vector<AudioSource*> AudioEngine::tempSources{};
AudioEngine::DistanceModel AudioEngine::distanceModel = DistanceModel::INVERSE_CLAMPED;

std::map<std::string, struct AudioEngine::EffectMapStorage> AudioEngine::effectmap{};
std::stack<ALuint> AudioEngine::slotlist{};

int AudioEngine::MAX_SCENE_EFFECTS = 64;
int AudioEngine::MAX_SOURCE_EFFECTS = 64;
std::string AudioEngine::lastError{};

LPALCREOPENDEVICESOFT AudioEngine::alcReopenDeviceSoft = nullptr;
ALint AudioEngine::initAttribs[4] = { 0, 0, 0, 0 };
bool AudioEngine::hasInitAttribs = false;
std::string AudioEngine::lastAppliedDevice;
std::string AudioEngine::lastDefaultName;
bool AudioEngine::devicePinned = false;

ALenum AudioEngine::getFormat(int bitDepth, int channels)
{
	if (bitDepth != 8 && bitDepth != 16)
		return AL_NONE;

	if (channels == 1)
		return bitDepth == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
	else if (channels == 2)
		return bitDepth == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
#ifdef AL_EXT_MCFORMATS
	else if (alIsExtensionPresent("AL_EXT_MCFORMATS"))
	{
		if (channels == 6)
			return bitDepth == 8 ? AL_FORMAT_51CHN8 : AL_FORMAT_51CHN16;
		else if (channels == 8)
			return bitDepth == 8 ? AL_FORMAT_71CHN8 : AL_FORMAT_71CHN16;
	}
#endif
	return AL_NONE;
}

int AudioEngine::getActiveSourceCount()
{
	return pool ? pool->getActiveSourceCount() : 0;
}

int AudioEngine::getMaxSourceCount()
{
	return pool ? pool->getMaxSources() : 0;
}

int AudioEngine::getDeviceGeneration()
{
	return sDeviceGeneration.load(std::memory_order_acquire);
}

bool AudioEngine::play(const std::vector<AudioSource*> &sources)
{
	return AudioSource::playBatch(sources);
}

void AudioEngine::stop(const std::vector<AudioSource*> &sources)
{
	return AudioSource::stopBatch(sources);
}

void AudioEngine::stop()
{
	AudioSource::stopAll();
}

void AudioEngine::pause(const std::vector<AudioSource*> &sources)
{
	return AudioSource::pauseBatch(sources);
}

std::vector<AudioSource*> AudioEngine::pause()
{
	return AudioSource::pauseAll();
}

void AudioEngine::setVolume(float volume)
{
	volume = std::max(0.f, std::min(volume, 1.f));
	alListenerf(AL_GAIN, volume);
}

float AudioEngine::getVolume()
{
	ALfloat volume;
	alGetListenerf(AL_GAIN, &volume);
	return volume;
}

cocos2d::Vec3 AudioEngine::getPosition()
{
	cocos2d::Vec3 v;
	alGetListenerfv(AL_POSITION, (float*)&v);
	return v;
}

void AudioEngine::setPosition(const cocos2d::Vec3& v)
{
	alListenerfv(AL_POSITION, (float*)&v);
}

std::array<cocos2d::Vec3, 2> AudioEngine::getOrientation()
{
	std::array<cocos2d::Vec3, 2> v;
	alGetListenerfv(AL_ORIENTATION, (float*)v.data());
	return v;
}

void AudioEngine::setOrientation(const cocos2d::Vec3& forward, const cocos2d::Vec3& up)
{
	cocos2d::Vec3 v[2] = { forward, up };
	alListenerfv(AL_ORIENTATION, (float*)v);
}

cocos2d::Vec3 AudioEngine::getVelocity()
{
	cocos2d::Vec3 v;
	alGetListenerfv(AL_VELOCITY, (float*)&v);
	return v;
}

void AudioEngine::setVelocity(const cocos2d::Vec3& v)
{
	alListenerfv(AL_VELOCITY, (float*)&v);
}

void AudioEngine::setDopplerScale(float scale)
{
	scale = std::max(0.f, scale);
	alDopplerFactor(scale);
}

float AudioEngine::getDopplerScale()
{
	return alGetFloat(AL_DOPPLER_FACTOR);
}
/*
void AudioEngine::setMeter(float scale)
{
	if (scale >= 0.0f)
	{
		metersPerUnit = scale;
#ifdef ALC_EXT_EFX
		alListenerf(AL_METERS_PER_UNIT, scale);
#endif
	}
}

float AudioEngine::getMeter() const
{
	return metersPerUnit;
}
*/
AudioEngine::DistanceModel AudioEngine::getDistanceModel()
{
	return distanceModel;
}

void AudioEngine::setDistanceModel(DistanceModel distanceModel_)
{
	distanceModel = distanceModel_;

	switch (distanceModel)
	{
	case DistanceModel::NONE:
		alDistanceModel(AL_NONE);
		break;

	case DistanceModel::INVERSE:
		alDistanceModel(AL_INVERSE_DISTANCE);
		break;

	case DistanceModel::INVERSE_CLAMPED:
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
		break;

	case DistanceModel::LINEAR:
		alDistanceModel(AL_LINEAR_DISTANCE);
		break;

	case DistanceModel::LINEAR_CLAMPED:
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		break;

	case DistanceModel::EXPONENT:
		alDistanceModel(AL_EXPONENT_DISTANCE);
		break;

	case DistanceModel::EXPONENT_CLAMPED:
		alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
		break;

	default:
		break;
	}
}

std::vector<AudioRecordingDevice*> AudioEngine::getRecordingDevices()
{
	if (!requestRecordAudioPermission())
		return {};

	std::vector<std::string> devnames;
	cocos2d::Vector<AudioRecordingDevice*> devices;

	auto _defaultname = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
	std::string defaultname;
	if (_defaultname)
		defaultname = _defaultname;

	//no device name obtained from AL, fallback to reading from device
	if (defaultname.empty())
	{
		//use some safe basic parameters - 8 kHz, 8 bits, 1 channel
		ALCdevice *defaultdevice = alcCaptureOpenDevice(NULL, 8000, AL_FORMAT_MONO8, 1024);
		if (alGetError() == AL_NO_ERROR)
		{
			defaultname = alcGetString(defaultdevice, ALC_CAPTURE_DEVICE_SPECIFIER);
			alcCaptureCloseDevice(defaultdevice);
		}
		else
		{
			//failed to open default recording device - bail, return empty list
			capture.clear();
			return {};
		}
	}

	devnames.reserve(capture.size());
	devnames.push_back(defaultname);

	//find devices name list
	const ALCchar *devstr = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
	if (!devstr)
		return {};
	size_t offset = 0;
	while (true)
	{
		if (devstr[offset] == '\0')
			break;
		std::string str(&devstr[offset]);
		if (str != defaultname)
			devnames.push_back(str);
		offset += str.length() + 1;
	}

	devices.reserve(devnames.size());
	//build ordered list of devices
	for (auto& devname : devnames)
	{
		bool needCreate = true;
		for (auto&& c : capture)
		{
			if (devname == c->getName())
			{
				devices.pushBack(c);
				needCreate = false;
				break;
			}
		}
		if (needCreate)
		{
			auto dev = new AudioRecordingDevice(devname.c_str());
			dev->autorelease();
			devices.pushBack(dev);
		}
	}

	capture.clear();
	capture = devices;

	std::vector<AudioRecordingDevice*> ret;
	for (ssize_t i = 0; i < capture.size(); i++)
		ret.push_back(capture.at(i));
	return ret;
}

bool AudioEngine::setEffect(const std::string& name, const AudioEffect::ParamMap& params)
{
	AudioEffect *effect;
	ALuint slot;

	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
	{
		//new effect needed but no more slots
		if (effectmap.size() >= (unsigned int)MAX_SCENE_EFFECTS)
			return false;

		effect = new AudioEffect();
		slot = slotlist.top();
		slotlist.pop();

		effectmap[name] = { effect, slot };
	}
	else
	{
		effect = iter->second.effect;
		slot = iter->second.slot;
	}

	const bool result = effect->setParams(params);

#ifdef ALC_EXT_EFX
	if (alAuxiliaryEffectSloti)
	{
		if (result)
		{
			auto it = params.find(AudioEffect::Parameter::VOLUME);
			if (it != params.end())
				alAuxiliaryEffectSlotf(slot, AL_EFFECTSLOT_GAIN, it->second);
			alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect->getEffect());
		}
		else
			alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
		alGetError();
	}
#endif

	return result;
}

bool AudioEngine::removeEffect(const std::string& name)
{
	auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	AudioEffect *effect = iter->second.effect;
	ALuint slot = iter->second.slot;

#ifdef ALC_EXT_EFX
	if (alAuxiliaryEffectSloti)
		alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, AL_EFFECT_NULL);
#endif

	delete effect;
	effectmap.erase(iter);
	slotlist.push(slot);
	return true;
}

AudioEffect::ParamMap AudioEngine::getEffect(const std::string& name)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return {};
	return iter->second.effect->getParams();
}

std::vector<std::string> AudioEngine::getActiveEffects()
{
	if (effectmap.empty())
		return {};
	std::vector<std::string> list;
	list.reserve(effectmap.size());
	for (auto& i : effectmap)
		list.push_back(i.first);
	return list;
}

int AudioEngine::getMaxEffectCount()
{
	return MAX_SCENE_EFFECTS;
}

int AudioEngine::getMaxSourceEffectCount()
{
	return MAX_SOURCE_EFFECTS;
}

bool AudioEngine::isEffectSupported()
{
#ifdef ALC_EXT_EFX
	return (alGenEffects != nullptr);
#else
	return false;
#endif
}

bool AudioEngine::getEffectID(const std::string& name, ALuint &id)
{
	const auto iter = effectmap.find(name);
	if (iter == effectmap.end())
		return false;

	id = iter->second.slot;
	return true;
}

void AudioEngine::onEnterBackground()
{
	sAppBackground = true;
	updateSuspension();
}

void AudioEngine::onEnterForeground()
{
	sAppBackground = false;
	updateSuspension();
}

void AudioEngine::onAudioSessionInterruption(bool interrupted)
{
	sSessionInterrupted = interrupted;
	updateSuspension();
}

void AudioEngine::updateSuspension()
{
	if (!valid)
		return;
	const bool suspended = sAppBackground || sSessionInterrupted;
	if (sSuspended.exchange(suspended, std::memory_order_acq_rel) == suspended)
		return;
	if (suspended)
	{
		// Capture once across overlapping app/session notifications.
		auto sources = AudioSource::pauseAll();
		for (auto* source : sources)
			tempSources.pushBack(source);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(ALC_SOFT_pause_device)
		if (sPauseDevice)
			sPauseDevice(device);
#endif
	}
	else
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(ALC_SOFT_pause_device)
		if (sResumeDevice)
			sResumeDevice(device);
#endif
		std::vector<AudioSource*> sources;
		for (auto* source : tempSources)
		{
			// A source explicitly stopped while suspended must stay stopped.
			if (pool->isPlaying(source))
				sources.push_back(source);
		}
		AudioSource::playBatch(sources);
		tempSources.clear();
	}
}

bool AudioEngine::init()
{
	// Lifecycle configuration is serialized by the host, like FileOpener setup.
	if (valid)
		return true;
	if (context || device || AudioPoolThread::Instance)
		end();
	lastError.clear();
	if (!AudioInternal::initializeAudioSession(lastError))
	{
		AudioInternal::shutdownAudioSession();
		return false;
	}

	// Check permission before opening new device
	requestRecordAudioPermission();

	// Passing null for default device.
	device = alcOpenDevice(nullptr);

	if (device == nullptr)
	{
		lastError = "Could not open device.";
		end();
		return false;
	}

	// Load the entry point
	if (alcIsExtensionPresent(device, "ALC_SOFT_reopen_device") == ALC_TRUE)
		alcReopenDeviceSoft = (LPALCREOPENDEVICESOFT)alcGetProcAddress(device, "alcReopenDeviceSOFT");
	else
		alcReopenDeviceSoft = nullptr;

#ifdef ALC_EXT_EFX
	MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 64;
	ALint attribs[4] = { ALC_MAX_AUXILIARY_SENDS, MAX_SOURCE_EFFECTS, 0, 0 };
	// Remember attribute list for reopening
	hasInitAttribs = true;
	std::copy_n(attribs, 4, initAttribs);
#else
	hasInitAttribs = false;
	ALint *attribs = nullptr;
#endif

	context = alcCreateContext(device, attribs);

	if (context == nullptr)
	{
		lastError = "Could not create context.";
		end();
		return false;
	}

	if (!alcMakeContextCurrent(context) || alcGetError(device) != ALC_NO_ERROR)
	{
		lastError = "Could not make context current.";
		end();
		return false;
	}

	// New context => new AL object namespace: bump the device generation
	// (Sources detect stale ids via it, see overview in AudioEngine.h).
	++sDeviceGeneration;

#ifdef ALC_EXT_EFX
	initializeEFX();
#endif

	// EFX aux slots are context objects - allocate them once per context.
	createEffectSlots();

	pool = AudioPool::getInstance();
	if (!pool || !pool->init())
	{
		lastError = "Could not initialize source pool.";
		end();
		return false;
	}

	try
	{
		AudioPoolThread::Instance = new AudioPoolThread(pool);
	}
	catch (const std::exception& error)
	{
		lastError = std::string("Could not start audio worker: ") + error.what();
		end();
		return false;
	}

	initializeDeviceEvents();

	lastDefaultName = getDefaultDeviceName();
	lastAppliedDevice = lastDefaultName;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(ALC_SOFT_pause_device)
	if (alcIsExtensionPresent(device, "ALC_SOFT_pause_device") == ALC_TRUE)
	{
		sPauseDevice = (LPALCDEVICEPAUSESOFT)alcGetProcAddress(device, "alcDevicePauseSOFT");
		sResumeDevice = (LPALCDEVICERESUMESOFT)alcGetProcAddress(device, "alcDeviceResumeSOFT");
	}
#endif
	valid = true;
	updateSuspension();
	return true;
}

void AudioEngine::end()
{
	valid = false;
	AudioInternal::shutdownAudioSession();
#ifdef ALC_SOFT_system_events
	if (sEventControlSOFT)
	{
		constexpr ALCenum events[] = {
			ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT, ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT };
		sEventControlSOFT(2, events, ALC_FALSE);
	}
	if (sEventCallbackSOFT)
		sEventCallbackSOFT(nullptr, nullptr);
	sEventControlSOFT = nullptr;
	sEventCallbackSOFT = nullptr;
#endif
	if (AudioPoolThread::Instance)
	{
		AudioPoolThread::Instance->setFinish();
		delete AudioPoolThread::Instance;
		AudioPoolThread::Instance = nullptr;
	}

	// Drain the pool while the OpenAL context is still current (valid AL
	// calls): stops all playing Sources and frees the pool's OpenAL sources.
	// The AudioPool OBJECT is deliberately NOT destroyed here - AudioSource objects
	// hold a raw AudioPool* and their destructors call AudioPool::stop()/lock() (e.g.
	// when caller refcounts drop after end()); destroying it would be a
	// use-after-free. The pool is a process-lifetime singleton and its
	// drained state is re-initialized by the next AudioEngine::init().
	if (pool && context)
		pool->end();

	tempSources.clear(); // release the retained paused Sources (refcounted)

	capture.clear();

#ifdef ALC_EXT_EFX
	for (auto& e : effectmap)
	{
		delete e.second.effect;
		slotlist.push(e.second.slot);
	}

	if (alDeleteAuxiliaryEffectSlots)
	{
		while (!slotlist.empty())
		{
			alDeleteAuxiliaryEffectSlots(1, &slotlist.top());
			slotlist.pop();
		}
	}
#endif
	// Drop the effect registry itself (the AudioEffect objects and slots were
	// deleted above); without this a re-init would leave dangling entries in
	// the static map (AudioEngine::setEffect would return a freed pointer).
	effectmap.clear();
	resetEFX();

	if (context)
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		context = nullptr;
		// Stale Source ids must never address the next context's objects.
		++sDeviceGeneration;
	}
	if (device)
	{
		alcCloseDevice(device);
		device = nullptr;
	}

	// Reset the device-tracking state
	sDeviceEventPending.store(false, std::memory_order_release);
	lastAppliedDevice.clear();
	lastDefaultName.clear();
	devicePinned = false;
	alcReopenDeviceSoft = nullptr;
	hasInitAttribs = false;
	sRecoveryFailures = 0;
	sAppBackground = false;
	sSessionInterrupted = false;
	sSuspended.store(false, std::memory_order_release);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && defined(ALC_SOFT_pause_device)
	sPauseDevice = nullptr;
	sResumeDevice = nullptr;
#endif
}

void AudioEngine::createEffectSlots()
{
	MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 64;
	while (!slotlist.empty())
		slotlist.pop();

#ifdef ALC_EXT_EFX
	alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &MAX_SOURCE_EFFECTS);

	alGetError();
	if (alGenAuxiliaryEffectSlots)
	{
		// get real number of scene effects
		for (int i = 0; i < MAX_SCENE_EFFECTS; i++)
		{
			ALuint slot;
			alGenAuxiliaryEffectSlots(1, &slot);
			if (alGetError() == AL_NO_ERROR)
				slotlist.push(slot);
			else
			{
				MAX_SCENE_EFFECTS = i;
				break;
			}
		}
	}
	else
		MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 0;
#else
	MAX_SCENE_EFFECTS = MAX_SOURCE_EFFECTS = 0;
#endif
}

void AudioEngine::initializeDeviceEvents()
{
#ifdef ALC_SOFT_system_events
	// Push notifications for default-device changes / device removals; the
	// polling path in checkDeviceChange() remains as a fallback. A missing
	// extension just leaves the polling path active.
	if (alcIsExtensionPresent(device, "ALC_SOFT_system_events") != ALC_TRUE)
	{
		AWARN("ALC_SOFT_system_events not available");
		return;
	}
	sEventCallbackSOFT = (LPALCEVENTCALLBACKSOFT)alcGetProcAddress(NULL, "alcEventCallbackSOFT");
	sEventControlSOFT = (LPALCEVENTCONTROLSOFT)alcGetProcAddress(NULL, "alcEventControlSOFT");
	if (!sEventCallbackSOFT || !sEventControlSOFT)
	{
		AWARN("ALC_SOFT_system_events entry points not found");
		return;
	}

	sEventCallbackSOFT(audioDeviceEventCallback, nullptr);
	constexpr ALCenum events[2] = {
		ALC_EVENT_TYPE_DEFAULT_DEVICE_CHANGED_SOFT,
		ALC_EVENT_TYPE_DEVICE_REMOVED_SOFT
	};
	sEventControlSOFT(2, events, ALC_TRUE);
#else
	AINFO("ALC_SOFT_system_events not declared by the AL headers");
#endif
}

void AudioEngine::checkDeviceChange()
{
	if (!valid || !device || sSuspended.load(std::memory_order_acquire))
		return;

	// Throttle (also safe when called from other places than the AudioPoolThread).
	const auto now = std::chrono::steady_clock::now();
	if (now - sLastDeviceCheck < sDeviceCheckInterval)
		return;
	sLastDeviceCheck = now;

	bool changed = false;
	bool disconnected = false;

	// Default device name observed in this check; lastDefaultName is only
	// advanced after the change was handled, so failures are retried.
	std::string observedDefault = lastDefaultName;

	// 1) Fast path: system-events notification (flag set by the callback).
	if (sDeviceEventPending.exchange(false, std::memory_order_acq_rel))
		changed = true;

	// 2) Polling: default device name differs (on Windows the old endpoint
	//    stays "connected", so this is what catches plain default switches).
	{
		const std::string defaultName = getDefaultDeviceName();
		if (defaultName != lastDefaultName)
		{
			changed = true;
			observedDefault = defaultName;
		}
	}

	// 3) Unplug: the currently open device reports ALC_CONNECTED == ALC_FALSE
	//    (leads to the recreation path; see the overview in AudioEngine.h).
#ifdef ALC_EXT_disconnect
	{
		ALint connected = ALC_TRUE;
		alcGetIntegerv(device, ALC_CONNECTED, 1, &connected);
		// Clear the error: without ALC_EXT_disconnect this is an invalid enum.
		alcGetError(device);
		if (connected == ALC_FALSE)
		{
			changed = true;
			disconnected = true;
		}
	}
#endif

	if (!changed)
		return;

	if (devicePinned && !disconnected)
	{
		// A fixed device was requested - don't hijack it on default changes
		// (still note the new default name so the check does not re-trigger).
		lastDefaultName = observedDefault;
		AINFO("audio device pinned to \"%s\", ignoring default device change",
			lastAppliedDevice.c_str());
		return;
	}

	// Windows emits several notifications for one user action.
	if (now - sLastReopen < sReopenThrottle)
	{
		//AINFO("audio device switch suppressed");
		return;
	}

	if (disconnected)
	{
		// The opened device is physically gone - in-place reopening cannot
		// revive it (see the overview in AudioEngine.h), so the recreation
		// path is used. It keeps retrying (~1/s) until some device exists.
		AINFO("device disconnected (detected default: \"%s\"), recreating it",
			observedDefault.c_str());
		sLastReopen = now;
		if (recoverDisconnectedDevice())
			sRecoveryFailures = 0; // tracking state was re-based inside
		else
		{
			++sRecoveryFailures;
			// Log the first failure, then every 10th attempt (no log flood).
			if (sRecoveryFailures == 1 || sRecoveryFailures % 10 == 0)
				AWARN("device recovery failed (%d consecutive attempts); retrying automatically",
					sRecoveryFailures);
		}
		return;
	}

	// Note: "observedDefault" may still be the cached pre-change name on
	// Windows; the authoritative endpoint is logged by reopenDevice() after
	// it succeeded. This branch is only reached while the device is connected.
	AINFO("switching to current default device: \"%s\"",
		observedDefault.c_str());
	if (reopenDevice(std::string())) // empty -> follow current default (NULL deviceName)
	{
		lastDefaultName = getDefaultDeviceName();
	}
	else
	{
		// Accept the change as "handled but not applied" so we do not
		// retry-spin; the next change triggers a new attempt.
		lastDefaultName = observedDefault;
		AWARN("audio device change not applied (%s); keeping the current audio device",
			alcReopenDeviceSoft ? "reopen failed" : "ALC_SOFT_reopen_device not supported");
	}
}

bool AudioEngine::reopenDevice(const std::string& name)
{
	if (!valid || !device)
	{
		AERRO("reopenDevice: engine not initialized");
		return false;
	}

	// Record the attempt before calling so checkDeviceChange()'s throttle also
	// backs off repeating failures.
	sLastReopen = std::chrono::steady_clock::now();

	if (!alcReopenDeviceSoft)
	{
		// Extension unavailable: keep the originally opened device.
		AWARN("ALC_SOFT_reopen_device not supported; cannot switch the audio device");
		return false;
	}

	if (name.empty())
	{
		// Follow the current default: pass deviceName = NULL so the
		// implementation re-resolves it at call time. NEVER pre-resolve via
		// alcGetString(NULL, ALC_DEFAULT*_DEVICE_SPECIFIER) - those are cached
		// snapshots on Windows/OpenAL Soft and still name the OLD endpoint
		// right after a change.
		const ALCboolean ok = alcReopenDeviceSoft(device, nullptr,
			hasInitAttribs ? initAttribs : nullptr);
		if (ok == ALC_TRUE)
		{
			devicePinned = false;
			const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
			lastAppliedDevice = actual ? actual : std::string();
			AINFO("switched to default device: \"%s\"",
				lastAppliedDevice.empty() ? "<unknown>" : lastAppliedDevice.c_str());
			AudioALSupport::refresh();
			return true;
		}
		AWARN("alcReopenDeviceSOFT(NULL) failed (%s)", getErrorString(alcGetError(device)));
		return false;
	}

	// Switch to an explicitly named device and pin it.
	devicePinned = true;
	// already on that device
	if (name == lastAppliedDevice)
		return true;

	const ALCboolean ok = alcReopenDeviceSoft(device, name.c_str(),
		hasInitAttribs ? initAttribs : nullptr);
	if (ok == ALC_TRUE)
	{
		const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
		lastAppliedDevice = actual ? actual : name;
		AINFO("device reopened: \"%s\"", lastAppliedDevice.c_str());
		AudioALSupport::refresh();
		return true;
	}
	AWARN("alcReopenDeviceSOFT(\"%s\") failed (%s)", name.c_str(), getErrorString(alcGetError(device)));
	return false;
}

bool AudioEngine::recoverDisconnectedDevice()
{
	AINFO("recovering from a disconnected audio device...");
	if (!valid || !device || !context || !pool)
	{
		AERRO("engine not initialized");
		return false;
	}

	// Keep membership and captured Source pointers stable until the replacement
	// context has reassigned them. In particular, a host such as FairyGUI must
	// not observe the pool's temporary empty state and release its last owner.
	auto recoveryLock = pool->lock();

	// Snapshot context-level state for restoration.
	ALfloat pos[3], vel[3], orient[6];
	alGetListenerfv(AL_POSITION, pos);
	alGetListenerfv(AL_VELOCITY, vel);
	alGetListenerfv(AL_ORIENTATION, orient);
	ALfloat volume = 1.0f;
	alGetListenerf(AL_GAIN, &volume);
	const ALfloat doppler = alGetFloat(AL_DOPPLER_FACTOR);

	// Capture the currently assigned Sources (playing or paused) before the
	// context dies so they can resume automatically after the swap - their AL
	// ids are regenerated lazily by prepareAtomic() via the device generation.
	const auto resumeSources = pool->getPlayingSources();

	// Open the replacement device+context FIRST. if no device exists,
	// the caller retries automatically once something is plugged in.
	ALCdevice* newDevice = alcOpenDevice(nullptr);
	if (!newDevice)
	{
		lastError = "Could not open audio device while recovering.";
		return false;
	}
	ALCcontext* newContext = alcCreateContext(newDevice, hasInitAttribs ? initAttribs : nullptr);
	if (!newContext)
	{
		alcCloseDevice(newDevice);
		lastError = "Could not create context while recovering.";
		return false;
	}

	// From here on the old context is being torn down. AL object ids are only
	// valid in the context that created them, so all cleanup happens BEFORE
	// destroying it (while it is still current).
#ifdef ALC_EXT_EFX
	// Effects, filters and aux slots are context objects as well.
	if (alDeleteAuxiliaryEffectSlots)
	{
		while (!slotlist.empty())
		{
			alDeleteAuxiliaryEffectSlots(1, &slotlist.top());
			slotlist.pop();
		}
	}
	for (auto& e : effectmap)
		delete e.second.effect;
	effectmap.clear();
#endif

	// Sources are deliberately NOT stopped: their state (decoder position,
	// properties) and the captured list are what allow the automatic resume
	// below; stale ids are never touched because prepareAtomic() regenerates
	// them first (generation check).

	// Make the new context current, then destroy the old one (alcDestroyContext
	// forbids destroying the current context).
	if (!alcMakeContextCurrent(newContext))
	{
		alcDestroyContext(newContext);
		alcCloseDevice(newDevice);
		AERRO("recoverDisconnectedDevice: cannot make the new context current");
		return false;
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
	device = newDevice;
	context = newContext;

	// bump the device generation
	++sDeviceGeneration;

	// Rebuild context-owned objects
	createEffectSlots();
	if (!pool->init())
	{
		lastError = "Could not rebuild source pool after device recovery.";
		// This is the worker thread, so end() cannot join itself here.
		// Leave the new context owned for end()/the next init() to drain.
		valid = false;
		return false;
	}

	// Restore the context state captured above.
	alListenerfv(AL_POSITION, pos);
	alListenerfv(AL_VELOCITY, vel);
	alListenerfv(AL_ORIENTATION, orient);
	alListenerf(AL_GAIN, volume);
	alDopplerFactor(doppler);
	setDistanceModel(distanceModel);

	std::vector<AudioSource*> playableSources;
	playableSources.reserve(resumeSources.size());
	for (auto* s : resumeSources)
	{
		// Queue sources cannot be resumed
		if (s->getType() == AudioSource::Type::QUEUE)
		{
			AINFO("queue-type audio source cannot be resumed automatically; re-queue it to play again");
			continue;
		}
		playableSources.push_back(s);
	}
	if (!playableSources.empty())
	{
		if (AudioSource::playBatchAtomic(pool, playableSources))
			AINFO("resumed %d audio source(s) on the new audio device", (int)playableSources.size());
		else
			AWARN("failed to resume all of the %d captured sources", (int)playableSources.size());
	}

	// Re-base the tracking state on the fresh device
	const ALCchar* actual = alcGetString(device, ALC_DEVICE_SPECIFIER);
	lastAppliedDevice = actual ? actual : std::string();
	devicePinned = false;
	lastDefaultName = getDefaultDeviceName();
	sDeviceEventPending.store(false, std::memory_order_release);
	AudioALSupport::refresh();

	AINFO("audio device recreated after disconnect: \"%s\"",
		lastAppliedDevice.empty() ? "<unknown>" : lastAppliedDevice.c_str());
	return true;
}


#ifdef ALC_EXT_EFX
namespace AudioInternal
{
	LPALGENEFFECTS alGenEffects = nullptr;
	LPALDELETEEFFECTS alDeleteEffects = nullptr;
	LPALISEFFECT alIsEffect = nullptr;
	LPALEFFECTI alEffecti = nullptr;
	LPALEFFECTIV alEffectiv = nullptr;
	LPALEFFECTF alEffectf = nullptr;
	LPALEFFECTFV alEffectfv = nullptr;
	LPALGETEFFECTI alGetEffecti = nullptr;
	LPALGETEFFECTIV alGetEffectiv = nullptr;
	LPALGETEFFECTF alGetEffectf = nullptr;
	LPALGETEFFECTFV alGetEffectfv = nullptr;
	LPALGENFILTERS alGenFilters = nullptr;
	LPALDELETEFILTERS alDeleteFilters = nullptr;
	LPALISFILTER alIsFilter = nullptr;
	LPALFILTERI alFilteri = nullptr;
	LPALFILTERIV alFilteriv = nullptr;
	LPALFILTERF alFilterf = nullptr;
	LPALFILTERFV alFilterfv = nullptr;
	LPALGETFILTERI alGetFilteri = nullptr;
	LPALGETFILTERIV alGetFilteriv = nullptr;
	LPALGETFILTERF alGetFilterf = nullptr;
	LPALGETFILTERFV alGetFilterfv = nullptr;
	LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots = nullptr;
	LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots = nullptr;
	LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot = nullptr;
	LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti = nullptr;
	LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv = nullptr;
	LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf = nullptr;
	LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv = nullptr;
	LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti = nullptr;
	LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv = nullptr;
	LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf = nullptr;
	LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv = nullptr;
}
#endif

#define GET_FUNC(TYPE, NAME) NAME = (TYPE)alGetProcAddress(#NAME); if(!(NAME)) break;

void AudioEngine::resetEFX()
{
#ifdef ALC_EXT_EFX
	alGenEffects = nullptr; alDeleteEffects = nullptr; alIsEffect = nullptr;
	alEffecti = nullptr; alEffectiv = nullptr; alEffectf = nullptr; alEffectfv = nullptr;
	alGetEffecti = nullptr; alGetEffectiv = nullptr; alGetEffectf = nullptr; alGetEffectfv = nullptr;
	alGenFilters = nullptr; alDeleteFilters = nullptr; alIsFilter = nullptr;
	alFilteri = nullptr; alFilteriv = nullptr; alFilterf = nullptr; alFilterfv = nullptr;
	alGetFilteri = nullptr; alGetFilteriv = nullptr; alGetFilterf = nullptr; alGetFilterfv = nullptr;
	alGenAuxiliaryEffectSlots = nullptr; alDeleteAuxiliaryEffectSlots = nullptr; alIsAuxiliaryEffectSlot = nullptr;
	alAuxiliaryEffectSloti = nullptr; alAuxiliaryEffectSlotiv = nullptr;
	alAuxiliaryEffectSlotf = nullptr; alAuxiliaryEffectSlotfv = nullptr;
	alGetAuxiliaryEffectSloti = nullptr; alGetAuxiliaryEffectSlotiv = nullptr;
	alGetAuxiliaryEffectSlotf = nullptr; alGetAuxiliaryEffectSlotfv = nullptr;
#endif
}

void AudioEngine::initializeEFX()
{
	resetEFX();
#ifdef ALC_EXT_EFX
	if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
		return;

	bool ok = false;
	do
	{
		GET_FUNC(LPALGENEFFECTS, alGenEffects);
		GET_FUNC(LPALDELETEEFFECTS, alDeleteEffects);
		GET_FUNC(LPALISEFFECT, alIsEffect);
		GET_FUNC(LPALEFFECTI, alEffecti);
		GET_FUNC(LPALEFFECTIV, alEffectiv);
		GET_FUNC(LPALEFFECTF, alEffectf);
		GET_FUNC(LPALEFFECTFV, alEffectfv);
		GET_FUNC(LPALGETEFFECTI, alGetEffecti);
		GET_FUNC(LPALGETEFFECTIV, alGetEffectiv);
		GET_FUNC(LPALGETEFFECTF, alGetEffectf);
		GET_FUNC(LPALGETEFFECTFV, alGetEffectfv);
		GET_FUNC(LPALGENFILTERS, alGenFilters);
		GET_FUNC(LPALDELETEFILTERS, alDeleteFilters);
		GET_FUNC(LPALISFILTER, alIsFilter);
		GET_FUNC(LPALFILTERI, alFilteri);
		GET_FUNC(LPALFILTERIV, alFilteriv);
		GET_FUNC(LPALFILTERF, alFilterf);
		GET_FUNC(LPALFILTERFV, alFilterfv);
		GET_FUNC(LPALGETFILTERI, alGetFilteri);
		GET_FUNC(LPALGETFILTERIV, alGetFilteriv);
		GET_FUNC(LPALGETFILTERF, alGetFilterf);
		GET_FUNC(LPALGETFILTERFV, alGetFilterfv);
		GET_FUNC(LPALGENAUXILIARYEFFECTSLOTS, alGenAuxiliaryEffectSlots);
		GET_FUNC(LPALDELETEAUXILIARYEFFECTSLOTS, alDeleteAuxiliaryEffectSlots);
		GET_FUNC(LPALISAUXILIARYEFFECTSLOT, alIsAuxiliaryEffectSlot);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTI, alAuxiliaryEffectSloti);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTIV, alAuxiliaryEffectSlotiv);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTF, alAuxiliaryEffectSlotf);
		GET_FUNC(LPALAUXILIARYEFFECTSLOTFV, alAuxiliaryEffectSlotfv);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTI, alGetAuxiliaryEffectSloti);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTIV, alGetAuxiliaryEffectSlotiv);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTF, alGetAuxiliaryEffectSlotf);
		GET_FUNC(LPALGETAUXILIARYEFFECTSLOTFV, alGetAuxiliaryEffectSlotfv);
		ok = true;
	}
	while (false);
	//failed to initialize functions, revert to nullptr
	if (!ok)
	{
		resetEFX();
	}
#endif
}

NS_CC_END
