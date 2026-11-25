#include "lua_conversion/lua_conversion.hpp"
#include "2d/Label.h"
#include "2d/font/FontRendering.h"
#include <cmath>
#include <limits>
#include <optional>

namespace
{
template<class Integer>
bool readNonnegativeInteger(lua_State* L, int index, Integer& value)
{
    if (lua_type(L, index) != LUA_TNUMBER)
        return false;
    const auto number = lua_tonumber(L, index);
    const auto upperBound = std::ldexp(lua_Number{1}, std::numeric_limits<Integer>::digits);
    if (!(number >= 0 && number < upperBound) || std::trunc(number) != number)
        return false;
    value = static_cast<Integer>(number);
    return true;
}

template<class Integer>
bool readConfigField(lua_State* L, const char* name, Integer& value)
{
    lua_pushstring(L, name);
    lua_rawget(L, 2);
    const bool valid = lua_isnil(L, -1) || readNonnegativeInteger(L, -1, value);
    lua_pop(L, 1);
    return valid;
}

int fontGetInstance(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_settop(L, 1);
    return 1;
}

int fontInspect(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.FontRendering", "cc.FontRendering:inspectFont");
    LUA_TRY_INVOKE_R(1, [](std::string_view name) { return cc::FontRendering::getInstance().inspectFont(name); });
    LUA_SINVOKE_FOOTER("1");
}

int fontGetConfig(lua_State* L)
{
    const auto config = cc::FontRendering::getInstance().getConfig();
    lua_createtable(L, 0, 6);
    lua::native_to_luaval_field(L, -1, "maxPages", config.maxPages);
    lua::native_to_luaval_field(L, -1, "glyphIdleTimeMs", config.glyphIdleTime.count());
    lua::native_to_luaval_field(L, -1, "workerCount", config.workerCount);
    lua::native_to_luaval_field(L, -1, "maxPendingGlyphs", config.maxPendingGlyphs);
    lua::native_to_luaval_field(L, -1, "maxStagingBytes", config.maxStagingBytes);
    lua::native_to_luaval_field(L, -1, "uploadBytesPerFrame", config.uploadBytesPerFrame);
    return 1;
}

int fontConfigure(lua_State* L)
{
    luaL_checktype(L, 2, LUA_TTABLE);
    auto& rendering = cc::FontRendering::getInstance();
    auto config = rendering.getConfig();
    auto idleTimeMs = config.glyphIdleTime.count();
    auto status = cc::GlyphStatus::InvalidInput;
    if (readConfigField(L, "maxPages", config.maxPages) && readConfigField(L, "glyphIdleTimeMs", idleTimeMs) &&
        readConfigField(L, "workerCount", config.workerCount) && readConfigField(L, "maxPendingGlyphs", config.maxPendingGlyphs) &&
        readConfigField(L, "maxStagingBytes", config.maxStagingBytes) && readConfigField(L, "uploadBytesPerFrame", config.uploadBytesPerFrame))
    {
        config.glyphIdleTime = std::chrono::milliseconds(idleTimeMs);
        status = rendering.configure(config);
    }
    lua::native_to_luaval(L, status);
    return 1;
}

int fontSetWorkerCount(lua_State* L)
{
    uint32_t count;
    const auto status = readNonnegativeInteger(L, 2, count)
        ? cc::FontRendering::getInstance().setWorkerCount(count) : cc::GlyphStatus::InvalidInput;
    lua::native_to_luaval(L, status);
    return 1;
}

int fontGetStats(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.FontRendering", "cc.FontRendering:getStats");
    if (lua_gettop(lua_S) == 1)
    {
        const auto& fonts = cc::FontRendering::getInstance();
        lua::native_to_luaval(lua_S, fonts.getStats());
        const auto uploads = fonts.getUploadStats();
        lua::native_to_luaval_field(lua_S, -1, "uploadedGlyphs", uploads.glyphs);
        lua::native_to_luaval_field(lua_S, -1, "uploadedBytes", uploads.bytes);
        return 1;
    }
    LUA_SINVOKE_FOOTER("0");
}

int fontTrim(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.FontRendering", "cc.FontRendering:trim");
    LUA_TRY_INVOKE_R(0, [] { cc::FontRendering::getInstance().trim(); });
    LUA_SINVOKE_FOOTER("0");
}

int labelGetFontMetrics(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Label", "cc.Label:getFontMetrics");
    LUA_TRY_INVOKE_R(0, [](const cc::Label& label) -> std::optional<cc::FontMetrics> {
        cc::FontMetrics metrics;
        if (label.getFontMetrics(metrics))
            return metrics;
        return std::nullopt;
    });
    LUA_INVOKE_FOOTER("0");
}

int labelMeasureText(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Label", "cc.Label:measureText");
    LUA_TRY_INVOKE_R(1, [](const cc::Label& label, std::string_view text) -> std::optional<cc::Size> {
        cc::Size size;
        if (label.measureText(text, size))
            return size;
        return std::nullopt;
    });
    LUA_INVOKE_FOOTER("1");
}
}

void register_cc_font_manual(lua_State* L)
{
    luaL_getmetatable(L, "cc.Label");
    tolua_function(L, "getFontMetrics", labelGetFontMetrics);
    tolua_function(L, "measureText", labelMeasureText);
    lua_pop(L, 1);

    // Resolving the service per call keeps Lua references valid across a Director reset.
    lua_getglobal(L, "cc");
    lua_newtable(L);
    const luaL_Reg functions[] = {
        {"getInstance", fontGetInstance}, {"inspectFont", fontInspect}, {"getConfig", fontGetConfig},
        {"configure", fontConfigure}, {"setWorkerCount", fontSetWorkerCount}, {"getStats", fontGetStats},
        {"trim", fontTrim}, {nullptr, nullptr}
    };
    luaL_register(L, nullptr, functions);
    lua_setfield(L, -2, "FontRendering");
    lua_pop(L, 1);
}
