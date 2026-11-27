#include "haptics/private/HapticControl.h"
#include <cmath>
#include <limits>

namespace cc::haptics
{
namespace
{
template <class T>
T gone()
{
    return T{.error = ErrorInfo{Error::NotFound, {}}};
}
}  // namespace
Result<HapticTime> HapticTime::afterMs(double deltaMs) const
{
    if (!std::isfinite(deltaMs) || deltaMs < 0 ||
        deltaMs * 1000 >= double(std::numeric_limits<std::int64_t>::max() - us))
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    auto result  = *this;
    result.us   += std::llround(deltaMs * 1000);
    return {result, {}};
}
std::vector<TargetInfo> HapticService::enumerate() const
{
    return _control->enumerate();
}
Result<TargetId> HapticService::handset() const
{
    return _control->target({});
}
Result<TargetId> HapticService::gamepad(input::DeviceId id) const
{
    return _control->target(id);
}
Result<Capabilities> HapticService::capabilities(TargetId id) const
{
    return _control->capabilities(id);
}
HapticTime HapticService::now() const
{
    return _control->now();
}
Result<HapticScope> HapticService::createScope()
{
    return _control->scope(_control);
}
HapticScope::HapticScope(HapticScope&& other) noexcept
    : _control(std::move(other._control)), _id(std::exchange(other._id, 0))
{
}
HapticScope& HapticScope::operator=(HapticScope&& other) noexcept
{
    if (this != &other)
    {
        close();
        _control = std::move(other._control);
        _id      = std::exchange(other._id, 0);
    }
    return *this;
}
HapticScope::~HapticScope()
{
    close();
}
void HapticScope::close() noexcept
{
    if (auto control = _control.lock())
        control->close(_id);
    _control.reset();
}
RawSession::RawSession(RawSession&& other) noexcept
    : _control(std::move(other._control)), _id(std::exchange(other._id, 0))
{
}
RawSession& RawSession::operator=(RawSession&& other) noexcept
{
    if (this != &other)
    {
        close();
        _control = std::move(other._control);
        _id      = std::exchange(other._id, 0);
    }
    return *this;
}
RawSession::~RawSession()
{
    close();
}
void RawSession::close() noexcept
{
    if (auto control = _control.lock())
        control->closeRaw(_id);
    _control.reset();
}
Result<PlaybackId> HapticScope::play(TargetId target, const HapticClip& clip, const PlayOptions& options)
{
    if (auto control = _control.lock())
        return control->play(_id, target, clip, options);
    return gone<Result<PlaybackId>>();
}
Status HapticScope::stop(PlaybackId playback)
{
    if (auto control = _control.lock())
        return control->stop(_id, playback);
    return gone<Status>();
}
Result<PlaybackSnapshot> HapticScope::readPlayback(PlaybackId playback)
{
    if (auto control = _control.lock())
        return control->read(_id, playback);
    return gone<Result<PlaybackSnapshot>>();
}
Result<OperationId> HapticScope::stopTarget(TargetId target)
{
    if (auto control = _control.lock())
        return control->stopTarget(_id, target);
    return gone<Result<OperationId>>();
}
Result<OperationSnapshot> HapticScope::readOperation(OperationId operation)
{
    if (auto control = _control.lock())
        return control->read(_id, operation);
    return gone<Result<OperationSnapshot>>();
}
Result<RawSession> HapticScope::acquireRaw(TargetId target, AcquirePolicy policy)
{
    if (auto control = _control.lock())
        return control->acquire(_control, _id, target, policy);
    return gone<Result<RawSession>>();
}
Result<OperationId> RawSession::cancel()
{
    if (auto control = _control.lock())
        return control->cancelRaw(_id);
    return gone<Result<OperationId>>();
}
RawSnapshot RawSession::state() const
{
    if (auto control = _control.lock())
        return control->rawState(_id);
    return {};
}
}  // namespace cc::haptics
