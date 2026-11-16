#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>

namespace cocos2d { namespace ui { namespace detail {

// The owner, lifecycle operations and task delivery belong to the cocos thread.
// Producers may post from any thread. A task owns its callback snapshot, never
// the Ref owner; an instance-specific epoch prevents delivery after exit/reentry.
template<class Owner, class Event>
class VideoPlayerEventQueue : public std::enable_shared_from_this<VideoPlayerEventQueue<Owner, Event>>
{
public:
    using Callback = std::function<void(Owner*, Event)>;
    using Task = std::function<void()>;
    using Delivery = void (*)(Owner*, const Callback&, Event);

    static std::shared_ptr<VideoPlayerEventQueue> create(Owner* owner, Delivery delivery)
    {
        return std::shared_ptr<VideoPlayerEventQueue>(new VideoPlayerEventQueue(owner, delivery));
    }

    void setCallback(Callback callback)
    {
        // Destroy the previous callable outside the lock: its release may reenter.
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (!_closed) _callback.swap(callback);
        }
    }

    Callback getCallback() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _callback;
    }

    Task makeTask(Event event)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return makeTaskLocked(event);
    }

    // The poster must enqueue without executing the task synchronously. Holding
    // the lock through submission makes shutdown a barrier for new submissions.
    template<class Poster>
    void post(Event event, Poster&& poster)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto task = makeTaskLocked(event);
        if (task) poster(std::move(task));
    }

    void activate(Owner* owner)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_closed) { _owner = owner; ++_epoch; }
    }

    void invalidate()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        ++_epoch;
    }

    void deactivate()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _owner = nullptr;
        ++_epoch;
    }

    void shutdown()
    {
        Callback previous;
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _closed = true;
            _owner = nullptr;
            ++_epoch;
            previous.swap(_callback);
        }
    }

private:
    VideoPlayerEventQueue(Owner* owner, Delivery delivery) : _owner(owner), _delivery(delivery) {}

    Task makeTaskLocked(Event event)
    {
        if (_closed || !_owner) return {};
        auto state = this->shared_from_this();
        const auto epoch = _epoch;
        return [state, epoch, event, callback = _callback] {
            Owner* owner;
            {
                std::lock_guard<std::mutex> lock(state->_mutex);
                if (state->_closed || !state->_owner || state->_epoch != epoch) return;
                owner = state->_owner;
            }
            // Lifecycle and delivery are serialized by the cocos thread. The
            // production delivery anchors the Ref across reentrant callbacks.
            state->_delivery(owner, callback, event);
        };
    }

    mutable std::mutex _mutex;
    Owner* _owner;
    Delivery _delivery;
    Callback _callback;
    uint64_t _epoch = 0;
    bool _closed = false;
};

}}} // namespace cocos2d::ui::detail
