#include "WinXInput.h"
#include "WinLegacyInput.h"

#include <cfgmgr32.h>
#include <objbase.h>

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <system_error>
#include <thread>
#include <utility>

namespace cc::input::detail {
namespace {

using Clock = std::chrono::steady_clock;
using namespace std::chrono_literals;
constexpr auto pollConnected = 4ms;
constexpr auto pollEmpty = 1s;
constexpr auto outputRetry = 40ms;
constexpr std::size_t maxOutputCommands = 64;
constexpr std::array<WORD, 10> buttonMasks{
    XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y,
    XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER,
    XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB
};

struct State {
    std::array<std::uint8_t, buttonMasks.size()> buttons{};
    std::array<std::int16_t, 6> axes{};
    std::uint8_t hat = 0;
};

State decode(const XINPUT_GAMEPAD& input)
{
    State state;
    for (std::size_t i = 0; i < buttonMasks.size(); ++i)
        state.buttons[i] = (input.wButtons & buttonMasks[i]) != 0;
    const auto trigger = [](BYTE value) { return static_cast<std::int16_t>(value * 257 - 32768); };
    const auto invert = [](SHORT value) { return static_cast<std::int16_t>(-1 - value); };
    state.axes = {input.sThumbLX, invert(input.sThumbLY), trigger(input.bLeftTrigger),
                  input.sThumbRX, invert(input.sThumbRY), trigger(input.bRightTrigger)};
    if (input.wButtons & XINPUT_GAMEPAD_DPAD_UP) state.hat |= 1;
    if (input.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) state.hat |= 2;
    if (input.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) state.hat |= 4;
    if (input.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) state.hat |= 8;
    return state;
}

RawState rawState(const State& state)
{
    return {{state.buttons.begin(), state.buttons.end()}, {state.hat},
            {state.axes.begin(), state.axes.end()}, {}};
}

std::string makeName(BYTE type)
{
    switch (type)
    {
    case XINPUT_DEVSUBTYPE_WHEEL: return "XInput Wheel";
    case XINPUT_DEVSUBTYPE_ARCADE_STICK: return "XInput Arcade Stick";
    case XINPUT_DEVSUBTYPE_FLIGHT_STICK: return "XInput Flight Stick";
    case XINPUT_DEVSUBTYPE_DANCE_PAD: return "XInput Dance Pad";
    case XINPUT_DEVSUBTYPE_GUITAR:
    case XINPUT_DEVSUBTYPE_GUITAR_ALTERNATE:
    case XINPUT_DEVSUBTYPE_GUITAR_BASS: return "XInput Guitar";
    case XINPUT_DEVSUBTYPE_DRUM_KIT: return "XInput Drum Kit";
    case XINPUT_DEVSUBTYPE_ARCADE_PAD: return "XInput Arcade Pad";
    default: return "XInput Controller";
    }
}

EndpointDescriptor describe(XInputApi& api, DWORD index)
{
    XINPUT_CAPABILITIES caps{};
    const bool hasCaps = api.capabilities(index, caps) == ERROR_SUCCESS;
    EndpointDescriptor result;
    result.name = makeName(caps.SubType);
    result.controllerType = GamepadType::XboxCompatible;
    auto& layout = result.layout;
    layout.id = "win-xinput-sdl3-v1";
    layout.buttonCount = static_cast<unsigned>(buttonMasks.size()); // Public XInput has no Guide.
    layout.axisCount = 6;
    layout.hatCount = 1;
    layout.xinput = true;
    // SDL uses a generic Microsoft Xbox 360 identity when the private
    // capability API is unavailable. The public DeviceInfo IDs remain absent.
    layout.guid = DeviceGuid::make(3, 0x045e, 0x028e, 0, {}, result.name, 'x', caps.SubType);
    layout.builtInMapping =
        "a:b0,b:b1,x:b2,y:b3,leftshoulder:b4,rightshoulder:b5,back:b6,start:b7,leftstick:b8,rightstick:b9,"
        "dpup:h0.1,dpright:h0.2,dpdown:h0.4,dpleft:h0.8,"
        "leftx:a0,lefty:a1,lefttrigger:a2,rightx:a3,righty:a4,righttrigger:a5,face:abxy";
    if (hasCaps)
    {
        const auto& controls = caps.Gamepad;
        for (const auto mask : buttonMasks)
            layout.buttonPresent.push_back((controls.wButtons & mask) != 0);
        constexpr auto directions = XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_RIGHT |
                                    XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_LEFT;
        layout.hatPresent = {static_cast<std::uint8_t>((controls.wButtons & directions) != 0)};
        layout.axisPresent = {controls.sThumbLX != 0, controls.sThumbLY != 0, controls.bLeftTrigger != 0,
                              controls.sThumbRX != 0, controls.sThumbRY != 0, controls.bRightTrigger != 0};
        const bool rumble = (caps.Flags & XINPUT_CAPS_FFB_SUPPORTED) != 0 ||
                            caps.Vibration.wLeftMotorSpeed != 0 || caps.Vibration.wRightMotorSpeed != 0;
        result.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble), rumble);
        result.capabilities.acknowledgedBodyStop = rumble;
        if (caps.Flags & XINPUT_CAPS_WIRELESS)
            result.link = Link::Wireless;
    }
    if (const auto power = api.power(index))
    {
        result.power = *power;
        if (power->state == Power::State::External && result.link == Link::Unknown)
            result.link = Link::Wired;
    }
    return result;
}

bool samePower(const Power& left, const Power& right)
{
    return left.state == right.state && left.percent == right.percent && left.level == right.level;
}

Error xinputError(DWORD error)
{
    switch (error)
    {
    case ERROR_SUCCESS: return Error::None;
    case ERROR_DEVICE_NOT_CONNECTED: return Error::Disconnected;
    case ERROR_ACCESS_DENIED: return Error::PermissionDenied;
    case ERROR_NOT_SUPPORTED: return Error::Unsupported;
    default: return Error::BackendFailure;
    }
}

class XInputBackend final : public GamepadBackend {
public:
    explicit XInputBackend(std::unique_ptr<XInputApi> api) : _api(std::move(api)) {}
    ~XInputBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (!_api)
            return Error::Unsupported;
        if (_worker.joinable())
            return Error::Busy;
        _sink = &sink;
        _stopping = false;
        _active = true;
        _rescan = true;

        CM_NOTIFY_FILTER filter{};
        filter.cbSize = sizeof(filter);
        filter.Flags = CM_NOTIFY_FILTER_FLAG_ALL_INTERFACE_CLASSES;
        filter.FilterType = CM_NOTIFY_FILTER_TYPE_DEVICEINTERFACE;
        CM_Register_Notification(&filter, this, &XInputBackend::deviceChange, &_notification);
        try
        {
            _worker = std::thread([this] { run(); });
        }
        catch (const std::system_error&)
        {
            stop();
            return Error::BackendFailure;
        }
        return Error::None;
    }

    void stop() noexcept override
    {
        if (_notification)
        {
            CM_Unregister_Notification(_notification);
            _notification = nullptr;
        }
        if (_worker.joinable())
        {
            {
                std::lock_guard lock(_mutex);
                _stopping = true;
            }
            _wake.notify_one();
            _worker.join();
        }
        _sink = nullptr;
        for (auto& slot : _slots)
            slot.connected = false;
        _published = {};
        _baselines = {};
        _commands.clear();
    }

    void setActive(bool active) override
    {
        {
            std::lock_guard lock(_mutex);
            if (_active == active)
                return;
            _active = active;
            if (!active)
            {
                _stopMotors = true;
                ++_outputEpoch;
            }
            else
                _rescan = true;
        }
        _wake.notify_one();
    }

    void requestBaseline(EndpointKey key) override
    {
        {
            std::lock_guard lock(_mutex);
            if (!published(key))
                return;
            _baselines[key.endpoint] = true;
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
        const auto* rumble = std::get_if<Rumble>(&command.command);
        const auto* stop = std::get_if<Stop>(&command.command);
        if (!rumble && (!stop || (stop->channel != Channel::All && stop->channel != Channel::Body)))
            return Error::Unsupported;
        {
            std::lock_guard lock(_mutex);
            if (_stopping || !published(key))
                return Error::Disconnected;
            if (!_active && rumble)
                return Error::Busy;
            if (_commands.size() >= maxOutputCommands + (stop ? outputStopReserve : 0))
                return Error::QueueFull;
            _commands.push_back({key, command, _outputEpoch});
        }
        _wake.notify_one();
        return Error::None;
    }

private:
    struct Slot {
        std::uint64_t generation = 0, cursor = 0;
        bool connected = false;
        bool neutralConfirmed = false;
        DWORD packet = 0;
        State state;
        Power power;
        Clock::time_point due{}, powerDue{}, stopDue{};
    };
    struct Command {
        EndpointKey key;
        NativeCommand effect;
        std::uint64_t epoch;
    };

    static DWORD CALLBACK deviceChange(HCMNOTIFICATION, void* context, CM_NOTIFY_ACTION action,
                                        PCM_NOTIFY_EVENT_DATA, DWORD) noexcept
    {
        if (action == CM_NOTIFY_ACTION_DEVICEINTERFACEARRIVAL ||
            action == CM_NOTIFY_ACTION_DEVICEINTERFACEREMOVAL)
        {
            auto& backend = *static_cast<XInputBackend*>(context);
            {
                std::lock_guard lock(backend._mutex);
                backend._rescan = true;
            }
            backend._wake.notify_one();
        }
        return ERROR_SUCCESS;
    }

    bool published(EndpointKey key) const
    {
        return key.backend == WinXInputId && key.endpoint < _published.size() &&
               key.generation != 0 && _published[key.endpoint] == key.generation;
    }

    EndpointKey key(DWORD index) const
    {
        return {WinXInputId, index, _slots[index].generation};
    }

    void publishGeneration(DWORD index, bool open)
    {
        std::lock_guard lock(_mutex);
        _published[index] = open ? _slots[index].generation : 0;
        if (!open)
            _baselines[index] = false;
    }

    void close(DWORD index, bool notify)
    {
        auto& slot = _slots[index];
        if (!slot.connected)
            return;
        slot.stopDue = {};
        slot.connected = false;
        slot.neutralConfirmed = false;
        publishGeneration(index, false);
        if (notify)
            _sink->detached(key(index));
    }

    void stopMotor(DWORD index)
    {
        auto& slot = _slots[index];
        if (slot.stopDue != Clock::time_point{})
        {
            const auto status = xinputError(_api->vibrate(index, {}));
            slot.neutralConfirmed = status == Error::None;
            slot.stopDue = status == Error::None || status == Error::Disconnected
                ? Clock::time_point{} : Clock::now() + outputRetry;
        }
    }

    void poll(DWORD index, bool baseline, bool rebuilding, std::vector<AttachedEndpoint>& topology)
    {
        auto& slot = _slots[index];
        XINPUT_STATE input{};
        const auto result = _api->read(index, input);
        const ReportTime time;
        const auto now = Clock::now();
        if (result != ERROR_SUCCESS)
        {
            if (result == ERROR_DEVICE_NOT_CONNECTED || rebuilding)
                close(index, !rebuilding);
            slot.due = now + (slot.connected ? pollConnected : pollEmpty);
            return;
        }
        slot.due = now + pollConnected;
        const State state = decode(input.Gamepad);
        if (!slot.connected || rebuilding)
        {
            stopMotor(index);
            slot.connected = true;
            slot.neutralConfirmed = false;
            ++slot.generation;
            slot.cursor = 0;
            slot.packet = input.dwPacketNumber;
            slot.state = state;
            slot.powerDue = now + pollEmpty;
            auto descriptor = describe(*_api, index);
            slot.power = descriptor.power;
            auto initial = RawBaseline{rawState(state), slot.cursor, time};
            publishGeneration(index, true);
            if (rebuilding)
                topology.push_back({key(index), std::move(descriptor), std::move(initial)});
            else
                _sink->attached(key(index), std::move(descriptor), std::move(initial));
            return;
        }
        if (baseline)
        {
            slot.state = state;
            slot.packet = input.dwPacketNumber;
            _sink->baseline(key(index), {rawState(state), ++slot.cursor, time});
            return;
        }
        std::optional<Power> power;
        if (now >= slot.powerDue)
        {
            slot.powerDue = now + pollEmpty;
            if (const auto current = _api->power(index); current && !samePower(*current, slot.power))
                power = slot.power = *current;
        }
        if (input.dwPacketNumber == slot.packet && !power)
            return;

        std::array<RawChange, buttonMasks.size() + 7> changes{};
        std::size_t count = 0;
        for (unsigned i = 0; i < state.buttons.size(); ++i)
            if (state.buttons[i] != slot.state.buttons[i])
                changes[count++] = {RawKind::Button, i, state.buttons[i]};
        for (unsigned i = 0; i < state.axes.size(); ++i)
            if (state.axes[i] != slot.state.axes[i])
                changes[count++] = {RawKind::Axis, i, state.axes[i]};
        if (state.hat != slot.state.hat)
            changes[count++] = {RawKind::Hat, 0, state.hat};
        slot.packet = input.dwPacketNumber;
        slot.state = state;
        if (count || power)
            _sink->report(key(index), {std::span(changes).first(count), {}, {}, power, ++slot.cursor, time});
    }

    void send(const Command& command)
    {
        const auto index = static_cast<DWORD>(command.key.endpoint);
        auto& slot = _slots[index];
        Error result = Error::Disconnected;
        if (slot.connected && key(index) == command.key)
        {
            std::uint64_t currentEpoch;
            bool active;
            {
                std::lock_guard lock(_mutex);
                currentEpoch = _outputEpoch;
                active = _active && !_stopping;
            }
            if (!command.effect.canApply() ||
                (std::holds_alternative<Rumble>(command.effect.command) && (!active || currentEpoch != command.epoch)))
                result = Error::Busy;
            else
            {
                const auto operation = command.effect.commandAt(nowNs());
                const auto* rumble = std::get_if<Rumble>(&operation);
                const auto start = Clock::now();
                XINPUT_VIBRATION value{};
                if (rumble)
                {
                    const auto motor = [](float level) { return static_cast<WORD>(level * 65535.f + 0.5f); };
                    value = {motor(rumble->low), motor(rumble->high)};
                }
                const bool neutral = value.wLeftMotorSpeed == 0 && value.wRightMotorSpeed == 0;
                // An earlier successful worker stop is valid until another
                // write or a change of endpoint generation.
                result = neutral && slot.neutralConfirmed ? Error::None : xinputError(_api->vibrate(index, value));
                slot.neutralConfirmed = neutral && result == Error::None;
                if (result == Error::None)
                    slot.stopDue = neutral ? Clock::time_point{} : start + rumble->duration;
                else if (result == Error::Disconnected)
                    close(index, true);
            }
        }
        if (command.effect.id != CommandId{})
            _sink->outputCompleted(command.key, command.effect.id, result);
    }

    void run()
    {
        const auto com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        auto deadline = Clock::time_point{};
        std::deque<Command> commands;
        std::vector<AttachedEndpoint> snapshot;
        for (;;)
        {
            bool rescan, stopping, stopMotors, topology;
            std::array<bool, XUSER_MAX_COUNT> baselines;
            {
                std::unique_lock lock(_mutex);
                _wake.wait_until(lock, deadline, [this] {
                    return _stopping || _rescan || _stopMotors || _topology || !_commands.empty() ||
                           std::ranges::any_of(_baselines, [](bool pending) { return pending; });
                });
                stopping = _stopping;
                rescan = std::exchange(_rescan, false);
                stopMotors = std::exchange(_stopMotors, false);
                topology = std::exchange(_topology, false);
                baselines = std::exchange(_baselines, {});
                commands.swap(_commands);
            }
            if (stopMotors || stopping)
                for (DWORD i = 0; i < _slots.size(); ++i)
                    stopMotor(i);
            if (stopping)
                break;

            const auto now = Clock::now();
            for (DWORD i = 0; i < _slots.size(); ++i)
            {
                const bool hasOutput = std::ranges::any_of(commands, [i](const auto& c) { return c.key.endpoint == i; });
                if (topology || rescan || baselines[i] || now >= _slots[i].due || hasOutput)
                    poll(i, baselines[i], topology, snapshot);
            }
            if (topology)
            {
                _sink->topology(std::move(snapshot));
                snapshot.clear();
            }
            for (const auto& command : commands)
                send(command);
            commands.clear();
            deadline = Clock::time_point::max();
            for (DWORD i = 0; i < _slots.size(); ++i)
            {
                auto& slot = _slots[i];
                if (slot.stopDue != Clock::time_point{} && Clock::now() >= slot.stopDue)
                    stopMotor(i);
                deadline = std::min(deadline, slot.due);
                if (slot.stopDue != Clock::time_point{})
                    deadline = std::min(deadline, slot.stopDue);
            }
        }
        if (SUCCEEDED(com))
            CoUninitialize();
    }

    std::unique_ptr<XInputApi> _api;
    ReportSink* _sink = nullptr;
    HCMNOTIFICATION _notification = nullptr;
    std::thread _worker;
    std::mutex _mutex;
    std::condition_variable _wake;
    std::array<Slot, XUSER_MAX_COUNT> _slots;
    std::array<std::uint64_t, XUSER_MAX_COUNT> _published{};
    std::array<bool, XUSER_MAX_COUNT> _baselines{};
    std::deque<Command> _commands;
    std::uint64_t _outputEpoch = 0;
    bool _stopping = false, _active = true, _rescan = false, _stopMotors = false, _topology = false;
};
}

std::unique_ptr<GamepadBackend> makeXInputBackend(std::unique_ptr<XInputApi> api)
{
    return std::make_unique<XInputBackend>(std::move(api));
}

} // namespace cc::input::detail
