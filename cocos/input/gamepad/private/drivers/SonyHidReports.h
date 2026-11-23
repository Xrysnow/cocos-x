#pragma once

#include "DualSenseReports.h"
#include "DualShock4Reports.h"

namespace cc::input::detail {

enum class SonyHidModel { DualShock4, DualSense, DualSenseEdge };

inline std::optional<SonyHidModel> sonyHidModel(unsigned vendor, unsigned product)
{
    if (const auto model = dualSenseModel(vendor, product))
        return *model == DualSenseModel::Edge ? SonyHidModel::DualSenseEdge : SonyHidModel::DualSense;
    if (isDualShock4Product(static_cast<std::uint16_t>(vendor), static_cast<std::uint16_t>(product)))
        return SonyHidModel::DualShock4;
    return {};
}

inline const char* sonyHidName(SonyHidModel model)
{
    switch (model)
    {
    case SonyHidModel::DualShock4: return "DualShock 4 Wireless Controller";
    case SonyHidModel::DualSense: return "DualSense Wireless Controller";
    case SonyHidModel::DualSenseEdge: return "DualSense Edge Wireless Controller";
    }
    return "Sony Gamepad";
}

inline DualSenseModel dualSenseModelFor(SonyHidModel model)
{
    return model == SonyHidModel::DualSenseEdge ? DualSenseModel::Edge : DualSenseModel::Standard;
}

inline DualShock4Transport dualShock4TransportFor(DualSenseTransport transport)
{
    return transport == DualSenseTransport::Bluetooth ? DualShock4Transport::Bluetooth : DualShock4Transport::Usb;
}

inline void configureSonyHidLayout(RawLayout& layout, SonyHidModel model,
                                   unsigned standardButtonCount = DualSenseBaseButtonCount)
{
    layout.buttonCount = model == SonyHidModel::DualShock4 ? 12 :
        model == SonyHidModel::DualSenseEdge ? 17 : standardButtonCount;
    layout.axisCount = 6;
    layout.hatCount = 1;
    layout.builtInMapping =
        "a:b0,b:b1,x:b2,y:b3,back:b4,guide:b5,start:b6,leftstick:b7,rightstick:b8,"
        "leftshoulder:b9,rightshoulder:b10,touchpad:b11,"
        "leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:a4,righttrigger:a5,"
        "dpup:h0.1,dpright:h0.2,dpdown:h0.4,dpleft:h0.8,face:sony";
    if (model != SonyHidModel::DualShock4)
        layout.builtInMapping += ",misc1:b12";
    if (model == SonyHidModel::DualSenseEdge)
        layout.builtInMapping += ",paddle4:b13,paddle3:b14,paddle2:b15,paddle1:b16";
}

struct SonyHidInput : DualSenseInput {
    bool hasTouchSample;
};

class SonyHidReports {
public:
    SonyHidReports(SonyHidModel model, DualSenseTransport transport) : _model(model), _transport(transport) {}

    void calibrate(std::span<const std::uint8_t> report)
    {
        _calibration = _model == SonyHidModel::DualShock4 ?
            decodeDualShock4Calibration(dualShock4TransportFor(_transport), report) :
            decodeDualSenseCalibration(_transport, report);
    }

    bool hasCalibration() const { return _calibration.has_value(); }

    std::optional<SonyHidInput> decode(std::span<const std::uint8_t> report)
    {
        if (_model == SonyHidModel::DualShock4)
        {
            if (auto sample = decodeDualShock4Input(dualShock4TransportFor(_transport), report, _calibration))
            {
                const auto time = _ds4Clock.sampleTimeNs(static_cast<std::uint16_t>(sample->sensorTicks));
                for (auto& value : sample->motion) value.deviceTimeNs = time;
                return SonyHidInput{*sample, sample->hasTouchSample};
            }
            return {};
        }
        if (auto sample = decodeDualSenseInput(_transport, report, _calibration, dualSenseModelFor(_model)))
        {
            if (_model == SonyHidModel::DualSenseEdge)
            {
                // The two digital trigger bits contribute to the decoded axes. In the
                // SDL HIDAPI layout, the four extra buttons occupy these raw slots.
                for (unsigned i = 0; i < 4; ++i)
                    sample->buttons[13 + i] = sample->buttons[DualSenseBaseButtonCount + i];
            }
            return SonyHidInput{*sample, true};
        }
        return {};
    }

    std::optional<DualSenseControls> simple(std::span<const std::uint8_t> report) const
    {
        if (_model == SonyHidModel::DualShock4)
            return decodeDualShock4Simple(dualShock4TransportFor(_transport), report);
        if (_transport != DualSenseTransport::Bluetooth) return {};
        auto sample = decodeDualSenseBluetoothSimple(report);
        if (sample && _model == SonyHidModel::DualSenseEdge)
        {
            sample->buttons[13] = 0;
            sample->buttons[14] = 0;
        }
        return sample;
    }

private:
    SonyHidModel _model;
    DualSenseTransport _transport;
    std::optional<DualSenseCalibration> _calibration;
    DualShock4SensorClock _ds4Clock;
};

class SonyHidOutput {
public:
    explicit SonyHidOutput(SonyHidModel model)
    {
        if (model == SonyHidModel::DualShock4) _state.emplace<DualShock4Output>();
    }

    void configureRumble(SonyHidModel model, DualSenseTransport transport,
                         std::optional<std::uint16_t> firmware)
    {
        if (auto* output = std::get_if<DualSenseOutput>(&_state))
            output->configureRumble(dualSenseModelFor(model), transport, firmware);
    }

    bool apply(const OutputCommand& command, std::uint64_t now)
    {
        return std::visit([&](auto& output) { return output.apply(command, now); }, _state);
    }

    bool expire(std::uint64_t now)
    {
        return std::visit([&](auto& output) { return output.expire(now); }, _state);
    }

    bool setHapticsMode(bool enabled)
    {
        auto* output = std::get_if<DualSenseOutput>(&_state);
        if (!output)
            return false;
        output->setHapticsMode(enabled);
        return true;
    }

    bool hasTimedRumble() const
    {
        return std::visit([](const auto& output) { return output.hasTimedRumble(); }, _state);
    }

    std::span<const std::uint8_t> encode(DualSenseTransport transport, unsigned usbLength = 0,
                                         DualSenseOutputKind kind = DualSenseOutputKind::Effects)
    {
        if (auto* output = std::get_if<DualSenseOutput>(&_state))
            return output->encode(transport, usbLength ? usbLength : 63, kind);
        if (kind == DualSenseOutputKind::ReleaseBluetoothLights) return {};
        return std::get<DualShock4Output>(_state).encode(dualShock4TransportFor(transport),
            usbLength ? usbLength : 32, kind == DualSenseOutputKind::EnableBluetooth);
    }

private:
    std::variant<DualSenseOutput, DualShock4Output> _state;
};

} // namespace cc::input::detail
