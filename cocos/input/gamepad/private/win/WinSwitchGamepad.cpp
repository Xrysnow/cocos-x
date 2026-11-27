#include "WinSwitchGamepad.h"

#include <algorithm>

namespace cc::input::detail {
namespace {

constexpr std::uint64_t replyTimeout = 120000000;
constexpr std::uint64_t rumbleRefresh = 50000000;
constexpr std::uint64_t simpleInputDelay = 100000000;
constexpr unsigned maxAttempts = 3;

enum SetupStep { Handshake, HighSpeed, SecondHandshake, ForceUsb, ReportMode, FactorySticks, UserSticks,
                 FactoryImu, UserImu, Vibration, SetupDone };

const std::array<SwitchRequest, SetupDone> setup{{
    {0x02, true}, {0x03, true}, {0x02, true}, {0x04, true},
    {0x03, false, {0x30}, 1},
    SwitchRequest::spi(SwitchFactorySticks, 18), SwitchRequest::spi(SwitchUserSticks, 22),
    SwitchRequest::spi(SwitchFactoryImu, 24), SwitchRequest::spi(SwitchUserImu, 20),
    {0x48, false, {1}, 1}
}};

SwitchRequest imuRequest(bool enabled)
{
    return {0x40, false, {static_cast<std::uint8_t>(enabled)}, 1};
}

} // namespace

WinSwitchGamepad::WinSwitchGamepad(const std::wstring& path, SwitchModel model, WinHidBus bus, unsigned outputLength)
    : _model(model), _reports(model), _usb(bus == WinHidBus::Usb)
{
    if (bus == WinHidBus::Unknown || outputLength == 0 || outputLength > 512)
        return;
    _buffer.resize(std::max(outputLength, _usb ? 64u : 49u));
    _writable = openHid(path, GENERIC_WRITE, FILE_FLAG_OVERLAPPED);
    if (_writable)
        _written.reset(CreateEventW(nullptr, TRUE, FALSE, nullptr));
    _setupStep = _usb ? Handshake : ReportMode;
}

WinSwitchGamepad::~WinSwitchGamepad()
{
    if (!writable()) return;
    stopOutput();
    if (_imuEnabled || _imuPending.value_or(false))
        write(_output.subcommand(imuRequest(false), SwitchNeutralRumble));
    if (_modeRequested && !_usb && !_startedInFullMode.value_or(false))
        write(_output.subcommand({0x03, false, {0x3f}, 1}, SwitchNeutralRumble));
}

bool WinSwitchGamepad::write(const SwitchPacket& packet)
{
    if (!writable()) return false;
    std::ranges::copy(std::span(packet).first(_usb ? 64u : 49u), _buffer.begin());
    return writeHid(_writable.get(), _written.get(), _buffer);
}

void WinSwitchGamepad::finishSetup(std::span<const std::uint8_t> reply)
{
    if (_setupStep >= ReportMode)
        _subcommandsReady = true;
    switch (_setupStep)
    {
    case FactorySticks: _reports.calibrate(SwitchFactorySticks, reply); break;
    case UserSticks: _reports.calibrate(SwitchUserSticks, reply); break;
    case FactoryImu: _reports.calibrate(SwitchFactoryImu, reply); break;
    case UserImu: _reports.calibrate(SwitchUserImu, reply); break;
    case Vibration: _vibrationReady = true; break;
    default: break;
    }
    ++_setupStep;
    _attempts = 0;
    _nextCommand = 0;
}

void WinSwitchGamepad::updateCapabilities(WinInputEndpoint& endpoint, ReportSink& sink)
{
    if (!_lastFull || !_subcommandsReady)
        return;
    auto& caps = endpoint.descriptor.capabilities;
    const auto body = static_cast<unsigned>(Feature::BodyRumble);
    const auto lights = static_cast<unsigned>(Feature::PlayerLights);
    if (caps.features[lights] && caps.features[body] == _vibrationReady &&
        caps.acknowledgedBodyStop == _vibrationReady)
        return;
    for (auto sensor : {Sensor::Accel, Sensor::Gyro})
    {
        const auto index = static_cast<unsigned>(sensor);
        caps.sensors.set(index);
        caps.nominalHz[index] = 200.f;
    }
    caps.features.set(lights);
    caps.features.set(body, _vibrationReady);
    caps.acknowledgedBodyStop = _vibrationReady;
    caps.playerLightMask = 0x0f;
    sink.capabilitiesChanged(endpoint.key, caps);
}

void WinSwitchGamepad::decode(WinInputEndpoint& endpoint, std::span<const std::uint8_t> bytes,
                               ReportSink& sink, ReportTime time)
{
    if (_setupStep < SetupDone && _attempts)
    {
        if (auto reply = setup[_setupStep].reply(bytes))
            finishSetup(*reply);
    }
    else if (_imuPending && imuRequest(*_imuPending).reply(bytes))
    {
        _imuEnabled = *_imuPending;
        _imuPending.reset();
        _imuAttempts = 0;
    }
    if (_lastFull && time.receivedNs - _lastFull < simpleInputDelay && !bytes.empty() && bytes[0] == 0x3f)
        return;
    const auto sample = _reports.decode(bytes, _sensors.any());
    if (!sample)
    {
        updateCapabilities(endpoint, sink);
        return;
    }
    if (sample->power)
        _lastFull = time.receivedNs;
    constexpr auto maxChanges = std::tuple_size_v<decltype(SwitchInput::buttons)> +
        std::tuple_size_v<decltype(SwitchInput::axes)> + 1;
    std::array<RawChange, maxChanges> changes{};
    unsigned count = 0;
    const auto update = [&](RawKind kind, unsigned index, auto& current, auto value) {
        if (current != value)
        {
            current = value;
            changes[count++] = {kind, index, value};
        }
    };
    for (unsigned i = 0; i < endpoint.state.buttons.size(); ++i)
        update(RawKind::Button, i, endpoint.state.buttons[i], sample->buttons[i]);
    for (unsigned i = 0; i < endpoint.state.axes.size(); ++i)
    {
        update(RawKind::Axis, i, endpoint.state.axes[i], sample->axes[i]);
        endpoint.state.axesKnown[i] = 1;
    }
    if (!endpoint.state.hats.empty())
        update(RawKind::Hat, 0, endpoint.state.hats[0], sample->hat);
    if (!_startedInFullMode)
    {
        _startedInFullMode = sample->power.has_value() && !_modeRequested;
        endpoint.sendBaseline(sink, time);
        count = 0;
    }
    updateCapabilities(endpoint, sink);
    std::array<Motion, 6> motion{};
    unsigned motionCount = 0;
    for (const auto& value : std::span(sample->motion).first(sample->motionCount))
        if (_sensors[static_cast<unsigned>(value.sensor)])
            motion[motionCount++] = value;
    std::optional<Power> power;
    auto& current = endpoint.descriptor.power;
    if (sample->power && (sample->power->percent != current.percent || sample->power->state != current.state))
    {
        current = *sample->power;
        power = current;
    }
    if (count || motionCount || power)
        sink.report(endpoint.key, {std::span(changes).first(count), {}, std::span(motion).first(motionCount),
                                   power, ++endpoint.cursor, time});
}

void WinSwitchGamepad::setSensor(Sensor sensor, bool enabled)
{
    const bool wasEnabled = _sensors.any();
    _sensors.set(static_cast<unsigned>(sensor), enabled);
    if (wasEnabled != _sensors.any())
    {
        _imuAttempts = 0;
        if (!_imuPending) _nextImu = 0;
    }
}

void WinSwitchGamepad::pollProtocol(std::uint64_t now)
{
    if (_setupStep < SetupDone)
    {
        if (now < _nextCommand) return;
        if (_attempts == maxAttempts)
        {
            ++_setupStep;
            _attempts = 0;
            return;
        }
        const auto& request = setup[_setupStep];
        const auto motors = bodyActive(now) ? _motors : SwitchNeutralRumble;
        const bool written = write(request.usb ? _output.usb(request.id) : _output.subcommand(request, motors));
        if (_setupStep == ReportMode)
            _modeRequested |= written;
        if (_setupStep == ForceUsb && written)
        {
            ++_setupStep; // Force USB has no acknowledgement.
            _attempts = 0;
            return;
        }
        ++_attempts;
        _nextCommand = now + replyTimeout;
        return;
    }
    if (now < _nextImu) return;
    const bool enabled = _sensors.any();
    if (_imuPending && *_imuPending != enabled)
    {
        // A write can take effect even if the acknowledgement was lost.
        _imuEnabled = *_imuPending;
        _imuPending.reset();
        _imuAttempts = 0;
    }
    if (_imuEnabled != enabled && _imuAttempts < maxAttempts)
    {
        ++_imuAttempts;
        const auto motors = bodyActive(now) ? _motors : SwitchNeutralRumble;
        if (write(_output.subcommand(imuRequest(enabled), motors)))
            _imuPending = enabled;
        _nextImu = now + replyTimeout;
    }
}

Error WinSwitchGamepad::submit(const OutputCommand& command, const NativeBodyGate& gate)
{
    if (!writable() || !_lastFull || !_subcommandsReady)
        return Error::Unsupported;
    const auto* stop = std::get_if<Stop>(&command);
    if (_stopping && !stop)
        return Error::Busy;
    const auto now = nowNs();
    const bool stopBody = stop && (stop->channel == Channel::All || stop->channel == Channel::Body);
    const bool stopLights = stop && (stop->channel == Channel::All || stop->channel == Channel::Lights);
    const auto* rumble = std::get_if<Rumble>(&command);
    const auto* lights = std::get_if<PlayerLights>(&command);
    if (!rumble && !lights && !stopBody && !stopLights)
        return Error::Unsupported;
    auto deadline = stopBody || !bodyActive(now) ? 0 : _rumbleEnd;
    auto motors = deadline ? _motors : SwitchNeutralRumble;
    if (rumble)
    {
        if (!_vibrationReady) return Error::Unsupported;
        if (!bodyGateOpen(gate)) return Error::Busy;
        motors = encodeSwitchRumble(_model, rumble->low, rumble->high);
        deadline = now + static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(rumble->duration).count());
    }
    if (lights || (stopLights && _lights))
    {
        const auto mask = static_cast<std::uint8_t>(lights ? lights->mask & 0x0f : 0);
        if (!write(_output.subcommand({0x30, false, {mask}, 1}, motors)))
            return Error::BackendFailure;
        _lights = mask;
    }
    else if (rumble || (stopBody && _vibrationReady) || (!deadline && _rumbleEnd))
    {
        if (!write(_output.rumble(motors)))
            return Error::BackendFailure;
    }
    _motors = motors;
    _rumbleEnd = deadline;
    if (rumble)
        _bodyGate = gate;
    else if (!_rumbleEnd)
        _bodyGate.reset();
    if (stopBody || rumble)
        _nextRumble = std::min(now + rumbleRefresh, _rumbleEnd);
    return Error::None;
}

void WinSwitchGamepad::poll()
{
    const auto now = nowNs();
    if (_stopping)
        stopOutput();
    if (!_stopping && _rumbleEnd && now >= _nextRumble)
    {
        if (!bodyActive(now))
        {
            if (submit(Stop{Channel::Body}) == Error::BackendFailure)
            {
                _motors = SwitchNeutralRumble;
                _nextRumble = now + rumbleRefresh;
            }
        }
        else
        {
            write(_output.rumble(_motors));
            _nextRumble = std::min(now + rumbleRefresh, _rumbleEnd);
        }
    }
    pollProtocol(now);
}

void WinSwitchGamepad::stopOutput()
{
    _stopping = (_rumbleEnd || _lights) && submit(Stop{}) != Error::None;
    if (_stopping)
        _motors = SwitchNeutralRumble;
}

void WinSwitchGamepad::resetTopology()
{
    stopOutput();
    setSensor(Sensor::Accel, false);
    setSensor(Sensor::Gyro, false);
}

} // namespace cc::input::detail
