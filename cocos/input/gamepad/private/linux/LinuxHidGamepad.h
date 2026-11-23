#pragma once

#include "../GamepadBackend.h"

#include <functional>
#include <memory>

namespace cc::input::detail {

class LinuxHidGamepad {
public:
    virtual ~LinuxHidGamepad() = default;
    virtual int fd() const = 0;
    virtual bool attached() const = 0;
    virtual const std::string& association() const = 0;
    virtual EndpointKey key() const = 0;
    virtual bool read(ReportSink& sink, const std::function<void()>& beforeAttach) = 0;
    virtual RawBaseline baseline() const = 0;
    virtual AttachedEndpoint snapshot() = 0;
    virtual void setSensor(Sensor sensor, bool enabled) = 0;
    virtual Error submit(const OutputCommand& command) = 0;
    virtual void neutral() = 0;
    virtual void tick(std::uint64_t now, bool active) = 0;
    virtual bool needsPolling() const = 0;
};

} // namespace cc::input::detail
