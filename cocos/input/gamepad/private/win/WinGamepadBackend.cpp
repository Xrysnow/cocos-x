#include "WinXInput.h"
#include "WinLegacyInput.h"

#include <bit>
#include <condition_variable>
#include <iterator>
#include <mutex>
#include <utility>

namespace cc::input::detail {
namespace {

class SystemXInput final : public XInputApi {
public:
    ~SystemXInput() override
    {
        if (_module)
            FreeLibrary(_module);
    }

    bool load()
    {
        for (const auto* name : {L"xinput1_4.dll", L"xinput9_1_0.dll"})
        {
            _module = LoadLibraryExW(name, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            if (!_module)
                continue;
            _get = symbol<decltype(_get)>("XInputGetState");
            _set = symbol<decltype(_set)>("XInputSetState");
            _caps = symbol<decltype(_caps)>("XInputGetCapabilities");
            _power = symbol<decltype(_power)>("XInputGetBatteryInformation");
            if (_get && _set && _caps)
                return true;
            FreeLibrary(std::exchange(_module, nullptr));
        }
        return false;
    }

    DWORD read(DWORD slot, XINPUT_STATE& state) noexcept override
    {
        return _get(slot, &state);
    }

    DWORD capabilities(DWORD slot, XINPUT_CAPABILITIES& caps) noexcept override
    {
        return _caps(slot, 0, &caps);
    }

    DWORD vibrate(DWORD slot, XINPUT_VIBRATION vibration) noexcept override
    {
        return _set(slot, &vibration);
    }

    std::optional<Power> power(DWORD slot) noexcept override
    {
        XINPUT_BATTERY_INFORMATION battery{};
        if (!_power || _power(slot, BATTERY_DEVTYPE_GAMEPAD, &battery) != ERROR_SUCCESS)
            return std::nullopt;
        switch (battery.BatteryType)
        {
        case BATTERY_TYPE_WIRED: return Power{Power::State::External, {}, {}};
        case BATTERY_TYPE_ALKALINE:
        case BATTERY_TYPE_NIMH: return Power{Power::State::OnBattery, {}, battery.BatteryLevel};
        default: return Power{};
        }
    }

private:
    template<class T>
    T symbol(const char* name) const
    {
        return std::bit_cast<T>(GetProcAddress(_module, name));
    }

    HMODULE _module = nullptr;
    decltype(&XInputGetState) _get = nullptr;
    decltype(&XInputSetState) _set = nullptr;
    decltype(&XInputGetCapabilities) _caps = nullptr;
    decltype(&XInputGetBatteryInformation) _power = nullptr;
};

class WinGamepadBackend final : public GamepadBackend, private ReportSink {
public:
    WinGamepadBackend(std::unique_ptr<GamepadBackend> xinput, std::unique_ptr<GamepadBackend> legacy)
        : _xinput(std::move(xinput)), _legacy(std::move(legacy)) {}

    ~WinGamepadBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (_startedXInput || _startedLegacy)
            return Error::Busy;
        _sink = &sink;
        _startedXInput = _xinput && _xinput->start(*this) == Error::None;
        _startedLegacy = _legacy && _legacy->start(*this) == Error::None;
        return _startedXInput || _startedLegacy ? Error::None : Error::Unsupported;
    }

    void stop() noexcept override
    {
        {
            std::lock_guard lock(_mutex);
            _awaiting = 0;
            ++_topologyEpoch;
        }
        _published.notify_all();
        if (std::exchange(_startedXInput, false))
            _xinput->stop();
        if (std::exchange(_startedLegacy, false))
            _legacy->stop();
        _snapshot.clear();
        _sink = nullptr;
    }

    void setActive(bool active) override
    {
        if (_startedXInput)
            _xinput->setActive(active);
        if (_startedLegacy)
            _legacy->setActive(active);
    }

    void requestBaseline(EndpointKey key) override
    {
        if (auto* owner = backend(key))
            owner->requestBaseline(key);
    }

    Error setSensor(EndpointKey key, Sensor sensor, bool enabled) override
    {
        const auto owner = backend(key);
        return owner ? owner->setSensor(key, sensor, enabled) : Error::Disconnected;
    }

    void requestTopology() override
    {
        {
            std::lock_guard lock(_mutex);
            if (_awaiting != 0)
                return;
            _awaiting = static_cast<unsigned>(_startedXInput) + static_cast<unsigned>(_startedLegacy);
            _snapshot.clear();
        }
        if (_startedXInput)
            _xinput->requestTopology();
        if (_startedLegacy)
            _legacy->requestTopology();
    }

    Error submit(EndpointKey key, const NativeCommand& command) override
    {
        const auto owner = backend(key);
        return owner ? owner->submit(key, command) : Error::Disconnected;
    }

private:
    GamepadBackend* backend(EndpointKey key) const
    {
        if (key.backend == WinXInputId && _startedXInput)
            return _xinput.get();
        if ((key.backend == WinRawHidId || key.backend == WinDirectInputId) && _startedLegacy)
            return _legacy.get();
        return nullptr;
    }

    void attached(EndpointKey key, EndpointDescriptor descriptor, RawBaseline initial) override
    {
        _sink->attached(key, std::move(descriptor), std::move(initial));
    }

    void report(EndpointKey key, const ReportView& report) override { _sink->report(key, report); }
    void baseline(EndpointKey key, RawBaseline state) override { _sink->baseline(key, std::move(state)); }
    void capabilitiesChanged(EndpointKey key, EndpointCapabilities caps) override
    {
        _sink->capabilitiesChanged(key, std::move(caps));
    }
    void desynchronized(EndpointKey key, InputGap gap) override { _sink->desynchronized(key, gap); }
    void detached(EndpointKey key) override { _sink->detached(key); }

    void topology(std::vector<AttachedEndpoint> endpoints) override
    {
        std::unique_lock lock(_mutex);
        if (_awaiting == 0)
            return;
        _snapshot.insert(_snapshot.end(), std::make_move_iterator(endpoints.begin()),
                         std::make_move_iterator(endpoints.end()));
        if (--_awaiting == 0)
        {
            _sink->topology(std::move(_snapshot));
            ++_topologyEpoch;
            _published.notify_all();
        }
        else
        {
            // The first producer must not send changes for new generations
            // until the queue has accepted the combined snapshot.
            const auto epoch = _topologyEpoch;
            _published.wait(lock, [this, epoch] { return _topologyEpoch != epoch; });
        }
    }

    void outputCompleted(EndpointKey key, CommandId id, Error error) override
    {
        _sink->outputCompleted(key, id, error);
    }

    std::unique_ptr<GamepadBackend> _xinput;
    std::unique_ptr<GamepadBackend> _legacy;
    ReportSink* _sink = nullptr;
    bool _startedXInput = false, _startedLegacy = false;
    std::mutex _mutex;
    std::condition_variable _published;
    std::vector<AttachedEndpoint> _snapshot;
    unsigned _awaiting = 0;
    std::uint64_t _topologyEpoch = 0;
};

} // namespace

std::unique_ptr<GamepadBackend> makeWinGamepadBackend()
{
    auto api = std::make_unique<SystemXInput>();
    auto xinput = api->load() ? makeXInputBackend(std::move(api)) : nullptr;
    return std::make_unique<WinGamepadBackend>(std::move(xinput), makeWinLegacyInput(WinLegacyPaths::Both));
}

} // namespace cc::input::detail
