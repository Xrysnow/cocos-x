#include "AudioDirectBackend.h"

#include <AL/alc.h>
#include <pipewire/extensions/metadata.h>
#include <pipewire/pipewire.h>
#include <spa/node/io.h>
#include <spa/param/audio/format-utils.h>
#include <spa/utils/json.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <limits>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>

namespace cc::audio::detail {
namespace {

using Position = AudioChannelPosition;
using Error = AudioOutputError;
using Clock = std::chrono::steady_clock;
using namespace std::chrono_literals;
namespace fs = std::filesystem;

struct Channel {
    Position position;
    std::string_view name;
    spa_audio_channel spa;
};

constexpr std::array channels{
    Channel{Position::FrontLeft, "FL", SPA_AUDIO_CHANNEL_FL},
    Channel{Position::FrontRight, "FR", SPA_AUDIO_CHANNEL_FR},
    Channel{Position::FrontCenter, "FC", SPA_AUDIO_CHANNEL_FC},
    Channel{Position::Lfe, "LFE", SPA_AUDIO_CHANNEL_LFE},
    Channel{Position::RearLeft, "RL", SPA_AUDIO_CHANNEL_RL},
    Channel{Position::RearRight, "RR", SPA_AUDIO_CHANNEL_RR},
    Channel{Position::SideLeft, "SL", SPA_AUDIO_CHANNEL_SL},
    Channel{Position::SideRight, "SR", SPA_AUDIO_CHANNEL_SR},
};

std::optional<Position> channelPosition(std::string_view name)
{
    const auto match = std::ranges::find(channels, name, &Channel::name);
    if (match == channels.end())
        return {};
    return match->position;
}

std::string_view property(const spa_dict* props, const char* key)
{
    if (const auto* value = props ? spa_dict_lookup(props, key) : nullptr)
        return value;
    return {};
}

template<class Integer>
std::optional<Integer> integerProperty(const spa_dict* props, const char* key)
{
    const auto text = property(props, key);
    if (text.empty())
        return {};
    Integer value{};
    const auto end = text.data() + text.size();
    const auto result = std::from_chars(text.data(), end, value);
    if (result.ec == std::errc{} && result.ptr == end)
        return value;
    return {};
}

std::vector<Position> layout(std::string_view positions)
{
    constexpr std::string_view separators = "[, ]\t\r\n\"";
    std::vector<Position> result;
    while (!positions.empty())
    {
        const auto start = positions.find_first_not_of(separators);
        if (start == positions.npos)
            break;
        positions.remove_prefix(start);
        const auto end = positions.find_first_of(separators);
        const auto position = channelPosition(positions.substr(0, end));
        if (!position || std::ranges::find(result, *position) != result.end())
            return {};
        result.push_back(*position);
        positions.remove_prefix(end == positions.npos ? positions.size() : end);
    }
    return result;
}

fs::path usbParent(fs::path path)
{
    while (path != path.root_path() && !path.empty())
    {
        std::error_code error;
        if (fs::exists(path / "idVendor", error) && fs::exists(path / "idProduct", error))
            return path;
        path = path.parent_path();
    }
    return {};
}

std::string findUsbPath(const spa_dict* props)
{
    std::error_code error;
    const auto syspath = property(props, "sysfs.path");
    if (syspath.starts_with("/devices/"))
    {
        const auto path = fs::canonical(fs::path("/sys") / fs::path(syspath).relative_path(), error);
        if (!error)
            return usbParent(path).string();
    }
    auto card = integerProperty<unsigned>(props, "api.alsa.pcm.card");
    if (!card) card = integerProperty<unsigned>(props, "alsa.card");
    if (!card) card = integerProperty<unsigned>(props, "api.alsa.card");
    if (!card)
        return {};
    const auto path = fs::canonical(fs::path("/sys/class/sound") /
        ("card" + std::to_string(*card)) / "device", error);
    return error ? std::string{} : usbParent(path).string();
}

class LoopLock {
public:
    explicit LoopLock(pw_thread_loop* loop) : _loop(loop) { pw_thread_loop_lock(_loop); }
    ~LoopLock() { pw_thread_loop_unlock(_loop); }
    LoopLock(const LoopLock&) = delete;
    LoopLock& operator=(const LoopLock&) = delete;

private:
    pw_thread_loop* _loop;
};

class Monitor {
    struct Node {
        pw_node* proxy = nullptr;
        spa_hook listener{};
        std::string name, description, usbPath, mainName;
        std::optional<std::uint64_t> serial;
        unsigned rate = 48000;
        std::vector<Position> positions;

        ~Node()
        {
            if (proxy)
            {
                spa_hook_remove(&listener);
                pw_proxy_destroy(reinterpret_cast<pw_proxy*>(proxy));
            }
        }

        void update(const spa_dict* props)
        {
            if (const auto value = property(props, PW_KEY_NODE_NAME); !value.empty())
                name = value;
            auto value = property(props, PW_KEY_NODE_DESCRIPTION);
            if (value.empty())
                value = property(props, PW_KEY_NODE_NICK);
            if (!value.empty())
                description = value;
            if (const auto value = integerProperty<std::uint64_t>(props, PW_KEY_OBJECT_SERIAL))
                serial = value;
            if (const auto value = integerProperty<unsigned>(props, "audio.rate"); value && *value)
                rate = *value;
            if (const auto value = property(props, "audio.position"); !value.empty())
                positions = layout(value);
            if (usbPath.empty())
                usbPath = findUsbPath(props);
        }
    };

    struct Port {
        unsigned node;
        bool input;
        std::optional<Position> position;
    };

    struct Link {
        unsigned inputNode, inputPort, outputNode, outputPort;
    };

public:
    explicit Monitor(std::uint64_t generation) : _generation(std::to_string(generation)) {}

    ~Monitor()
    {
        if (_started) pw_thread_loop_stop(loop);
        _nodes.clear();
        removeMetadata();
        if (_registry)
        {
            spa_hook_remove(&_registryHook);
            pw_proxy_destroy(reinterpret_cast<pw_proxy*>(_registry));
        }
        if (core)
        {
            spa_hook_remove(&_coreHook);
            pw_core_disconnect(core);
        }
        if (_context) pw_context_destroy(_context);
        if (loop) pw_thread_loop_destroy(loop);
    }

    bool start()
    {
        static const auto initialized = [] { pw_init(nullptr, nullptr); return true; }();
        (void)initialized;
        loop = pw_thread_loop_new("cocos-direct-audio", nullptr);
        if (!loop || pw_thread_loop_start(loop) != 0)
            return false;
        _started = true;
        const LoopLock lock(loop);
        _context = pw_context_new(pw_thread_loop_get_loop(loop), nullptr, 0);
        core = _context ? pw_context_connect(_context, nullptr, 0) : nullptr;
        if (!core)
            return false;
        static constexpr auto coreEvents = [] {
            pw_core_events events{};
            events.version = PW_VERSION_CORE_EVENTS;
            events.done = [](void* data, unsigned id, int sequence) {
                auto& monitor = *static_cast<Monitor*>(data);
                if (id == PW_ID_CORE)
                {
                    monitor._done = sequence;
                    pw_thread_loop_signal(monitor.loop, false);
                }
            };
            events.error = [](void* data, unsigned id, int, int error, const char*) {
                auto& monitor = *static_cast<Monitor*>(data);
                if (id == PW_ID_CORE && error == -EPIPE)
                {
                    monitor.failed = true;
                    pw_thread_loop_signal(monitor.loop, false);
                }
            };
            return events;
        }();
        pw_core_add_listener(core, &_coreHook, &coreEvents, this);
        _registry = pw_core_get_registry(core, PW_VERSION_REGISTRY, 0);
        if (!_registry)
            return false;
        static constexpr pw_registry_events registryEvents{PW_VERSION_REGISTRY_EVENTS, onGlobal, onRemove};
        pw_registry_add_listener(_registry, &_registryHook, &registryEvents, this);
        // Bindings created during enumeration need a second round trip.
        return synchronize() && synchronize();
    }

    bool synchronize()
    {
        const auto sequence = pw_core_sync(core, PW_ID_CORE, 0);
        timespec until{};
        if (sequence < 0 || pw_thread_loop_get_time(loop, &until, 250'000'000) < 0)
            return false;
        while (_done < sequence && !failed)
            if (pw_thread_loop_timed_wait_full(loop, &until) < 0)
                return false;
        return !failed;
    }

    std::vector<DirectEndpoint> endpoints() const
    {
        std::vector<DirectEndpoint> result;
        for (const auto& [id, node] : _nodes)
        {
            if (!node.serial || node.name.empty())
                continue;
            DirectEndpoint item;
            item.key = key(node);
            item.name = node.description.empty() ? node.name : node.description;
            item.deviceSelector = node.name;
            item.mainDeviceName = node.mainName;
            item.usbPath = node.usbPath;
            item.isDefault = node.name == _default;
            item.sampleRate = node.rate;
            item.channels = positionsOf(id, node);
            result.push_back(std::move(item));
        }
        return result;
    }

    void rememberMainName(const std::string& connection, const std::string& name)
    {
        for (auto& [id, node] : _nodes)
            if (node.serial && key(node) == connection)
                node.mainName = name;
    }

    std::optional<std::pair<unsigned, std::uint64_t>> find(const std::string& connection) const
    {
        for (const auto& [id, node] : _nodes)
            if (node.serial && key(node) == connection)
                return std::pair{id, *node.serial};
        return {};
    }

    bool contains(unsigned id, std::uint64_t serial) const
    {
        const auto node = _nodes.find(id);
        return node != _nodes.end() && node->second.serial == serial;
    }

    bool routes(unsigned source, unsigned sink, const std::vector<Position>& positions) const
    {
        std::array<bool, channels.size()> seen{};
        std::size_t matched = 0;
        for (const auto& [id, link] : _links)
        {
            if (link.outputNode != source)
                continue;
            const auto input = _ports.find(link.inputPort);
            const auto output = _ports.find(link.outputPort);
            if (link.inputNode != sink || input == _ports.end() || output == _ports.end() ||
                !input->second.input || output->second.input || input->second.node != sink ||
                output->second.node != source || !input->second.position ||
                input->second.position != output->second.position)
                return false;
            const auto index = std::ranges::find(positions, *input->second.position) - positions.begin();
            if (static_cast<std::size_t>(index) == positions.size() || seen[index])
                return false;
            seen[index] = true;
            ++matched;
        }
        return matched == positions.size();
    }

    pw_thread_loop* loop = nullptr;
    pw_core* core = nullptr;
    std::atomic_bool failed = false;

private:
    std::string key(const Node& node) const
    {
        return _generation + ":" + std::to_string(*node.serial);
    }

    std::vector<Position> positionsOf(unsigned id, const Node& node) const
    {
        std::vector<Position> result;
        for (const auto& [portId, port] : _ports)
        {
            if (port.node != id || !port.input)
                continue;
            if (!port.position || std::ranges::find(result, *port.position) != result.end())
                return {};
            result.push_back(*port.position);
        }
        if (node.positions.empty())
            return result;
        return result.empty() || std::ranges::is_permutation(result, node.positions)
            ? node.positions : std::vector<Position>{};
    }

    static void onGlobal(void* data, unsigned id, unsigned, const char* type, unsigned version,
                         const spa_dict* props)
    {
        auto& monitor = *static_cast<Monitor*>(data);
        const std::string_view interfaceType(type);
        if (interfaceType == PW_TYPE_INTERFACE_Node && property(props, PW_KEY_MEDIA_CLASS) == "Audio/Sink")
        {
            auto [it, added] = monitor._nodes.try_emplace(id);
            if (!added)
                return;
            auto& node = it->second;
            node.update(props);
            node.proxy = static_cast<pw_node*>(pw_registry_bind(monitor._registry, id, type,
                std::min<unsigned>(version, PW_VERSION_NODE), 0));
            if (!node.proxy)
                return;
            static constexpr auto events = [] {
                pw_node_events value{};
                value.version = PW_VERSION_NODE_EVENTS;
                value.info = [](void* user, const pw_node_info* info) {
                    if (info->change_mask & PW_NODE_CHANGE_MASK_PROPS)
                        static_cast<Node*>(user)->update(info->props);
                };
                return value;
            }();
            pw_node_add_listener(node.proxy, &node.listener, &events, &node);
        }
        else if (interfaceType == PW_TYPE_INTERFACE_Port)
        {
            const auto node = integerProperty<unsigned>(props, PW_KEY_NODE_ID);
            const auto direction = property(props, PW_KEY_PORT_DIRECTION);
            if (node && (direction == "in" || direction == "out"))
                monitor._ports.emplace(id, Port{*node, direction == "in",
                    channelPosition(property(props, PW_KEY_AUDIO_CHANNEL))});
        }
        else if (interfaceType == PW_TYPE_INTERFACE_Link)
        {
            const auto input = integerProperty<unsigned>(props, PW_KEY_LINK_INPUT_NODE);
            const auto inputPort = integerProperty<unsigned>(props, PW_KEY_LINK_INPUT_PORT);
            const auto output = integerProperty<unsigned>(props, PW_KEY_LINK_OUTPUT_NODE);
            const auto outputPort = integerProperty<unsigned>(props, PW_KEY_LINK_OUTPUT_PORT);
            if (input && inputPort && output && outputPort)
                monitor._links.emplace(id, Link{*input, *inputPort, *output, *outputPort});
        }
        else if (interfaceType == PW_TYPE_INTERFACE_Metadata &&
                 property(props, PW_KEY_METADATA_NAME) == "default" && !monitor._metadata)
        {
            monitor._metadata = static_cast<pw_metadata*>(pw_registry_bind(monitor._registry, id,
                type, std::min<unsigned>(version, PW_VERSION_METADATA), 0));
            if (!monitor._metadata)
                return;
            monitor._metadataId = id;
            static constexpr pw_metadata_events events{PW_VERSION_METADATA_EVENTS, onMetadata};
            pw_metadata_add_listener(monitor._metadata, &monitor._metadataHook, &events, &monitor);
        }
        pw_thread_loop_signal(monitor.loop, false);
    }

    static void onRemove(void* data, unsigned id)
    {
        auto& monitor = *static_cast<Monitor*>(data);
        monitor._nodes.erase(id);
        monitor._ports.erase(id);
        monitor._links.erase(id);
        if (monitor._metadata && monitor._metadataId == id)
            monitor.removeMetadata();
        pw_thread_loop_signal(monitor.loop, false);
    }

    static int onMetadata(void* data, unsigned subject, const char* key, const char*, const char* value)
    {
        if (subject != PW_ID_CORE || (key && std::string_view(key) != "default.audio.sink"))
            return 0;
        auto& name = static_cast<Monitor*>(data)->_default;
        name.clear();
        if (!key || !value)
            return 0;
        spa_json document{}, object{};
        spa_json_init(&document, value, std::strlen(value));
        if (spa_json_enter_object(&document, &object) <= 0)
            return 0;
        std::array<char, 1024> text{};
        if (spa_json_get_string(&object, text.data(), text.size()) > 0 &&
            std::string_view(text.data()) == "name" &&
            spa_json_get_string(&object, text.data(), text.size()) > 0)
            name = text.data();
        return 0;
    }

    void removeMetadata()
    {
        _default.clear();
        if (_metadata)
        {
            spa_hook_remove(&_metadataHook);
            pw_proxy_destroy(reinterpret_cast<pw_proxy*>(_metadata));
            _metadata = nullptr;
        }
    }

    std::string _generation;
    bool _started = false;
    int _done = 0;
    pw_context* _context = nullptr;
    pw_registry* _registry = nullptr;
    pw_metadata* _metadata = nullptr;
    unsigned _metadataId = 0;
    spa_hook _coreHook{}, _registryHook{}, _metadataHook{};
    std::string _default;
    std::map<unsigned, Node> _nodes;
    std::map<unsigned, Port> _ports;
    std::map<unsigned, Link> _links;
};

struct MonitorSlot {
    std::mutex mutex;
    std::shared_ptr<Monitor> current;
    Clock::time_point retryAt;
    std::uint64_t generation = 0;
};

MonitorSlot& monitorSlot()
{
    static MonitorSlot state;
    return state;
}

std::shared_ptr<Monitor> monitor()
{
    auto& state = monitorSlot();
    const std::lock_guard lock(state.mutex);
    if (state.current && !state.current->failed)
        return state.current;
    const auto now = Clock::now();
    if (now < state.retryAt)
        return {};
    state.retryAt = now + 1s;
    auto candidate = std::make_shared<Monitor>(++state.generation);
    if (!candidate->start())
        return {};
    return state.current = std::move(candidate);
}

std::string openAlName(const std::string& selector)
{
    const auto close = [](ALCdevice* device) { alcCloseDevice(device); };
    const std::unique_ptr<ALCdevice, decltype(close)> device(alcOpenDevice(selector.c_str()), close);
    if (!device)
        return {};
    const auto* name = alcGetString(device.get(), ALC_ALL_DEVICES_SPECIFIER);
    return name ? name : "";
}

class PipeWireOutput final : public OutputStream {
    static constexpr std::size_t queueFrames = outputBlockFrames * outputQueueBlocks;
    static constexpr std::size_t historyEntries = 256;

    struct Segment {
        std::uint64_t deviceStart, validStart;
        std::uint64_t frames, validFrames;
    };

    struct RealtimeTiming {
        std::uint64_t observedNs;
        std::uint64_t ticks;
        std::uint64_t deviceFrame;
        std::uint64_t nativeTailFrames;
    };

public:
    PipeWireOutput(std::shared_ptr<Monitor> monitor, const DirectEndpoint& endpoint,
                   unsigned node, std::uint64_t serial, bool realtime)
        : _monitor(std::move(monitor)), _endpoint(endpoint), _targetNode(node), _targetSerial(serial),
          _generation(realtime ? nextRealtimeClockGeneration() : 0),
          _pcm((queueFrames + endpoint.sampleRate) * endpoint.channels.size())
    {
        if (realtime)
            _front = {static_cast<unsigned>(std::ranges::find(endpoint.channels, Position::FrontLeft) - endpoint.channels.begin()),
                static_cast<unsigned>(std::ranges::find(endpoint.channels, Position::FrontRight) - endpoint.channels.begin())};
    }

    ~PipeWireOutput() override
    {
        const LoopLock lock(_monitor->loop);
        closeStream();
    }

    Error open()
    {
        const LoopLock lock(_monitor->loop);
        return openLocked();
    }

private:
    bool gateOpen() const { return _gate && _gate->load(std::memory_order_acquire); }

    void closeStream()
    {
        if (!_stream)
            return;
        spa_hook_remove(&_listener);
        pw_stream_destroy(_stream);
        _stream = nullptr;
        _listener = {};
        _state = PW_STREAM_STATE_CONNECTING;
        _formatVerified = false;
        _graphPosition = nullptr;
    }

    Error openLocked()
    {
        const auto target = std::to_string(_targetSerial);
        const auto latency = std::to_string(outputBlockFrames) + "/" + std::to_string(_endpoint.sampleRate);
        auto* props = pw_properties_new(PW_KEY_MEDIA_TYPE, "Audio", PW_KEY_MEDIA_CATEGORY, "Playback",
            PW_KEY_MEDIA_ROLE, "Game", PW_KEY_TARGET_OBJECT, target.c_str(), "node.dont-fallback", "true",
            "node.dont-reconnect", "true", "node.dont-move", "true", "stream.dont-remix", "true",
            PW_KEY_NODE_LATENCY, latency.c_str(), nullptr);
        if (!props)
            return Error::BackendFailure;
        if (_generation)
        {
            const auto ceiling = std::to_string(realtimeMaxQuantumFrames) + "/" + std::to_string(_endpoint.sampleRate);
            pw_properties_set(props, PW_KEY_NODE_MAX_LATENCY, ceiling.c_str());
            pw_properties_set(props, PW_KEY_NODE_RATE, "1/48000");
        }
        _stream = pw_stream_new(_monitor->core, "Cocos direct audio", props);
        if (!_stream)
            return Error::BackendFailure;
        static constexpr auto events = [] {
            pw_stream_events value{};
            value.version = PW_VERSION_STREAM_EVENTS;
            value.state_changed = [](void* data, pw_stream_state, pw_stream_state state, const char*) {
                auto& self = *static_cast<PipeWireOutput*>(data);
                self._state = state;
                pw_thread_loop_signal(self._monitor->loop, false);
            };
            value.param_changed = [](void* data, unsigned id, const spa_pod* param) {
                auto& self = *static_cast<PipeWireOutput*>(data);
                if (id == SPA_PARAM_Format)
                {
                    if (param || self._active)
                        self._formatVerified = self.verifyFormat(param);
                    pw_thread_loop_signal(self._monitor->loop, false);
                }
            };
            value.io_changed = [](void* data, std::uint32_t id, void* area, std::uint32_t size) {
                auto& self = *static_cast<PipeWireOutput*>(data);
                if (id == SPA_IO_Position)
                    self._graphPosition = size >= sizeof(spa_io_position) ? static_cast<spa_io_position*>(area) : nullptr;
            };
            value.process = [](void* data) { static_cast<PipeWireOutput*>(data)->process(); };
            value.drained = [](void* data) {
                auto& self = *static_cast<PipeWireOutput*>(data);
                if (self._draining && self._active)
                {
                    self._consumed = self._written;
                    self._drained = true;
                    if (self._discarded)
                    {
                        if (const auto timing = self.realtimeTiming())
                            self._drainedDeviceFrame = timing->deviceFrame;
                    }
                    pw_thread_loop_signal(self._monitor->loop, false);
                }
            };
            return value;
        }();
        pw_stream_add_listener(_stream, &_listener, &events, this);
        alignas(spa_pod) std::array<std::uint8_t, 512> storage{};
        auto builder = SPA_POD_BUILDER_INIT(storage.data(), storage.size());
        spa_audio_info_raw format{};
        format.format = SPA_AUDIO_FORMAT_S16;
        format.rate = _endpoint.sampleRate;
        format.channels = static_cast<unsigned>(_endpoint.channels.size());
        for (unsigned i = 0; i < format.channels; ++i)
            format.position[i] = std::ranges::find(channels, _endpoint.channels[i], &Channel::position)->spa;
        const spa_pod* params[]{spa_format_audio_raw_build(&builder, SPA_PARAM_EnumFormat, &format)};
        const auto flags = static_cast<pw_stream_flags>(PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_INACTIVE |
            PW_STREAM_FLAG_MAP_BUFFERS | PW_STREAM_FLAG_DONT_RECONNECT);
        if (pw_stream_connect(_stream, PW_DIRECTION_OUTPUT, PW_ID_ANY, flags, params, 1) != 0)
            return Error::BackendFailure;
        // The PipeWire adapter negotiates its application-side PCM only when
        // the graph is active. Probe with empty buffers before accepting PCM.
        if (pw_stream_set_active(_stream, true) < 0)
            return Error::BackendFailure;
        timespec until{};
        if (pw_thread_loop_get_time(_monitor->loop, &until, 650'000'000) < 0)
            return Error::BackendFailure;
        while (!ready() || (_generation && !_quantumObserved))
        {
            if (_monitor->failed || !_monitor->contains(_targetNode, _targetSerial))
                return Error::Disconnected;
            if (_state == PW_STREAM_STATE_ERROR || pw_thread_loop_timed_wait_full(_monitor->loop, &until) < 0)
                return Error::Unsupported;
        }
        if (pw_stream_set_active(_stream, false) < 0)
            return Error::BackendFailure;
        _realtimeOpened = _generation != 0;
        return Error::None;
    }

public:
    Error submit(const std::int16_t* pcm, std::size_t frames) override
    {
        const LoopLock lock(_monitor->loop);
        if (_discarded)
            return Error::Busy;
        if (_generation)
        {
            if (_incompatibleQuantum)
                return Error::Unsupported;
            if (!validRealtimeBlock(pcm, frames, !_active, _front))
                return Error::InvalidArgument;
            if (!gateOpen() && !validRealtimeBlock(pcm, frames, true, _front))
                return Error::Busy;
        }
        if (available() == 0)
            return Error::QueueFull;
        const auto width = _endpoint.channels.size();
        const auto start = (_written * width) % _pcm.size();
        const auto count = frames * width;
        const auto first = std::min(count, _pcm.size() - start);
        std::copy_n(pcm, first, _pcm.begin() + start);
        std::copy_n(pcm + first, count - first, _pcm.begin());
        _written += frames;
        return Error::None;
    }

    Error setPaused(bool paused) override
    {
        const LoopLock lock(_monitor->loop);
        if (_discarded)
            return Error::Busy;
        if (!ready())
            return error();
        if (paused == !_active)
            return Error::None;
        if (_generation && paused)
            return Error::Unsupported;
        if (!paused)
        {
            _active = true;
            return pw_stream_set_active(_stream, true) < 0 ? Error::BackendFailure : Error::None;
        }
        updateProgress();
        _active = false;
        const bool canceledDrain = _draining;
        _draining = false;
        if (pw_stream_set_active(_stream, false) < 0 || pw_stream_flush(_stream, false) < 0)
            return Error::BackendFailure;
        // Keep every valid frame after the estimated device boundary for replay.
        _submitted = _consumed;
        _deviceWritten = 0;
        _devicePlayed = 0;
        _historyHead = 0;
        _historySize = 0;
        // PipeWire drain callbacks carry no request identity. Replace just this
        // stream on cancellation so an old callback can't finish a resumed drain.
        if (canceledDrain)
        {
            // A later drain on the replacement cannot certify samples from the retired stream.
            _uncertifiedStream = true;
            closeStream();
            return openLocked();
        }
        return Error::None;
    }

    Error stopWithEvidence() override
    {
        // Discard frames still owned by this producer. The native drain callback
        // is scoped to this stream and covers the frames already handed to PipeWire.
        {
            const LoopLock lock(_monitor->loop);
            if (!ready() || _failed)
                return error();
            if (_uncertifiedStream)
                return Error::Unsupported;
            if (_drained)
                return Error::None;
            _written = _submitted;
            _drainRequested = true;
            if (!_active)
            {
                _active = true;
                if (pw_stream_set_active(_stream, true) < 0)
                    return Error::BackendFailure;
            }
            const auto status = startDrain();
            if (status != Error::None)
                return status;
        }
        const auto deadline = Clock::now() + 200ms;
        while (Clock::now() < deadline)
        {
            {
                const LoopLock lock(_monitor->loop);
                if (!ready() || _failed)
                    return error();
                if (_drained)
                    return Error::None;
            }
            std::this_thread::sleep_for(2ms);
        }
        // Destroying a stalled stream stops further writes but supplies no drain evidence.
        return Error::Unsupported;
    }

    void setRealtimeGate(std::shared_ptr<const std::atomic_bool> gate) override
    {
        const LoopLock lock(_monitor->loop);
        _gate = std::move(gate);
    }

    AudioResult<RealtimeOutputStop> discardRealtime() override
    {
        std::optional<std::uint64_t> tail;
        {
            const LoopLock lock(_monitor->loop);
            if (!_generation || _discarded)
                return Error::Unsupported;
            _discarded = true;
            _written = _submitted;
            if (const auto timing = realtimeTiming())
                tail = timing->deviceFrame + timing->nativeTailFrames;
            else if (!_everSubmitted)
                tail = 0;
        }
        const auto status = stopWithEvidence();
        if (status != Error::None)
            return status;
        const LoopLock lock(_monitor->loop);
        if (_everSubmitted && (!_drainedDeviceFrame || _incompatibleQuantum))
            return Error::Unsupported;
        if (_drainedDeviceFrame)
            tail = std::max(tail.value_or(0), *_drainedDeviceFrame);
        if (!tail)
            return Error::Unsupported;
        return RealtimeOutputStop{_generation, *tail};
    }

    AudioResult<RealtimeOutputProgress> pollRealtime() override
    {
        const LoopLock lock(_monitor->loop);
        if (!_generation || _discarded || _incompatibleQuantum)
            return Error::Unsupported;
        if (!ready() || _failed)
            return error();
        auto progress = RealtimeOutputProgress{static_cast<unsigned>(_written - _submitted), available(), {}};
        if (!_active)
            return progress;
        if (const auto timing = realtimeTiming())
        {
            if (_lastTick && timing->ticks < *_lastTick)
                return Error::Unsupported;
            if (!_lastTick || timing->ticks > *_lastTick)
            {
                _clockAdvanced = _lastTick.has_value();
                _lastTick = timing->ticks;
                _ticksMovedAt = timing->observedNs;
            }
            if (!_clockAdvanced || timing->observedNs - _ticksMovedAt > realtimeClockTimeoutNs ||
                timing->deviceFrame < _lastDeviceFrame)
                return progress;
            updateConsumed(timing->nativeTailFrames);
            _lastDeviceFrame = timing->deviceFrame;
            progress.clock = RealtimeOutputClock{_generation, timing->observedNs, timing->deviceFrame,
                timing->deviceFrame + timing->nativeTailFrames + progress.queuedFrames, _consumed};
        }
        return progress;
    }

    Error drain() override
    {
        const LoopLock lock(_monitor->loop);
        _drainRequested = true;
        return startDrain();
    }

    AudioResult<OutputProgress> poll() override
    {
        const LoopLock lock(_monitor->loop);
        if (!ready() || _failed)
            return error();
        updateProgress();
        return OutputProgress{_consumed, available(), _drained};
    }

private:
    bool verifyFormat(const spa_pod* param) const
    {
        spa_audio_info_raw format{};
        if (!param || spa_format_audio_raw_parse(param, &format) < 0 ||
            format.format != SPA_AUDIO_FORMAT_S16 || format.rate != _endpoint.sampleRate ||
            format.channels != _endpoint.channels.size() || (format.flags & SPA_AUDIO_FLAG_UNPOSITIONED))
            return false;
        for (unsigned i = 0; i < format.channels; ++i)
        {
            const auto expected = std::ranges::find(channels, _endpoint.channels[i], &Channel::position);
            if (format.position[i] != expected->spa)
                return false;
        }
        return true;
    }

    bool ready() const
    {
        return !_monitor->failed && _monitor->contains(_targetNode, _targetSerial) && _formatVerified &&
            (_state == PW_STREAM_STATE_PAUSED || _state == PW_STREAM_STATE_STREAMING) &&
            _monitor->routes(pw_stream_get_node_id(_stream), _targetNode, _endpoint.channels);
    }

    Error error() const
    {
        return _monitor->failed || !_monitor->contains(_targetNode, _targetSerial)
            ? Error::Disconnected : Error::BackendFailure;
    }

    unsigned available() const
    {
        const auto capacity = _pcm.size() / _endpoint.channels.size();
        const auto space = capacity - (_written - _consumed);
        const auto pending = _written - _submitted;
        const auto limit = _generation ? realtimeQueueFrames : queueFrames;
        const auto queueSpace = limit - std::min<std::uint64_t>(pending, limit);
        return static_cast<unsigned>(std::min(space, queueSpace) / outputBlockFrames);
    }

    Error startDrain()
    {
        if (_drainRequested && !_draining && !_drained && _active && _submitted == _written)
        {
            _draining = true;
            if (pw_stream_flush(_stream, true) < 0)
                return Error::BackendFailure;
        }
        return Error::None;
    }

    std::optional<RealtimeTiming> realtimeTiming() const
    {
        if (_state != PW_STREAM_STATE_STREAMING)
            return {};
        pw_time time{};
        constexpr std::uint64_t nsPerSecond = 1'000'000'000;
        constexpr auto maxTailFrames = realtimeMaxTailNs * realtimeSampleRate / nsPerSecond;
        if (pw_stream_get_time_n(_stream, &time, sizeof(time)) < 0 ||
            time.now <= 0 || time.delay <= 0 || static_cast<std::uint64_t>(time.delay) > maxTailFrames ||
            !time.rate.num || static_cast<std::uint64_t>(time.rate.num) * realtimeSampleRate != time.rate.denom ||
            time.queued > maxTailFrames || time.buffered > maxTailFrames)
            return {};

        // PipeWire's sample timestamp uses CLOCK_MONOTONIC. Keep both the
        // timing estimate and its age in that clock before publishing it.
        timespec now{};
        if (clock_gettime(CLOCK_MONOTONIC, &now) != 0)
            return {};
        const auto ns = static_cast<std::uint64_t>(now.tv_sec) * nsPerSecond + static_cast<std::uint64_t>(now.tv_nsec);
        const auto sampled = static_cast<std::uint64_t>(time.now);
        if (ns < sampled || ns - sampled > realtimeClockTimeoutNs)
            return {};
        const auto elapsed = (ns - sampled) * realtimeSampleRate / nsPerSecond;
        const auto graphDelay = static_cast<std::uint64_t>(time.delay);
        const auto tail = time.queued + time.buffered + graphDelay - std::min(graphDelay, elapsed);
        if (tail > maxTailFrames ||
            time.ticks > std::numeric_limits<std::uint64_t>::max() - elapsed - tail - realtimeQueueFrames)
            return {};
        const auto observed = Clock::now();
        return RealtimeTiming{static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(observed.time_since_epoch()).count()),
            time.ticks, time.ticks + elapsed, tail};
    }

    void updateProgress()
    {
        if (!_active || _drained || _state != PW_STREAM_STATE_STREAMING || !_historySize)
            return;
        pw_time time{};
        if (pw_stream_get_time_n(_stream, &time, sizeof(time)) < 0 || !time.rate.denom)
            return;
        timespec now{};
        clock_gettime(CLOCK_MONOTONIC, &now);
        const auto ns = now.tv_sec * 1'000'000'000LL + now.tv_nsec;
        const auto elapsed = std::max(0.0, (ns - time.now) * 1.0e-9);
        const auto delay = static_cast<double>(time.delay) * time.rate.num / time.rate.denom;
        const auto graphFrames = static_cast<std::uint64_t>(std::max(0.0, delay - elapsed) * _endpoint.sampleRate);
        const auto queued = time.queued + time.buffered + graphFrames;
        updateConsumed(queued);
    }

    void updateConsumed(std::uint64_t queued)
    {
        _devicePlayed = std::max(_devicePlayed, _deviceWritten - std::min(_deviceWritten, queued));
        while (_historySize != 0)
        {
            const auto& segment = _history[_historyHead];
            if (segment.deviceStart >= _devicePlayed)
                break;
            const auto frames = _devicePlayed - segment.deviceStart;
            _consumed = segment.validStart + std::min(frames, segment.validFrames);
            if (frames < segment.frames)
                break;
            _historyHead = (_historyHead + 1) % historyEntries;
            --_historySize;
        }
    }

    void process()
    {
        auto* packet = pw_stream_dequeue_buffer(_stream);
        if (!packet)
            return;
        if (!packet->buffer->n_datas)
        {
            pw_stream_queue_buffer(_stream, packet);
            _failed = true;
            return;
        }
        auto& data = packet->buffer->datas[0];
        if (!data.data || !data.chunk)
        {
            pw_stream_queue_buffer(_stream, packet);
            _failed = true;
            return;
        }
        if (!_generation)
            updateProgress();
        const auto width = _endpoint.channels.size();
        const auto stride = width * sizeof(std::int16_t);
        const auto requested = packet->requested ? packet->requested : outputBlockFrames;
        const auto capacity = std::min<std::uint64_t>(data.maxsize / stride, requested);
        if (_generation && packet->requested)
        {
            const auto* clock = _graphPosition && _graphPosition->clock.duration ? &_graphPosition->clock : nullptr;
            const auto quantum = clock ? clock->duration : packet->requested;
            const bool graphChanged = _realtimeOpened && clock && _graphClockId && *_graphClockId != clock->id;
            const bool incompatible = quantum > realtimeMaxQuantumFrames || graphChanged ||
                packet->requested > realtimeQueueFrames || capacity != packet->requested;
            if (clock)
                _graphClockId = clock->id;
            if (!_realtimeOpened && _quantumObserved != !incompatible)
            {
                // The running graph may need a cycle to adopt our latency hint.
                _quantumObserved = !incompatible;
                pw_thread_loop_signal(_monitor->loop, false);
            }
            if (_realtimeOpened && incompatible && !_incompatibleQuantum)
            {
                _incompatibleQuantum = true;
                pw_thread_loop_signal(_monitor->loop, false);
            }
        }
        const bool routed = ready() && _active && !_failed &&
            (!_generation || (packet->requested && !_incompatibleQuantum));
        const auto valid = routed ? std::min(capacity, _written - _submitted) : 0;
        const auto frames = !_active || _draining ? 0 : routed && _drainRequested ? valid : capacity;
        auto* output = static_cast<std::int16_t*>(data.data);
        if (!_generation || gateOpen())
        {
            const auto offset = (_submitted * width) % _pcm.size();
            const auto first = std::min(valid * width, _pcm.size() - offset);
            std::copy_n(_pcm.data() + offset, first, output);
            std::copy_n(_pcm.data(), valid * width - first, output + first);
            std::fill_n(output + valid * width, (frames - valid) * width, std::int16_t{0});
        }
        else
            std::fill_n(output, frames * width, std::int16_t{0});

        if (frames)
        {
            const bool record = !_generation || valid != 0;
            if (record && _historySize == historyEntries)
                _failed = true;
            else
            {
                if (record)
                {
                    const auto tail = (_historyHead + _historySize) % historyEntries;
                    _history[tail] = {_deviceWritten, _submitted, frames, valid};
                    ++_historySize;
                }
                _deviceWritten += frames;
                _submitted += valid;
                _everSubmitted |= valid != 0;
            }
        }
        data.chunk->offset = 0;
        data.chunk->size = static_cast<std::uint32_t>(frames * stride);
        data.chunk->stride = static_cast<std::int32_t>(stride);
        packet->size = frames;
        if (_generation && !gateOpen())
            std::fill_n(output, frames * width, std::int16_t{0});
        if (pw_stream_queue_buffer(_stream, packet) < 0 || startDrain() != Error::None)
            _failed = true;
    }

    std::shared_ptr<Monitor> _monitor;
    DirectEndpoint _endpoint;
    unsigned _targetNode;
    std::uint64_t _targetSerial;
    const std::uint64_t _generation;
    std::shared_ptr<const std::atomic_bool> _gate;
    std::array<unsigned, 2> _front{};
    std::vector<std::int16_t> _pcm;
    std::array<Segment, historyEntries> _history{};
    std::size_t _historyHead = 0, _historySize = 0;
    std::uint64_t _written = 0, _submitted = 0, _consumed = 0;
    std::uint64_t _deviceWritten = 0, _devicePlayed = 0;
    std::uint64_t _lastDeviceFrame = 0;
    std::optional<std::uint64_t> _lastTick;
    std::uint64_t _ticksMovedAt = 0;
    std::optional<std::uint64_t> _drainedDeviceFrame;
    pw_stream* _stream = nullptr;
    spa_io_position* _graphPosition = nullptr;
    std::optional<unsigned> _graphClockId;
    spa_hook _listener{};
    pw_stream_state _state = PW_STREAM_STATE_CONNECTING;
    bool _formatVerified = false, _active = false, _failed = false;
    bool _drainRequested = false, _draining = false, _drained = false;
    bool _uncertifiedStream = false;
    bool _discarded = false, _everSubmitted = false;
    bool _realtimeOpened = false, _quantumObserved = false, _incompatibleQuantum = false, _clockAdvanced = false;
};

} // namespace

AudioResult<std::vector<DirectEndpoint>> enumeratePlatformEndpoints()
{
    const auto server = monitor();
    if (!server)
        return Error::Disconnected;
    std::vector<DirectEndpoint> endpoints;
    {
        const LoopLock lock(server->loop);
        if (server->failed)
            return Error::Disconnected;
        endpoints = server->endpoints();
    }
    for (auto& endpoint : endpoints)
    {
        if (!endpoint.mainDeviceName.empty() || endpoint.usbPath.empty())
            continue;
        endpoint.mainDeviceName = openAlName(endpoint.deviceSelector);
        if (endpoint.mainDeviceName.empty())
            continue;
        const LoopLock lock(server->loop);
        server->rememberMainName(endpoint.key, endpoint.mainDeviceName);
    }
    return endpoints;
}

namespace {

AudioResult<std::unique_ptr<OutputStream>> openOutput(const DirectEndpoint& endpoint, bool realtime)
{
    if (realtime && (endpoint.sampleRate != realtimeSampleRate ||
        !std::ranges::is_permutation(endpoint.channels, realtimeChannels)))
        return Error::Unsupported;
    const auto server = monitor();
    if (!server)
        return Error::Disconnected;
    std::optional<std::pair<unsigned, std::uint64_t>> target;
    {
        const LoopLock lock(server->loop);
        target = server->find(endpoint.key);
        if (server->failed || !target)
            return Error::Disconnected;
        const auto endpoints = server->endpoints();
        const auto found = std::ranges::find(endpoints, endpoint.key, &DirectEndpoint::key);
        if (found == endpoints.end() || found->sampleRate != endpoint.sampleRate ||
            found->channels != endpoint.channels || endpoint.channels.empty() ||
            !endpoint.sampleRate || endpoint.sampleRate > 384000)
            return Error::Unsupported;
    }
    auto stream = std::make_unique<PipeWireOutput>(server, endpoint, target->first, target->second, realtime);
    if (const auto error = stream->open(); error != Error::None)
        return error;
    return std::unique_ptr<OutputStream>(std::move(stream));
}

} // namespace

AudioResult<std::unique_ptr<OutputStream>> openPlatformOutput(const DirectEndpoint& endpoint)
{
    return openOutput(endpoint, false);
}

AudioResult<std::unique_ptr<OutputStream>> openPlatformRealtimeOutput(const DirectEndpoint& endpoint)
{
    return openOutput(endpoint, true);
}

void shutdownPlatformOutput() noexcept
{
    std::shared_ptr<Monitor> retired;
    {
        auto& state = monitorSlot();
        const std::lock_guard lock(state.mutex);
        retired = std::move(state.current);
        state.retryAt = {};
    }
}

} // namespace cc::audio::detail
