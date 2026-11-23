#pragma once

#include "../output/OutputRouter.h"

namespace cc::input::detail {

class FrameBuilder {
public:
    FrameBuilder(DeviceRegistry&, OutputRouter&, GamepadBackend*);
    const GamepadFrame& frame() const { return _frame; }
    void consume(ReportBatch&);
    void publish(std::uint64_t cutoff);

private:
    void apply(Attach&);
    void apply(Report&);
    void apply(Baseline&);
    void apply(CapabilityUpdate&);
    void apply(HapticCapabilityUpdate&);
    void apply(Detach&);
    void apply(Desync&);
    void apply(Focus&);
    void apply(MappingFence&);
    void apply(LocalFence&);
    void apply(PlayerFence&);
    void apply(NativeCompletion&);
    void apply(OutputNotice&);
    void apply(TopologyLoss&);
    void apply(TopologySnapshot&);

    void emit(DeviceId, Reason, Payload);
    void deviceChange(Device&, Change, Reason);
    void refreshMapping(Device&, Reason, bool force = false);
    void evaluate(Device&, Reason, bool baseline = false, bool suppressHeld = false,
                  std::span<const RawChange> changes = {});
    void release(Device&, Reason);
    void releaseAuxiliary(Device&, EndpointKey, Reason);
    void remove(Device&, EndpointKey, Reason);
    void requestBaselines(Device&);
    void refreshAuxiliary(Device&, Report&);

    DeviceRegistry& _registry;
    OutputRouter& _output;
    GamepadBackend* _backend;
    std::shared_ptr<const MappingDatabase> _mapping;
    std::shared_ptr<std::uint64_t> _epoch = std::make_shared<std::uint64_t>(0);
    GamepadFrame _frame;
    std::vector<GamepadEvent> _events;
    const Record* _record = nullptr;
    std::uint32_t _subIndex = 0;
    bool _active = true;
};

} // namespace cc::input::detail
