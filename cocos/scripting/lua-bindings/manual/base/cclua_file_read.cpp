#include "scripting/lua-bindings/manual/base/cclua_file_read.hpp"
#include "io/core/FileStream.h"
#include "platform/FileUtils.h"

using namespace cc;
using namespace cc::luaio;

namespace
{
FileUtils& checkFileUtils(lua_State* L)
{
    tolua_Error error{};
    if (!tolua_isusertype(L, 1, "cc.FileUtils", 0, &error))
        luaL_argerror(L, 1, "cc.FileUtils expected");
    auto self = static_cast<FileUtils*>(tolua_tousertype(L, 1, nullptr));
    if (!self)
        luaL_argerror(L, 1, "cc.FileUtils expected");
    return *self;
}

AdapterId checkAdapterId(lua_State* L, int index)
{
    luaL_checktype(L, index, LUA_TSTRING);
    const auto input = checkString(L, index);
    AdapterId id = 0;
    const auto parsed = std::from_chars(input.data(), input.data() + input.size(), id);
    if (parsed.ec != std::errc{} || parsed.ptr != input.data() + input.size())
        luaL_argerror(L, index, "adapter ID must be a decimal string");
    return id;
}

int pushHit(lua_State* L, io::Result<FileHit> hit)
{
    if (!hit)
        return pushError(L, hit.error);
    pushObject<FileHit>(L, "cc.FileHit", std::move(hit.value));
    return 1;
}

int findFile(lua_State* L)
{
    return pushHit(L, checkFileUtils(L).findFile(checkString(L, 2)));
}

int findFileIn(lua_State* L)
{
    return pushHit(L, checkFileUtils(L).findFileIn(checkAdapterId(L, 2), checkString(L, 3)));
}

int findPlatformFile(lua_State* L)
{
    return pushHit(L, checkFileUtils(L).findPlatformFile(checkString(L, 2)));
}

int findSibling(lua_State* L)
{
    return pushHit(L, checkFileUtils(L).findSibling(checkFileHit(L, 2), checkString(L, 3)));
}

int findAllFiles(lua_State* L)
{
    auto hits = checkFileUtils(L).findAllFiles(checkString(L, 2));
    if (!hits)
        return pushError(L, hits.error);
    lua_createtable(L, static_cast<int>(hits.value.size()), 0);
    int index = 1;
    for (auto& hit : hits.value)
    {
        pushObject<FileHit>(L, "cc.FileHit", std::move(hit));
        lua_rawseti(L, -2, index++);
    }
    return 1;
}

int fileHitField(lua_State* L)
{
    const auto& hit = checkFileHit(L, 1);
    const auto field = checkString(L, 2);
    if (field == "adapterId")
        pushDecimal(L, hit.adapterId());
    else if (field == "kind")
        pushString(L, hit.kind());
    else if (field == "name")
        pushString(L, hit.name());
    else if (field == "priority")
        lua_pushnumber(L, hit.priority());
    else if (field == "entryKey")
        pushString(L, hit.entry().entryKey);
    else if (field == "source")
        pushString(L, hit.entry().source);
    else if (field == "root" && hit.entry().rootIndex)
        pushString(L, hit.root());
    else if (field == "nativePath" && hit.entry().nativePath)
        pushString(L, *hit.entry().nativePath);
    else if (field == "sizeHint" && hit.entry().sizeHint)
        pushExact(L, *hit.entry().sizeHint);
    else
        lua_pushnil(L);
    return 1;
}

int readFile(lua_State* L)
{
    auto file = checkFileUtils(L).openRead(checkFileHit(L, 2));
    if (!file)
        return pushError(L, file.error);
    auto stream = io::FileStream::fromBackend(std::move(file.value));
    if (!stream)
        return pushError(L, stream.error);
    const auto bytes = stream.value->readAll(std::numeric_limits<size_t>::max());
    if (!bytes)
        return pushError(L, bytes.error);
    const auto closed = stream.value->close();
    if (!closed)
        return pushError(L, closed.error);
    const auto& data = bytes.value;
    pushString(L, data.empty() ? std::string_view{} :
        std::string_view(reinterpret_cast<const char*>(data.data()), data.size()));
    return 1;
}

int fileSize(lua_State* L)
{
    const auto size = checkFileUtils(L).fileSize(checkFileHit(L, 2));
    if (!size)
        return pushError(L, size.error);
    pushExact(L, size.value);
    return 1;
}

int getReadAdapters(lua_State* L)
{
    const auto adapters = checkFileUtils(L).getReadAdapters();
    lua_createtable(L, static_cast<int>(adapters.size()), 0);
    int index = 1;
    for (const auto& adapter : adapters)
    {
        lua_createtable(L, 0, 5);
        pushDecimal(L, adapter.id);
        lua_setfield(L, -2, "id");
        setString(L, "name", adapter.name);
        setString(L, "kind", adapter.kind);
        setNumber(L, "priority", adapter.priority);
        lua_createtable(L, static_cast<int>(adapter.roots.size()), 0);
        int rootIndex = 1;
        for (const auto& root : adapter.roots)
        {
            pushString(L, root);
            lua_rawseti(L, -2, rootIndex++);
        }
        lua_setfield(L, -2, "roots");
        lua_rawseti(L, -2, index++);
    }
    return 1;
}

int setAdapterPriority(lua_State* L)
{
    return pushStatus(L, checkFileUtils(L).setAdapterPriority(checkAdapterId(L, 2),
        static_cast<float>(luaL_checknumber(L, 3))));
}

int setAdapterSearchPaths(lua_State* L)
{
    auto& fileUtils = checkFileUtils(L);
    const auto id = checkAdapterId(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    const auto count = lua_objlen(L, 3);
    std::vector<std::string> roots;
    roots.reserve(count);
    for (size_t index = 1; index <= count; ++index)
    {
        lua_rawgeti(L, 3, static_cast<int>(index));
        if (lua_type(L, -1) != LUA_TSTRING)
            return pushError(L, {io::ErrorCode::InvalidArgument});
        roots.emplace_back(checkString(L, -1));
        lua_pop(L, 1);
    }
    return pushStatus(L, fileUtils.setAdapterSearchPaths(id, roots));
}

int addAdapterSearchPath(lua_State* L)
{
    return pushStatus(L, checkFileUtils(L).addAdapterSearchPath(checkAdapterId(L, 2),
        std::string(checkString(L, 3)), lua_toboolean(L, 4) != 0));
}
}

void register_cc_file_read_manual(lua_State* L)
{
    luaL_newmetatable(L, "cc.FileHit");
    lua_pushcfunction(L, destroyObject<FileHit>);
    lua_setfield(L, -2, "__gc");
    lua_pushcfunction(L, fileHitField);
    lua_setfield(L, -2, "__index");
    lua_pushliteral(L, "cc.FileHit");
    lua_setfield(L, -2, "__metatable");
    lua_pop(L, 1);

    luaL_getmetatable(L, "cc.FileUtils");
    const luaL_Reg methods[] = {
        {"findFile", findFile}, {"findFileIn", findFileIn}, {"findAllFiles", findAllFiles},
        {"findPlatformFile", findPlatformFile}, {"findSibling", findSibling},
        {"readFile", readFile}, {"fileSize", fileSize},
        {"getReadAdapters", getReadAdapters}, {"setAdapterPriority", setAdapterPriority},
        {"setAdapterSearchPaths", setAdapterSearchPaths}, {"addAdapterSearchPath", addAdapterSearchPath},
        {nullptr, nullptr}
    };
    luaL_register(L, nullptr, methods);
    lua_pop(L, 1);
}
