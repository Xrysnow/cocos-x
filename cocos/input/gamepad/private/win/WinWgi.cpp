#include "WinWgi.h"
#include "WinLegacyInput.h"
#include "../drivers/XboxBluetoothReports.h"

#if __has_include(<windows.gaming.input.h>) && __has_include(<roapi.h>) && __has_include(<wrl/client.h>)
#include <roapi.h>
#include <windows.gaming.input.h>
#include <wrl/client.h>

#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x40000
#define CC_GAMEPAD_WGI_ABI 1
#endif
#endif

#ifdef CC_GAMEPAD_WGI_ABI
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <future>
#include <map>
#include <mutex>
#include <set>
#include <system_error>
#include <thread>
#include <utility>
#endif

namespace cc::input::detail {

bool isWinWgiXboxProduct(unsigned vendor, unsigned product)
{
    return isKnownXboxProduct(vendor, product);
}

#ifdef CC_GAMEPAD_WGI_ABI
namespace {

namespace wgi = ABI::Windows::Gaming::Input;
using Microsoft::WRL::ComPtr;
using GamepadList = __FIVectorView_1_Windows__CGaming__CInput__CGamepad;
using Clock = std::chrono::steady_clock;
using namespace std::chrono_literals;
constexpr auto pollInterval = 4ms;
constexpr auto scanInterval = 250ms;
constexpr auto batteryInterval = 1s;
constexpr auto startupTimeout = 400ms;
constexpr auto startupRetry = 20ms;
constexpr std::uint64_t outputRetryNs = 40'000'000;
constexpr std::size_t maxOutputCommands = 64;

constexpr std::array standardButtons{
    wgi::GamepadButtons_A, wgi::GamepadButtons_B, wgi::GamepadButtons_X, wgi::GamepadButtons_Y,
    wgi::GamepadButtons_View, wgi::GamepadButtons_Menu, wgi::GamepadButtons_LeftThumbstick,
    wgi::GamepadButtons_RightThumbstick, wgi::GamepadButtons_LeftShoulder, wgi::GamepadButtons_RightShoulder
};
constexpr std::array paddles{
    wgi::GamepadButtons_Paddle1, wgi::GamepadButtons_Paddle2, wgi::GamepadButtons_Paddle3,
    wgi::GamepadButtons_Paddle4
};

class WgiRuntime {
public:
    ~WgiRuntime()
    {
        raw.Reset();
        gamepads.Reset();
        if (_initialized) _uninitialize();
        if (_module) FreeLibrary(_module);
    }

    bool start()
    {
        _module = LoadLibraryExW(L"combase.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!_module) return false;
        const auto initialize = symbol<decltype(&RoInitialize)>("RoInitialize");
        _uninitialize = symbol<decltype(&RoUninitialize)>("RoUninitialize");
        _activate = symbol<decltype(&RoGetActivationFactory)>("RoGetActivationFactory");
        _stringReference = symbol<decltype(&WindowsCreateStringReference)>("WindowsCreateStringReference");
        _stringBuffer = symbol<decltype(&WindowsGetStringRawBuffer)>("WindowsGetStringRawBuffer");
        _deleteString = symbol<decltype(&WindowsDeleteString)>("WindowsDeleteString");
        const auto keepMta = symbol<decltype(&CoIncrementMTAUsage)>("CoIncrementMTAUsage");
        if (!initialize || !_uninitialize || !_activate || !_stringReference ||
            !_stringBuffer || !_deleteString || !keepMta || FAILED(initialize(RO_INIT_MULTITHREADED)))
            return false;
        _initialized = true;

        // Keep the MTA alive for the process. WGI may destroy COM objects after
        // the last apartment closes, after some of its dependencies unload.
        // See SDL issue #5552.
        static std::once_flag pinFlag;
        static HRESULT pinResult = E_FAIL;
        std::call_once(pinFlag, [keepMta] {
            CO_MTA_USAGE_COOKIE cookie{};
            pinResult = keepMta(&cookie);
        });
        return SUCCEEDED(pinResult) &&
            factory(RuntimeClass_Windows_Gaming_Input_Gamepad, gamepads) &&
            factory(RuntimeClass_Windows_Gaming_Input_RawGameController, raw);
    }

    std::string deviceName([[maybe_unused]] wgi::IRawGameController* device) const
    {
#if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION >= 0x50000
        ComPtr<wgi::IRawGameController2> newer;
        HSTRING displayName = nullptr;
        if (FAILED(device->QueryInterface(IID_PPV_ARGS(&newer))) || FAILED(newer->get_DisplayName(&displayName)))
            return {};
        UINT32 length = 0;
        const auto* name = _stringBuffer(displayName, &length);
        auto result = name && length ? winUtf8(std::wstring_view(name, length)) : std::string{};
        _deleteString(displayName);
        return result;
#else
        return {};
#endif
    }

    ComPtr<wgi::IGamepadStatics> gamepads;
    ComPtr<wgi::IRawGameControllerStatics> raw;

private:
    template<class T>
    T symbol(const char* name) const { return std::bit_cast<T>(GetProcAddress(_module, name)); }

    template<class T>
    bool factory(const wchar_t* name, ComPtr<T>& result) const
    {
        const std::wstring_view id{name};
        HSTRING_HEADER storage{};
        HSTRING runtimeClass = nullptr;
        return SUCCEEDED(_stringReference(id.data(), static_cast<UINT32>(id.size()), &storage, &runtimeClass)) &&
            SUCCEEDED(_activate(runtimeClass, IID_PPV_ARGS(result.ReleaseAndGetAddressOf())));
    }

    HMODULE _module = nullptr;
    decltype(&RoUninitialize) _uninitialize = nullptr;
    decltype(&RoGetActivationFactory) _activate = nullptr;
    decltype(&WindowsCreateStringReference) _stringReference = nullptr;
    decltype(&WindowsGetStringRawBuffer) _stringBuffer = nullptr;
    decltype(&WindowsDeleteString) _deleteString = nullptr;
    bool _initialized = false;
};

bool modernXbox(unsigned product)
{
    // The generic XGIP identity does not distinguish hardware revisions.
    return product != 0x028e && product != 0x02ff;
}

bool validReading(const wgi::GamepadReading& reading)
{
    const auto inRange = [](double value) { return std::isfinite(value) && value >= -1.0 && value <= 1.0; };
    return inRange(reading.LeftThumbstickX) && inRange(reading.LeftThumbstickY) &&
        inRange(reading.RightThumbstickX) && inRange(reading.RightThumbstickY) &&
        inRange(reading.LeftTrigger) && reading.LeftTrigger >= 0 &&
        inRange(reading.RightTrigger) && reading.RightTrigger >= 0;
}

std::optional<Power> batteryPower(wgi::IGameControllerBatteryInfo* battery, Link link)
{
    using namespace ABI::Windows::System::Power;
    if (!battery) return std::nullopt;
    ComPtr<ABI::Windows::Devices::Power::IBatteryReport> report;
    BatteryStatus status{};
    if (FAILED(battery->TryGetBatteryReport(&report)) || !report || FAILED(report->get_Status(&status)))
        return std::nullopt;

    Power power;
    if (status == BatteryStatus_NotPresent)
    {
        if (link == Link::Wired) power.state = Power::State::External;
        return power;
    }
    if (status == BatteryStatus_Charging) power.state = Power::State::Charging;
    else if (status == BatteryStatus_Discharging) power.state = Power::State::OnBattery;

    ComPtr<__FIReference_1_int> remaining, full;
    INT32 current = 0, capacity = 0;
    if (SUCCEEDED(report->get_RemainingCapacityInMilliwattHours(&remaining)) && remaining &&
        SUCCEEDED(report->get_FullChargeCapacityInMilliwattHours(&full)) && full &&
        SUCCEEDED(remaining->get_Value(&current)) && SUCCEEDED(full->get_Value(&capacity)) &&
        current >= 0 && capacity > 0)
    {
        power.percent = static_cast<unsigned>(std::lround(std::min(1.0, static_cast<double>(current) / capacity) * 100));
        if (status == BatteryStatus_Idle && power.percent == 100u) power.state = Power::State::Charged;
    }
    return power;
}

Error feedbackStatus(HRESULT status)
{
    if (SUCCEEDED(status)) return Error::None;
    if (status == E_ACCESSDENIED) return Error::PermissionDenied;
    if (status == HRESULT_FROM_WIN32(ERROR_DEVICE_NOT_CONNECTED) || status == RPC_E_DISCONNECTED ||
        status == RO_E_CLOSED)
        return Error::Disconnected;
    if (status == E_NOTIMPL || status == HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED))
        return Error::Unsupported;
    return Error::BackendFailure;
}

struct Device : WinInputEndpoint {
    ComPtr<IUnknown> identity;
    ComPtr<wgi::IGamepad> gamepad;
    ComPtr<wgi::IGameControllerBatteryInfo> battery;
    XboxRumbleState motors;
    std::uint64_t retryOutput = 0;
    bool stoppingOutput = false;

    explicit Device(ComPtr<wgi::IGamepad> controller, ComPtr<IUnknown> object)
        : identity(std::move(object)), gamepad(std::move(controller)) {}

    Error write(const XboxRumbleState& next)
    {
        const auto strengths = next.motors();
        const wgi::GamepadVibration vibration{
            .LeftMotor = strengths.low,
            .RightMotor = strengths.high,
            .LeftTrigger = strengths.left,
            .RightTrigger = strengths.right,
        };
        const auto status = feedbackStatus(gamepad->put_Vibration(vibration));
        if (status == Error::None)
        {
            motors = next;
            retryOutput = 0;
            stoppingOutput = false;
        }
        return status;
    }

    void neutral(std::uint64_t now)
    {
        if (!motors.active() && !stoppingOutput) return;
        if (write({}) != Error::None)
        {
            stoppingOutput = true;
            retryOutput = now + outputRetryNs;
        }
    }

    void expire(std::uint64_t now)
    {
        if (now < retryOutput) return;
        if (stoppingOutput)
            neutral(now);
        else
        {
            auto next = motors;
            if (next.expire(now) && write(next) != Error::None)
                retryOutput = now + outputRetryNs;
        }
    }

    Error submit(const OutputCommand& command)
    {
        const auto* stop = std::get_if<Stop>(&command);
        if (stoppingOutput && (!stop || stop->channel != Channel::All)) return Error::Busy;
        if (!descriptor.capabilities.features.test(static_cast<unsigned>(Feature::BodyRumble)))
            return Error::Unsupported;
        if ((std::holds_alternative<TriggerRumble>(command) || (stop && stop->channel == Channel::Triggers)) &&
            !descriptor.capabilities.features.test(static_cast<unsigned>(Feature::TriggerRumble)))
            return Error::Unsupported;
        auto next = motors;
        const auto now = nowNs();
        next.expire(now);
        if (!next.apply(command, now)) return Error::Unsupported;
        return write(next);
    }

    void update(const wgi::GamepadReading& reading, bool updateBattery, ReportSink* sink)
    {
        std::array<RawChange, standardButtons.size() + paddles.size() + 7> changes{};
        unsigned count = 0;
        const auto apply = [&](RawKind kind, unsigned index, auto& old, auto value) {
            if (old != value)
            {
                changes[count++] = {kind, index, value};
                old = value;
            }
        };
        const auto pressed = [&](wgi::GamepadButtons mask) {
            return static_cast<std::uint8_t>((reading.Buttons & mask) != 0);
        };
        for (unsigned i = 0; i < standardButtons.size(); ++i)
            apply(RawKind::Button, i, state.buttons[i], pressed(standardButtons[i]));
        for (unsigned i = 0; i < paddles.size(); ++i)
        {
            const auto index = static_cast<unsigned>(standardButtons.size()) + i;
            if (descriptor.layout.buttonPresent[index])
                apply(RawKind::Button, index, state.buttons[index], pressed(paddles[i]));
        }
        const auto axis = [](double value) {
            return static_cast<std::int16_t>(std::lround(value * (value < 0 ? 32768.0 : 32767.0)));
        };
        const auto trigger = [](double value) {
            return static_cast<std::int16_t>(std::lround(value * 65535.0) - 32768);
        };
        const std::array axes{axis(reading.LeftThumbstickX), axis(-reading.LeftThumbstickY),
            trigger(reading.LeftTrigger), axis(reading.RightThumbstickX), axis(-reading.RightThumbstickY),
            trigger(reading.RightTrigger)};
        for (unsigned i = 0; i < axes.size(); ++i)
            apply(RawKind::Axis, i, state.axes[i], axes[i]);
        const auto hat = static_cast<std::uint8_t>((pressed(wgi::GamepadButtons_DPadUp) ? 1 : 0) |
            (pressed(wgi::GamepadButtons_DPadRight) ? 2 : 0) |
            (pressed(wgi::GamepadButtons_DPadDown) ? 4 : 0) |
            (pressed(wgi::GamepadButtons_DPadLeft) ? 8 : 0));
        apply(RawKind::Hat, 0, state.hats[0], hat);

        std::optional<Power> power;
        if (updateBattery)
        {
            const auto& previous = descriptor.power;
            if (const auto current = batteryPower(battery.Get(), descriptor.link); current &&
                (previous.state != current->state || previous.percent != current->percent))
                power = descriptor.power = *current;
        }
        if (sink && (count || power))
            sink->report(key, {std::span(changes).first(count), {}, {}, power, ++cursor, {}});
    }
};

std::optional<Device> openDevice(const WgiRuntime& runtime, ComPtr<wgi::IGamepad> gamepad,
                                 ComPtr<IUnknown> identity)
{
    ComPtr<wgi::IGameController> controller;
    ComPtr<wgi::IRawGameController> raw;
    UINT16 vendor = 0, product = 0;
    if (FAILED(gamepad.As(&controller)) || FAILED(runtime.raw->FromGameController(controller.Get(), &raw)) ||
        !raw || FAILED(raw->get_HardwareVendorId(&vendor)) || FAILED(raw->get_HardwareProductId(&product)) ||
        !isWinWgiXboxProduct(vendor, product))
        return std::nullopt;
    wgi::GamepadReading reading{};
    if (FAILED(gamepad->GetCurrentReading(&reading)) || !validReading(reading))
        return std::nullopt;

    Device result(std::move(gamepad), std::move(identity));
    auto& descriptor = result.descriptor;
    descriptor.vendor = vendor;
    descriptor.product = product;
    descriptor.controllerType = GamepadType::XboxCompatible;
    descriptor.name = runtime.deviceName(raw.Get());
    if (descriptor.name.empty()) descriptor.name = "Xbox Controller";
    boolean wireless = false;
    if (SUCCEEDED(controller->get_IsWireless(&wireless)))
        descriptor.link = wireless ? Link::Wireless : Link::Wired;
    result.gamepad.As(&result.battery);

    auto& layout = descriptor.layout;
    layout.id = "win-wgi-xbox-v1";
    // WGI's wireless flag also covers the Xbox Wireless Adapter.
    layout.guid = DeviceGuid::make(0, vendor, product, 0, {}, descriptor.name, 'w');
    layout.usesVersion = false;
    layout.buttonCount = static_cast<unsigned>(standardButtons.size() + paddles.size());
    layout.axisCount = 6;
    layout.hatCount = 1;
    layout.buttonPresent.resize(layout.buttonCount, 0);
    std::fill_n(layout.buttonPresent.begin(), standardButtons.size(), std::uint8_t{1});
    layout.builtInMapping =
        "a:b0,b:b1,x:b2,y:b3,back:b4,start:b5,leftstick:b6,rightstick:b7,leftshoulder:b8,rightshoulder:b9,"
        "paddle1:b10,paddle2:b11,paddle3:b12,paddle4:b13,"
        "leftx:a0,lefty:a1,lefttrigger:a2,rightx:a3,righty:a4,righttrigger:a5,"
        "dpup:h0.1,dpright:h0.2,dpdown:h0.4,dpleft:h0.8,face:abxy";
    ComPtr<wgi::IGamepad2> newer;
    if (SUCCEEDED(result.gamepad.As(&newer)))
        for (unsigned i = 0; i < paddles.size(); ++i)
        {
            wgi::GameControllerButtonLabel label{};
            if (SUCCEEDED(newer->GetButtonLabel(paddles[i], &label)) && label != wgi::GameControllerButtonLabel_None)
                layout.buttonPresent[standardButtons.size() + i] = 1;
        }
    wgi::GamepadVibration feedback{};
    if (SUCCEEDED(result.gamepad->get_Vibration(&feedback)))
    {
        descriptor.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble));
        descriptor.capabilities.features.set(static_cast<unsigned>(Feature::TriggerRumble), modernXbox(product));
    }
    result.state.buttons.resize(layout.buttonCount);
    result.state.axes.resize(layout.axisCount);
    result.state.axesKnown.assign(layout.axisCount, 1);
    result.state.hats.resize(layout.hatCount);
    result.update(reading, true, nullptr);
    return result;
}

class WinWgiBackend final : public GamepadBackend {
public:
    ~WinWgiBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (_worker.joinable()) return Error::Busy;
        std::promise<Error> startup;
        auto outcome = startup.get_future();
        _exit = false;
        _active = true;
        try
        {
            _worker = std::thread([this, &sink, signal = std::move(startup)]() mutable {
                run(sink, signal);
            });
        }
        catch (const std::system_error&)
        {
            return Error::BackendFailure;
        }
        const auto result = outcome.get();
        if (result != Error::None) _worker.join();
        return result;
    }

    void stop() noexcept override
    {
        if (!_worker.joinable()) return;
        {
            std::lock_guard lock(_mutex);
            _exit = true;
        }
        _wake.notify_one();
        _worker.join();
        _published.clear();
        _baselines.clear();
        _commands.clear();
        _neutral = _topology = false;
    }

    void setActive(bool active) override
    {
        {
            std::lock_guard lock(_mutex);
            if (_active == active) return;
            _active = active;
            if (!active)
            {
                _neutral = true;
                ++_outputEpoch;
            }
        }
        _wake.notify_one();
    }

    void requestBaseline(EndpointKey key) override
    {
        {
            std::lock_guard lock(_mutex);
            if (!_published.contains(key)) return;
            _baselines.insert(key);
        }
        _wake.notify_one();
    }

    void requestTopology() override
    {
        {
            std::lock_guard lock(_mutex);
            _topology = true;
        }
        _wake.notify_one();
    }

    Error submit(EndpointKey key, const NativeCommand& command) override
    {
        const auto* stop = std::get_if<Stop>(&command.command);
        if (!(std::holds_alternative<Rumble>(command.command) ||
              std::holds_alternative<TriggerRumble>(command.command) ||
              (stop && (stop->channel == Channel::All || stop->channel == Channel::Body ||
                        stop->channel == Channel::Triggers))))
            return Error::Unsupported;
        {
            std::lock_guard lock(_mutex);
            if (_exit || !_published.contains(key)) return Error::Disconnected;
            if (!_active && !stop) return Error::Busy;
            if (_commands.size() >= maxOutputCommands) return Error::QueueFull;
            _commands.push_back({key, command, _outputEpoch});
        }
        _wake.notify_one();
        return Error::None;
    }

private:
    struct Command {
        EndpointKey key;
        NativeCommand command;
        std::uint64_t epoch;
    };
    // Gamepad objects are managed by WGI. Compare their canonical COM
    // identity on the worker, where all references are obtained and used.
    using Devices = std::map<IUnknown*, Device>;

    bool scan(const WgiRuntime& runtime, Devices& devices, ReportSink* sink)
    {
        ComPtr<GamepadList> list;
        UINT32 size = 0;
        if (FAILED(runtime.gamepads->get_Gamepads(&list)) || !list || FAILED(list->get_Size(&size)))
            return false;
        std::vector<std::pair<ComPtr<IUnknown>, ComPtr<wgi::IGamepad>>> present;
        present.reserve(size);
        for (UINT32 index = 0; index < size; ++index)
        {
            ComPtr<wgi::IGamepad> gamepad;
            ComPtr<IUnknown> identity;
            if (FAILED(list->GetAt(index, &gamepad)) || !gamepad || FAILED(gamepad.As(&identity)))
                return false;
            present.emplace_back(std::move(identity), std::move(gamepad));
        }

        for (auto it = devices.begin(); it != devices.end();)
        {
            if (std::ranges::any_of(present, [&](const auto& pair) { return pair.first.Get() == it->first; }))
            {
                ++it;
                continue;
            }
            auto& device = it->second;
            device.neutral(nowNs());
            {
                std::lock_guard lock(_mutex);
                _published.erase(device.key);
            }
            if (sink) sink->detached(device.key);
            it = devices.erase(it);
        }
        for (auto& [identity, gamepad] : present)
        {
            if (devices.contains(identity.Get())) continue;
            auto* handle = identity.Get();
            auto device = openDevice(runtime, std::move(gamepad), std::move(identity));
            if (!device) continue;
            device->key = {WinWgiId, ++_nextEndpoint, 1};
            auto& added = devices.emplace(handle, std::move(*device)).first->second;
            if (sink) publish(added, *sink);
        }
        return true;
    }

    void publish(Device& device, ReportSink& sink)
    {
        {
            std::lock_guard lock(_mutex);
            _published.insert(device.key);
        }
        auto attachment = device.attachment();
        sink.attached(attachment.key, std::move(attachment.descriptor), std::move(attachment.initial));
    }

    void send(Devices& devices, const Command& request, ReportSink& sink)
    {
        auto destination = std::ranges::find_if(devices, [&](const auto& item) {
            return item.second.key == request.key;
        });
        Error result = Error::Disconnected;
        if (destination != devices.end())
        {
            bool active;
            {
                std::lock_guard lock(_mutex);
                active = _active && !_exit && request.epoch == _outputEpoch;
            }
            result = active || std::holds_alternative<Stop>(request.command.command)
                ? destination->second.submit(request.command.command) : Error::Busy;
        }
        if (request.command.id != CommandId{})
            sink.outputCompleted(request.key, request.command.id, result);
    }

    bool waitForXbox(const WgiRuntime& runtime, Devices& devices)
    {
        // Gamepad.Gamepads can be empty until the provider has populated it.
        const auto until = Clock::now() + startupTimeout;
        for (;;)
        {
            if (scan(runtime, devices, nullptr) && std::ranges::any_of(devices, [](const auto& item) {
                return item.second.descriptor.capabilities.features.test(static_cast<unsigned>(Feature::TriggerRumble));
            }))
                return true;
            if (Clock::now() >= until) return false;
            std::this_thread::sleep_for(startupRetry);
        }
    }

    void run(ReportSink& sink, std::promise<Error>& startup)
    {
        WgiRuntime runtime;
        Devices devices;
        if (!runtime.start() || !waitForXbox(runtime, devices))
        {
            startup.set_value(Error::Unsupported);
            return;
        }
        startup.set_value(Error::None);
        for (auto& [handle, device] : devices) publish(device, sink);

        auto deadline = Clock::now();
        auto scanAt = deadline + scanInterval;
        auto batteryAt = deadline + batteryInterval;
        for (;;)
        {
            std::deque<Command> commands;
            std::set<EndpointKey> baselines;
            bool exit, neutral, topology;
            {
                std::unique_lock lock(_mutex);
                _wake.wait_until(lock, deadline, [this] {
                    return _exit || _neutral || _topology || !_commands.empty() || !_baselines.empty();
                });
                exit = _exit;
                neutral = std::exchange(_neutral, false);
                topology = std::exchange(_topology, false);
                commands.swap(_commands);
                baselines.swap(_baselines);
            }
            const auto now = Clock::now();
            const auto ns = nowNs();
            if (exit || neutral || topology)
                for (auto& [handle, device] : devices) device.neutral(ns);
            if (exit) return;
            if (topology || now >= scanAt)
            {
                scan(runtime, devices, topology ? nullptr : &sink);
                scanAt = now + scanInterval;
            }
            const bool updateBattery = now >= batteryAt;
            if (updateBattery) batteryAt = now + batteryInterval;

            std::vector<AttachedEndpoint> snapshot;
            for (auto& [handle, device] : devices)
            {
                const bool baseline = !topology && baselines.contains(device.key);
                wgi::GamepadReading reading{};
                if (SUCCEEDED(device.gamepad->GetCurrentReading(&reading)) && validReading(reading))
                    device.update(reading, updateBattery && !baseline, topology || baseline ? nullptr : &sink);
                if (topology)
                {
                    std::lock_guard lock(_mutex);
                    _published.erase(device.key);
                    ++device.key.generation;
                    _published.insert(device.key);
                    snapshot.push_back(device.attachment());
                }
                else if (baseline)
                    device.sendBaseline(sink);
                device.expire(ns);
            }
            if (topology) sink.topology(std::move(snapshot));
            for (const auto& command : commands) send(devices, command, sink);
            deadline = devices.empty() ? scanAt : now + pollInterval;
        }
    }

    std::thread _worker;
    std::mutex _mutex;
    std::condition_variable _wake;
    std::set<EndpointKey> _published, _baselines;
    std::deque<Command> _commands;
    std::uint64_t _nextEndpoint = 0, _outputEpoch = 0;
    bool _exit = false, _active = true, _neutral = false, _topology = false;
};

} // namespace

bool winWgiApiAvailable()
{
    // Always probe from an MTA thread regardless of the caller's COM apartment.
    bool available = false;
    try
    {
        std::thread worker([&] {
            WgiRuntime runtime;
            ComPtr<GamepadList> devices;
            UINT32 size = 0;
            available = runtime.start() && SUCCEEDED(runtime.gamepads->get_Gamepads(&devices)) &&
                devices && SUCCEEDED(devices->get_Size(&size));
        });
        worker.join();
    }
    catch (const std::system_error&)
    {}
    return available;
}

std::unique_ptr<GamepadBackend> makeWinWgiBackend() { return std::make_unique<WinWgiBackend>(); }
#else
bool winWgiApiAvailable() { return false; }
std::unique_ptr<GamepadBackend> makeWinWgiBackend() { return {}; }
#endif

} // namespace cc::input::detail
