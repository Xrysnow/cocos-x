#include "haptics/private/HapticControl.h"
#include <algorithm>
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
Status HapticService::setCalibration(TargetId target, const HapticCalibration& profile)
{
    return _control->setCalibration(target, profile);
}
Status HapticService::setOutputSettings(const OutputSettings& settings)
{
    return _control->setOutputSettings(settings);
}
std::weak_ptr<const void> HapticService::lifetimeToken() const
{
    return _control->lifetimeToken();
}
Status HapticService::preparePcm(TargetId target)
{
    return _control->preparePcm(target);
}
Status HapticService::setPcmModeTiming(TargetId target, const PcmModeTiming& timing)
{
    return _control->setPcmModeTiming(target, timing);
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
namespace
{
std::atomic_uint64_t nextPlayer{1};
}
Result<OperationId> RawSession::oneShot(const AndroidOneShot& pulse)
{
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind = detail::MobileCommand::Kind::Android;
        cmd.raw  = pulse;
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::waveform(const AndroidWaveform& waveform)
{
    if (waveform.steps.size() > 128)
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind = detail::MobileCommand::Kind::Android;
        cmd.raw  = waveform;
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::predefined(AndroidEffect effect)
{
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind = detail::MobileCommand::Kind::Android;
        cmd.raw  = effect;
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::composition(const AndroidComposition& composition)
{
    if (composition.steps.size() > 16)
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind = detail::MobileCommand::Kind::Android;
        cmd.raw  = composition;
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::envelope(const AndroidEnvelope& envelope)
{
    if (envelope.points.size() > 64)
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind = detail::MobileCommand::Kind::Android;
        cmd.raw  = envelope;
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::sendParameters(RawPlayerId player, const AppleParameters& parameters)
{
    if (parameters.parameters.size() > 128)
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind   = detail::MobileCommand::Kind::Parameters;
        cmd.raw    = parameters;
        cmd.player = static_cast<std::uint64_t>(player);
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<OperationId> RawSession::sendCurve(RawPlayerId player, const AppleParameterCurve& curve)
{
    if (curve.points.size() > 16)
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind   = detail::MobileCommand::Kind::Curve;
        cmd.raw    = curve;
        cmd.player = static_cast<std::uint64_t>(player);
        return c->rawCommand(_id, std::move(cmd));
    }
    return gone<Result<OperationId>>();
}
Result<RawPlayback> RawSession::playPattern(const ApplePattern& pattern, bool replace)
{
    if (pattern.events.size() > 128 || pattern.parameters.size() > 128 || pattern.curves.size() > 32 ||
        std::ranges::any_of(pattern.curves, [](auto& c) { return c.points.size() > 16; }))
        return {{}, ErrorInfo{Error::InvalidArgument, {}}};
    if (auto c = _control.lock())
    {
        detail::MobileCommand cmd;
        cmd.kind    = detail::MobileCommand::Kind::Apple;
        cmd.raw     = pattern;
        auto player = nextPlayer++;
        cmd.player  = player;
        cmd.replace = replace;
        auto result = c->rawCommand(_id, std::move(cmd));
        if (!result.value)
            return {{}, result.error};
        return {RawPlayback{static_cast<RawPlayerId>(player), *result.value}, {}};
    }
    return gone<Result<RawPlayback>>();
}
Result<OperationId> RawSession::stop(RawPlayerId player)
{
    if (auto c = _control.lock())
        return c->stopPlayer(_id, player);
    return gone<Result<OperationId>>();
}
RawSnapshot RawSession::state() const
{
    if (auto control = _control.lock())
        return control->rawState(_id);
    return {};
}
}  // namespace cc::haptics
