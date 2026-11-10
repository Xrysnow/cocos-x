/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "scripting/lua-bindings/manual/spine/cclua_spine_manual.hpp"
#include "scripting/lua-bindings/auto/cclua_spine_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "spine/spine-cocos2dx.h"
#include <cmath>
#include <limits>
#include <utility>

namespace spine_binding
{
using Node = spine::SkeletonAnimation;
using Snapshot = cocos2d::ValueMap;
using Callback = std::function<void(const Snapshot&)>;
struct BoneSnapshot { bool present = false; Snapshot fields; };
struct Channel { spine::EventType value = spine::EventType_Start; };
struct Track { int value = 0; };

template<bool Checked>
bool readChannel(lua_State* L, int index, Channel* out)
{
    int value = 0;
    // A malformed channel must never silently select/clear START in unchecked builds.
    if (!lua::binding_read<int>::template F<true>(L, index, &value)
        || value < spine::EventType_Start || value > spine::EventType_Event)
        return false;
    out->value = static_cast<spine::EventType>(value);
    return true;
}

std::string copyString(const spine::String& value)
{
    return value.buffer() ? std::string(value.buffer(), value.length()) : std::string();
}

Snapshot eventSnapshot(spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
    static const char* names[] = {"start", "interrupt", "end", "complete", "dispose", "event"};
    auto* animation = entry ? entry->getAnimation() : nullptr;
    int loops = 0;
    const double end = entry ? entry->getAnimationEnd() : 0;
    if (end > 0 && std::isfinite(end)) {
        const double count = std::floor(double(entry->getTrackTime()) / end);
        if (std::isfinite(count) && count >= std::numeric_limits<int>::min()
            && count <= std::numeric_limits<int>::max()) loops = static_cast<int>(count);
    }
    Snapshot result{
        {"type", cocos2d::Value(names[static_cast<int>(type)])},
        {"trackIndex", cocos2d::Value(entry ? entry->getTrackIndex() : 0)},
        {"animation", cocos2d::Value(animation ? copyString(animation->getName()) : std::string())},
        {"loopCount", cocos2d::Value(loops)}
    };
    if (event) {
        Snapshot data{
            {"name", cocos2d::Value(copyString(event->getData().getName()))},
            {"intValue", cocos2d::Value(event->getIntValue())},
            {"floatValue", cocos2d::Value(event->getFloatValue())},
            {"stringValue", cocos2d::Value(copyString(event->getStringValue()))}
        };
        result.emplace("eventData", cocos2d::Value(std::move(data)));
    }
    return result;
}

void setListener(Node* self, Channel channel, Callback callback)
{
    if (channel.value == spine::EventType_Event) {
        spine::EventListener listener;
        if (callback) listener = [callback = std::move(callback)](spine::TrackEntry* entry, spine::Event* event) {
            const auto snapshot = eventSnapshot(spine::EventType_Event, entry, event);
            callback(snapshot);
        };
        self->setEventListener(listener);
        return;
    }
    spine::StartListener listener;
    if (callback) listener = [callback = std::move(callback), type = channel.value](spine::TrackEntry* entry) {
        const auto snapshot = eventSnapshot(type, entry, nullptr);
        callback(snapshot);
    };
    switch (channel.value) {
    case spine::EventType_Start: self->setStartListener(listener); break;
    case spine::EventType_Interrupt: self->setInterruptListener(listener); break;
    case spine::EventType_End: self->setEndListener(listener); break;
    case spine::EventType_Complete: self->setCompleteListener(listener); break;
    case spine::EventType_Dispose: self->setDisposeListener(listener); break;
    default: break; // Channel is validated before any callback reference is acquired.
    }
}

Node* create(const std::string& skeleton, const std::string& atlas, float scale)
{
    if (cocos2d::FileUtils::getInstance()->getFileExtension(skeleton) == ".json")
        return Node::createWithJsonFile(skeleton, atlas, scale);
    return Node::createWithBinaryFile(skeleton, atlas, scale);
}
}

namespace lua
{
template<> struct to_lua<spine_binding::BoneSnapshot> {
    static void F(lua_State* L, const spine_binding::BoneSnapshot& value) {
        if (value.present) native_to_luaval(L, value.fields);
        else lua_pushnil(L);
    }
};
template<> struct binding_argument<spine_binding::Channel> {
    spine_binding::Channel value;
    template<bool Checked> bool read(lua_State* L, int index) {
        return spine_binding::readChannel<Checked>(L, index, &value);
    }
    spine_binding::Channel get() { return value; }
};
template<> struct binding_argument<spine_binding::Track> {
    spine_binding::Track value;
    template<bool Checked> bool read(lua_State* L, int index) {
        // Native AnimationState expands a size_t index: a negative int would allocate
        // an enormous track vector. This precondition is required in both modes.
        return binding_read<int>::template F<true>(L, index, &value.value) && value.value >= 0;
    }
    spine_binding::Track get() { return value; }
};
}

static int spine_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:create");
    const auto withoutScale = [](const std::string& skeleton, const std::string& atlas) {
        return spine_binding::create(skeleton, atlas, 1);
    };
    LUA_TRY_INVOKE_R(3, &spine_binding::create);
    LUA_TRY_INVOKE_R(2, withoutScale);
    LUA_SINVOKE_FOOTER("2,3");
}

static int spine_findBone(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:findBone");
    const auto find = [](spine_binding::Node* self, const std::string& name) {
        spine_binding::BoneSnapshot result;
        if (auto* bone = self->findBone(name)) {
            result.present = true;
            result.fields = {
                {"x", cocos2d::Value(bone->getX())}, {"y", cocos2d::Value(bone->getY())},
                {"rotation", cocos2d::Value(bone->getRotation())},
                {"scaleX", cocos2d::Value(bone->getScaleX())}, {"scaleY", cocos2d::Value(bone->getScaleY())},
                {"worldX", cocos2d::Value(bone->getWorldX())}, {"worldY", cocos2d::Value(bone->getWorldY())}
            };
        }
        return result;
    };
    LUA_TRY_INVOKE_R(1, find);
    LUA_INVOKE_FOOTER("1");
}

static int spine_setAnimation(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setAnimation");
    const auto command = [](spine_binding::Node* self, spine_binding::Track track, const std::string& name, bool loop) {
        self->setAnimation(track.value, name, loop);
    };
    LUA_TRY_INVOKE(3, command);
    LUA_INVOKE_FOOTER("3");
}

static int spine_addAnimation(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:addAnimation");
    const auto command = [](spine_binding::Node* self, spine_binding::Track track, const std::string& name, bool loop, float delay) {
        self->addAnimation(track.value, name, loop, delay);
    };
    const auto withoutDelay = [](spine_binding::Node* self, spine_binding::Track track, const std::string& name, bool loop) {
        self->addAnimation(track.value, name, loop);
    };
    LUA_TRY_INVOKE(4, command);
    LUA_TRY_INVOKE(3, withoutDelay);
    LUA_INVOKE_FOOTER("3,4");
}

static int spine_setEmptyAnimation(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setEmptyAnimation");
    const auto command = [](spine_binding::Node* self, spine_binding::Track track, float mix) { self->setEmptyAnimation(track.value, mix); };
    LUA_TRY_INVOKE(2, command);
    LUA_INVOKE_FOOTER("2");
}

static int spine_addEmptyAnimation(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:addEmptyAnimation");
    const auto command = [](spine_binding::Node* self, spine_binding::Track track, float mix, float delay) {
        self->addEmptyAnimation(track.value, mix, delay);
    };
    const auto withoutDelay = [](spine_binding::Node* self, spine_binding::Track track, float mix) { self->addEmptyAnimation(track.value, mix); };
    LUA_TRY_INVOKE(3, command);
    LUA_TRY_INVOKE(2, withoutDelay);
    LUA_INVOKE_FOOTER("2,3");
}

static int spine_registerHandler(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:registerSpineEventHandler");
    // Validate the channel before conversion can acquire a Lua callback reference.
    spine_binding::Channel channel;
    if (argc == 2 && !spine_binding::readChannel<CC_LUA_BINDING_CHECKS>(lua_S, 3, &channel)) {
        arg_cur = 2;
    } else {
        const auto install = [](spine_binding::Node* self, spine_binding::Callback callback, spine_binding::Channel channel) {
            spine_binding::setListener(self, channel, std::move(callback));
        };
        LUA_TRY_INVOKE(2, install);
    }
    LUA_INVOKE_FOOTER("2");
}

static int spine_unregisterHandler(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:unregisterSpineEventHandler");
    const auto clear = [](spine_binding::Node* self, spine_binding::Channel channel) {
        spine_binding::setListener(self, channel, nullptr);
    };
    LUA_TRY_INVOKE(1, clear);
    LUA_INVOKE_FOOTER("1");
}

// These adapters select a native slot and materialize a snapshot; invocation,
// conversion, callback references, diagnostics and self returns stay shared.
#define SPINE_EVENT_SETTER(Name, Type) \
static int spine_##Name(lua_State* lua_S) \
{ \
    LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:" #Name); \
    const auto install = [](spine_binding::Node* self, spine_binding::Callback callback) { \
        spine_binding::setListener(self, {spine::Type}, std::move(callback)); \
    }; \
    LUA_TRY_INVOKE(1, install); \
    LUA_INVOKE_FOOTER("1"); \
}
SPINE_EVENT_SETTER(setStartListener, EventType_Start)
SPINE_EVENT_SETTER(setInterruptListener, EventType_Interrupt)
SPINE_EVENT_SETTER(setEndListener, EventType_End)
SPINE_EVENT_SETTER(setCompleteListener, EventType_Complete)
SPINE_EVENT_SETTER(setDisposeListener, EventType_Dispose)
SPINE_EVENT_SETTER(setEventListener, EventType_Event)
#undef SPINE_EVENT_SETTER

int register_all_cc_spine_manual(lua_State* L)
{
    luaL_getmetatable(L, "sp.SkeletonAnimation");
    tolua_function(L, "create", spine_create);
    tolua_function(L, "findBone", spine_findBone);
    tolua_function(L, "setAnimation", spine_setAnimation);
    tolua_function(L, "addAnimation", spine_addAnimation);
    tolua_function(L, "setEmptyAnimation", spine_setEmptyAnimation);
    tolua_function(L, "addEmptyAnimation", spine_addEmptyAnimation);
    tolua_function(L, "registerSpineEventHandler", spine_registerHandler);
    tolua_function(L, "unregisterSpineEventHandler", spine_unregisterHandler);
    tolua_function(L, "setStartListener", spine_setStartListener);
    tolua_function(L, "setInterruptListener", spine_setInterruptListener);
    tolua_function(L, "setEndListener", spine_setEndListener);
    tolua_function(L, "setCompleteListener", spine_setCompleteListener);
    tolua_function(L, "setDisposeListener", spine_setDisposeListener);
    tolua_function(L, "setEventListener", spine_setEventListener);
    lua_pop(L, 1);
    return 0;
}

int register_spine_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1)) {
        register_all_cc_spine(L);
        register_all_cc_spine_manual(L);
    }
    lua_pop(L, 1);
    return 1;
}
