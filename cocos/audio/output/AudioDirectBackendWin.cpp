#include "AudioDirectBackend.h"

#include <Windows.h>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <objbase.h>
#include <propsys.h>
#include <wrl/client.h>
#include <initguid.h>
#include <devpkey.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <latch>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>

namespace cc::audio::detail {
namespace {

using Microsoft::WRL::ComPtr;
using Position = AudioChannelPosition;
using Error = AudioOutputError;
using Clock = std::chrono::steady_clock;

struct ComApartment {
    HRESULT result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    ~ComApartment() { if (SUCCEEDED(result)) CoUninitialize(); }
    bool available() const { return SUCCEEDED(result) || result == RPC_E_CHANGED_MODE; }
};

struct PropValue {
    PROPVARIANT value{};
    ~PropValue() { PropVariantClear(&value); }
};

template <class T>
using ComMemory = std::unique_ptr<T, decltype(&CoTaskMemFree)>;

ComPtr<IMMDeviceEnumerator> makeEnumerator()
{
    ComPtr<IMMDeviceEnumerator> enumerator;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER,
                     IID_PPV_ARGS(enumerator.GetAddressOf()));
    return enumerator;
}

std::wstring idOf(IMMDevice* device)
{
    LPWSTR id = nullptr;
    if (FAILED(device->GetId(&id)))
        return {};
    const ComMemory<wchar_t> owner(id, CoTaskMemFree);
    return id ? id : L"";
}

std::string utf8(std::wstring_view text)
{
    if (text.empty())
        return {};
    const int length = WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                                          nullptr, 0, nullptr, nullptr);
    std::string output(length, '\0');
    if (length)
        WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                            output.data(), length, nullptr, nullptr);
    return output;
}

std::string containerOf(IPropertyStore* store)
{
    const PROPERTYKEY container{DEVPKEY_Device_ContainerId.fmtid, DEVPKEY_Device_ContainerId.pid};
    PropValue property;
    if (FAILED(store->GetValue(container, &property.value)) ||
        property.value.vt != VT_CLSID || !property.value.puuid)
        return {};
    wchar_t value[39]{};
    StringFromGUID2(*property.value.puuid, value, 39);
    std::string result = utf8(value);
    for (auto& ch : result)
        if (ch >= 'A' && ch <= 'F')
            ch += 'a' - 'A';
    return result;
}

struct MixFormat {
    unsigned rate = 0;
    std::vector<Position> channels;
};

MixFormat mixFormatOf(IMMDevice* endpoint)
{
    ComPtr<IAudioClient> client;
    if (FAILED(endpoint->Activate(__uuidof(IAudioClient), CLSCTX_INPROC_SERVER, nullptr,
                                  reinterpret_cast<void**>(client.GetAddressOf()))))
        return {};
    WAVEFORMATEX* format = nullptr;
    if (FAILED(client->GetMixFormat(&format)) || !format)
        return {};
    const ComMemory<WAVEFORMATEX> owner(format, CoTaskMemFree);
    DWORD mask = 0;
    if (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
        format->cbSize >= sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX))
        mask = reinterpret_cast<const WAVEFORMATEXTENSIBLE*>(format)->dwChannelMask;
    if (!mask && format->nChannels == 2)
        mask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;
    if (!mask && format->nChannels == 1)
        mask = SPEAKER_FRONT_CENTER;
    constexpr std::array speakers{
        std::pair{SPEAKER_FRONT_LEFT, Position::FrontLeft},
        std::pair{SPEAKER_FRONT_RIGHT, Position::FrontRight},
        std::pair{SPEAKER_FRONT_CENTER, Position::FrontCenter},
        std::pair{SPEAKER_LOW_FREQUENCY, Position::Lfe},
        std::pair{SPEAKER_BACK_LEFT, Position::RearLeft},
        std::pair{SPEAKER_BACK_RIGHT, Position::RearRight},
        std::pair{SPEAKER_SIDE_LEFT, Position::SideLeft},
        std::pair{SPEAKER_SIDE_RIGHT, Position::SideRight},
    };
    MixFormat result;
    result.rate = format->nSamplesPerSec;
    for (const auto& [bit, position] : speakers)
        if (mask & bit)
            result.channels.push_back(position);
    if (result.channels.size() != format->nChannels)
        result.channels.clear();
    return result;
}

struct Connections {
    struct Connection {
        std::string key;
        std::string mainName;
    };
    std::mutex mutex;
    std::map<std::wstring, Connection, std::less<>> active;
    std::uint64_t change = 0;
};

bool stillConnected(const std::shared_ptr<Connections>& connections, const std::string& key)
{
    const std::lock_guard lock(connections->mutex);
    return std::ranges::any_of(connections->active, [&](const auto& entry) {
        return entry.second.key == key;
    });
}

class Notifications final : public IMMNotificationClient {
public:
    explicit Notifications(std::shared_ptr<Connections> connections)
        : _connections(std::move(connections)) {}

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID type, void** result) override
    {
        if (!result)
            return E_POINTER;
        *result = nullptr;
        if (type != __uuidof(IUnknown) && type != __uuidof(IMMNotificationClient))
            return E_NOINTERFACE;
        *result = static_cast<IMMNotificationClient*>(this);
        AddRef();
        return S_OK;
    }

    ULONG STDMETHODCALLTYPE AddRef() override { return ++_references; }
    ULONG STDMETHODCALLTYPE Release() override
    {
        const auto remaining = --_references;
        if (!remaining)
            delete this;
        return remaining;
    }

    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR id, DWORD state) override
    {
        if (state != DEVICE_STATE_ACTIVE)
            invalidate(id);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR id) override
    {
        invalidate(id);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow, ERole, LPCWSTR) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR, const PROPERTYKEY) override { return S_OK; }

private:
    void invalidate(LPCWSTR id)
    {
        if (!id)
            return;
        const std::lock_guard lock(_connections->mutex);
        auto& active = _connections->active;
        if (const auto found = active.find(id); found != active.end())
            active.erase(found);
        ++_connections->change;
    }

    std::atomic<ULONG> _references{1};
    std::shared_ptr<Connections> _connections;
};

class ConnectionMonitor {
public:
    ConnectionMonitor() : _worker([this](std::stop_token stop) {
        const ComApartment com;
        const auto enumerator = com.available() ? makeEnumerator() : nullptr;
        ComPtr<IMMNotificationClient> notifications;
        notifications.Attach(new Notifications(connections));
        available = enumerator && SUCCEEDED(enumerator->RegisterEndpointNotificationCallback(notifications.Get()));
        _started.count_down();
        if (available)
        {
            std::mutex mutex;
            std::condition_variable_any ready;
            std::unique_lock lock(mutex);
            ready.wait(lock, stop, [] { return false; });
            enumerator->UnregisterEndpointNotificationCallback(notifications.Get());
        }
    }) { _started.wait(); }

    const std::shared_ptr<Connections> connections = std::make_shared<Connections>();
    bool available = false;

private:
    std::latch _started{1};
    std::jthread _worker;
};

struct MonitorSlot {
    std::mutex mutex;
    std::shared_ptr<ConnectionMonitor> current;
};

MonitorSlot& monitorSlot()
{
    static MonitorSlot state;
    return state;
}

std::shared_ptr<ConnectionMonitor> monitor()
{
    auto& state = monitorSlot();
    const std::lock_guard lock(state.mutex);
    if (!state.current)
        state.current = std::make_shared<ConnectionMonitor>();
    return state.current;
}

struct AlcDeviceCloser {
    void operator()(ALCdevice* device) const { alcCloseDevice(device); }
};

// The bundled WASAPI backend accepts the exact MMDevice ID as a selector.
std::string openAlName(const std::string& selector)
{
    const std::unique_ptr<ALCdevice, AlcDeviceCloser> device(alcOpenDevice(selector.c_str()));
    if (!device)
        return {};
    const auto* name = alcGetString(device.get(), ALC_ALL_DEVICES_SPECIFIER);
    return name ? name : "";
}

struct Layout {
    ALCint mode = 0;
    ALenum format = 0;
};

Layout directLayout(const std::vector<Position>& channels)
{
    constexpr std::array stereo{Position::FrontLeft, Position::FrontRight};
    constexpr std::array quad{Position::FrontLeft, Position::FrontRight,
                              Position::RearLeft, Position::RearRight};
    constexpr std::array surround{Position::FrontLeft, Position::FrontRight, Position::FrontCenter,
                                  Position::Lfe, Position::RearLeft, Position::RearRight,
                                  Position::SideLeft, Position::SideRight};
    if (std::ranges::equal(channels, stereo))
        return {ALC_STEREO_BASIC_SOFT, AL_FORMAT_STEREO16};
    if (std::ranges::equal(channels, quad))
        return {ALC_QUAD_SOFT, AL_FORMAT_QUAD16};
    if (std::ranges::equal(channels, surround))
        return {ALC_SURROUND_7_1_SOFT, AL_FORMAT_71CHN16};
    return {};
}

class CurrentContext {
public:
    CurrentContext(PFNALCSETTHREADCONTEXTPROC set, PFNALCGETTHREADCONTEXTPROC get, ALCcontext* context)
        : _set(set), _previous(get ? get() : nullptr), _active(set && set(context) == ALC_TRUE) {}
    ~CurrentContext() { if (_active) _set(_previous); }
    explicit operator bool() const { return _active; }

private:
    PFNALCSETTHREADCONTEXTPROC _set;
    ALCcontext* _previous;
    bool _active;
};

class OpenAlOutput final : public OutputStream {
    static constexpr std::size_t capacity = outputQueueBlocks;

public:
    OpenAlOutput(const DirectEndpoint& endpoint, std::shared_ptr<Connections> connections)
        : _endpoint(endpoint), _layout(directLayout(endpoint.channels)), _connections(std::move(connections)) {}

    ~OpenAlOutput() override
    {
        if (_context)
        {
            if (const auto guard = current(); guard)
            {
                if (_source)
                {
                    alSourceStop(_source);
                    alDeleteSources(1, &_source);
                }
                alDeleteBuffers(static_cast<ALsizei>(_buffers.size()), _buffers.data());
            }
            alcDestroyContext(_context);
        }
    }

    Error open()
    {
        if (!_layout.mode || !_endpoint.sampleRate || _endpoint.deviceSelector.empty() ||
            _endpoint.mainDeviceName.empty())
            return Error::Unsupported;
        _device.reset(alcOpenDevice(_endpoint.deviceSelector.c_str()));
        if (!_device)
            return Error::BackendFailure;
        if (!alcIsExtensionPresent(_device.get(), "ALC_SOFT_output_mode") ||
            !alcIsExtensionPresent(_device.get(), "ALC_EXT_disconnect"))
            return Error::Unsupported;
        _set = reinterpret_cast<PFNALCSETTHREADCONTEXTPROC>(
            alcGetProcAddress(_device.get(), "alcSetThreadContext"));
        _get = reinterpret_cast<PFNALCGETTHREADCONTEXTPROC>(
            alcGetProcAddress(_device.get(), "alcGetThreadContext"));
        if (!_get || !_set)
            return Error::Unsupported;
        const ALCint attributes[]{
            ALC_OUTPUT_MODE_SOFT, _layout.mode, ALC_FREQUENCY, static_cast<ALCint>(_endpoint.sampleRate),
            ALC_MONO_SOURCES, 0, ALC_STEREO_SOURCES, 1, 0
        };
        _context = alcCreateContext(_device.get(), attributes);
        if (!_context)
            return Error::BackendFailure;
        ALCint mode = 0, rate = 0;
        alcGetIntegerv(_device.get(), ALC_OUTPUT_MODE_SOFT, 1, &mode);
        alcGetIntegerv(_device.get(), ALC_FREQUENCY, 1, &rate);
        const auto lock = current();
        if (!lock || mode != _layout.mode || rate != static_cast<ALCint>(_endpoint.sampleRate) ||
            !alIsExtensionPresent("AL_SOFT_direct_channels") ||
            (_endpoint.channels.size() > 2 && !alIsExtensionPresent("AL_EXT_MCFORMATS")))
            return Error::Unsupported;

        alGenSources(1, &_source);
        alSourcei(_source, AL_DIRECT_CHANNELS_SOFT, AL_TRUE);
        if (alIsExtensionPresent("AL_SOFT_source_spatialize"))
            alSourcei(_source, AL_SOURCE_SPATIALIZE_SOFT, AL_FALSE);
        alGenBuffers(static_cast<ALsizei>(_buffers.size()), _buffers.data());
        if (alcIsExtensionPresent(_device.get(), "ALC_SOFT_device_clock"))
            _clock = reinterpret_cast<LPALCGETINTEGER64VSOFT>(
                alcGetProcAddress(_device.get(), "alcGetInteger64vSOFT"));
        if (!stillConnected(_connections, _endpoint.key))
            return Error::Disconnected;
        return alGetError() == AL_NO_ERROR ? Error::None : Error::BackendFailure;
    }

    Error submit(const std::int16_t* pcm, std::size_t frames) override
    {
        const auto lock = current();
        if (!lock)
            return Error::BackendFailure;
        auto slot = std::ranges::find(_frames, std::size_t{0});
        if (slot == _frames.end())
            return Error::QueueFull;
        const auto buffer = _buffers[slot - _frames.begin()];
        const auto bytes = frames * _endpoint.channels.size() * sizeof(*pcm);
        alBufferData(buffer, _layout.format, pcm, static_cast<ALsizei>(bytes),
                     static_cast<ALsizei>(_endpoint.sampleRate));
        if (alGetError() != AL_NO_ERROR)
            return Error::BackendFailure;
        ALint state = 0;
        alGetSourcei(_source, AL_SOURCE_STATE, &state);
        if (state == AL_STOPPED)
        {
            if (!recycle())
                return Error::BackendFailure;
            alSourceRewind(_source);
        }
        alSourceQueueBuffers(_source, 1, &buffer);
        if (alGetError() != AL_NO_ERROR)
            return Error::BackendFailure;
        *slot = frames;
        return _paused ? Error::None : kick(true);
    }

    Error setPaused(bool paused) override
    {
        const auto lock = current();
        if (!lock)
            return Error::BackendFailure;
        _paused = paused;
        if (paused)
        {
            alSourcePause(_source);
            return alGetError() == AL_NO_ERROR ? Error::None : Error::BackendFailure;
        }
        return kick();
    }

    Error drain() override
    {
        _draining = true;
        return Error::None;
    }

    AudioResult<OutputProgress> poll() override
    {
        ALCint connected = 0;
        alcGetIntegerv(_device.get(), ALC_CONNECTED, 1, &connected);
        if (connected != ALC_TRUE || !stillConnected(_connections, _endpoint.key))
            return Error::Disconnected;
        const auto lock = current();
        if (!lock)
            return Error::BackendFailure;

        if (!recycle())
            return Error::BackendFailure;
        ALint offset = 0;
        alGetSourcei(_source, AL_SAMPLE_OFFSET, &offset);
        if (alGetError() != AL_NO_ERROR)
            return Error::BackendFailure;
        auto consumed = _processed + static_cast<unsigned>(std::max(offset, 0));
        const auto available = static_cast<unsigned>(std::ranges::count(_frames, std::size_t{0}));
        bool drained = false;
        if (_draining && available == capacity && !_paused)
        {
            const auto now = Clock::now();
            if (_tailUntil == Clock::time_point{})
            {
                ALCint64SOFT latency = 0;
                if (_clock)
                    _clock(_device.get(), ALC_DEVICE_LATENCY_SOFT, 1, &latency);
                _tailUntil = now + std::chrono::nanoseconds(std::max<ALCint64SOFT>(latency, 0));
            }
            drained = now >= _tailUntil;
        }
        _consumed = std::max(consumed, _consumed);
        return OutputProgress{_consumed, available, drained};
    }

private:
    CurrentContext current() const { return {_set, _get, _context}; }

    bool recycle(ALint leave = 0)
    {
        ALint processed = 0;
        alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);
        while (processed-- > leave)
        {
            ALuint buffer = 0;
            alSourceUnqueueBuffers(_source, 1, &buffer);
            const auto entry = std::ranges::find(_buffers, buffer);
            if (entry == _buffers.end())
                return false;
            auto& frames = _frames[entry - _buffers.begin()];
            _processed += frames;
            frames = 0;
        }
        return alGetError() == AL_NO_ERROR;
    }

    Error kick(bool appended = false)
    {
        ALint state = 0, queued = 0, processed = 0;
        alGetSourcei(_source, AL_SOURCE_STATE, &state);
        alGetSourcei(_source, AL_BUFFERS_QUEUED, &queued);
        alGetSourcei(_source, AL_BUFFERS_PROCESSED, &processed);
        if (state != AL_PLAYING && (queued > processed || (appended && queued)))
        {
            // A stopped source restarts at the front. Remove old processed
            // buffers if the device ran empty between poll() and submit().
            if (state == AL_STOPPED && !recycle(appended ? 1 : 0))
                return Error::BackendFailure;
            alSourcePlay(_source);
        }
        return alGetError() == AL_NO_ERROR ? Error::None : Error::BackendFailure;
    }

    DirectEndpoint _endpoint;
    Layout _layout;
    std::shared_ptr<Connections> _connections;
    std::unique_ptr<ALCdevice, AlcDeviceCloser> _device;
    ALCcontext* _context = nullptr;
    PFNALCSETTHREADCONTEXTPROC _set = nullptr;
    PFNALCGETTHREADCONTEXTPROC _get = nullptr;
    LPALCGETINTEGER64VSOFT _clock = nullptr;
    ALuint _source = 0;
    std::array<ALuint, capacity> _buffers{};
    std::array<std::size_t, capacity> _frames{};
    std::uint64_t _processed = 0;
    std::uint64_t _consumed = 0;
    Clock::time_point _tailUntil;
    bool _paused = true;
    bool _draining = false;
};

} // namespace

AudioResult<std::vector<DirectEndpoint>> enumeratePlatformEndpoints()
{
    static std::atomic_uint64_t generation = 0;
    const ComApartment com;
    const auto watcher = monitor();
    const auto enumerator = com.available() && watcher->available ? makeEnumerator() : nullptr;
    if (!enumerator)
        return Error::BackendFailure;
    auto& connections = *watcher->connections;
    std::uint64_t change;
    {
        const std::lock_guard lock(connections.mutex);
        change = connections.change;
    }
    ComPtr<IMMDeviceCollection> collection;
    UINT count = 0;
    if (FAILED(enumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, collection.GetAddressOf())) ||
        FAILED(collection->GetCount(&count)))
        return Error::BackendFailure;
    ComPtr<IMMDevice> defaultDevice;
    enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, defaultDevice.GetAddressOf());
    const auto defaultId = defaultDevice ? idOf(defaultDevice.Get()) : std::wstring{};

    std::map<std::wstring, DirectEndpoint, std::less<>> found;
    for (UINT i = 0; i < count; ++i)
    {
        ComPtr<IMMDevice> device;
        if (FAILED(collection->Item(i, device.GetAddressOf())))
            continue;
        const auto id = idOf(device.Get());
        if (id.empty())
            continue;
        auto& endpoint = found[id];
        endpoint.deviceSelector = utf8(id);
        endpoint.isDefault = id == defaultId;
        auto format = mixFormatOf(device.Get());
        endpoint.sampleRate = format.rate;
        endpoint.channels = std::move(format.channels);
        endpoint.canRoute = directLayout(endpoint.channels).format != 0;

        ComPtr<IPropertyStore> store;
        if (SUCCEEDED(device->OpenPropertyStore(STGM_READ, store.GetAddressOf())))
        {
            PropValue name;
            const PROPERTYKEY friendlyName{DEVPKEY_Device_FriendlyName.fmtid, DEVPKEY_Device_FriendlyName.pid};
            if (SUCCEEDED(store->GetValue(friendlyName, &name.value)) &&
                name.value.vt == VT_LPWSTR && name.value.pwszVal)
                endpoint.name = utf8(name.value.pwszVal);
            endpoint.containerId = containerOf(store.Get());
        }
        if (endpoint.name.empty())
            endpoint.name = endpoint.deviceSelector;
    }

    std::vector<DirectEndpoint> result;
    {
        const std::lock_guard lock(connections.mutex);
        if (change != connections.change)
            return Error::Busy;
        std::erase_if(connections.active, [&found](const auto& entry) {
            return !found.contains(entry.first);
        });
        result.reserve(found.size());
        for (auto& [id, endpoint] : found)
        {
            auto& connection = connections.active[id];
            if (connection.key.empty())
                connection.key = endpoint.deviceSelector + ":" + std::to_string(++generation);
            endpoint.key = connection.key;
            endpoint.mainDeviceName = connection.mainName;
            result.push_back(std::move(endpoint));
        }
    }

    for (auto& endpoint : result)
    {
        if (!endpoint.mainDeviceName.empty())
            continue;
        auto name = openAlName(endpoint.deviceSelector);
        if (name.empty())
            continue;
        const std::lock_guard lock(connections.mutex);
        const auto entry = std::ranges::find_if(connections.active, [&](const auto& item) {
            return item.second.key == endpoint.key;
        });
        if (entry != connections.active.end())
            endpoint.mainDeviceName = entry->second.mainName = std::move(name);
    }
    return result;
}

AudioResult<std::unique_ptr<OutputStream>> openPlatformOutput(const DirectEndpoint& endpoint)
{
    const auto current = enumeratePlatformEndpoints();
    if (!current)
        return current.error();
    const auto& endpoints = current.value();
    const auto match = std::ranges::find(endpoints, endpoint.key, &DirectEndpoint::key);
    if (match == endpoints.end())
        return Error::Disconnected;
    if (match->sampleRate != endpoint.sampleRate || match->channels != endpoint.channels)
        return Error::Unsupported;
    auto stream = std::make_unique<OpenAlOutput>(*match, monitor()->connections);
    if (const auto error = stream->open(); error != Error::None)
        return error;
    return std::unique_ptr<OutputStream>(std::move(stream));
}

void shutdownPlatformOutput() noexcept
{
    std::shared_ptr<ConnectionMonitor> retired;
    {
        auto& state = monitorSlot();
        const std::lock_guard lock(state.mutex);
        retired = std::move(state.current);
    }
}

} // namespace cc::audio::detail
