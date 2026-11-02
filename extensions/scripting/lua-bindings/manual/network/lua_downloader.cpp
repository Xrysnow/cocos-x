/****************************************************************************
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
#include "lua_downloader.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"

#include "network/CCDownloader.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include <atomic>
#include <iostream>

#include <unordered_map>
#include <string>
#include <sstream>

#include "scripting/lua-bindings/manual/CCLuaEngine.h"

USING_NS_CC;
using namespace cocos2d::network;

struct LuaDownloaderState
{
    std::unique_ptr<Downloader> downloader;
    Scheduler* scheduler;
    std::atomic_bool alive{true};

    explicit LuaDownloaderState(std::unique_ptr<Downloader> value)
        : downloader(std::move(value)), scheduler(Director::getInstance()->getScheduler())
    {
        scheduler->retain();
    }
    ~LuaDownloaderState()
    {
        downloader.reset();
        scheduler->release();
    }
};

// A nullable heap holder makes __gc idempotent without leaving a constructed
// native object in Lua-owned memory after it has been finalized.
using LuaDownloaderHandle = std::shared_ptr<LuaDownloaderState>*;

static LuaDownloaderHandle* checkDownloaderHandle(lua_State* L)
{
    auto handle = static_cast<LuaDownloaderHandle*>(luaL_checkudata(L, 1, "cc.Downloader"));
    luaL_argcheck(L, handle && *handle, 1, "Downloader has been finalized");
    return handle;
}

struct LuaDownloadSnapshot
{
    std::string identifier;
    std::string requestURL;
    std::string storagePath;
    int64_t bytesReceived;
    int64_t totalBytesReceived;
    int64_t totalBytesExpected;

    explicit LuaDownloadSnapshot(const DownloadTask& task)
        : identifier(task.identifier), requestURL(task.requestURL), storagePath(task.storagePath),
          bytesReceived(task.progressInfo.bytesReceived), totalBytesReceived(task.progressInfo.totalBytesReceived),
          totalBytesExpected(task.progressInfo.totalBytesExpected) {}
};

static int get_field_int(lua_State* L, const char* field, int def)
{
    int ret = def;
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1))
    {
        // luaL_error(L, "get_field_int: field '%s' no exists.", field);
        lua_pop(L, 1);
        return ret;
    }
    ret = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

static std::string get_field_string(lua_State* L, const char* field, const char* def)
{
    std::string ret = def;
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1))
    {
        // luaL_error(L, "get_field_string: field '%s' no exists.", field);
        lua_pop(L, 1);
        return ret;
    }
    ret = std::string(lua_tostring(L, -1));
    lua_pop(L, 1);
    return ret;
}

static void set_field_string(lua_State* L, const char* field, const char* value)
{
    lua_pushstring(L, field);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}

static Downloader* checkDownloader(lua_State* L)
{
    return (**checkDownloaderHandle(L))->downloader.get();
}

static int lua_download_task_cancel(lua_State* L)
{
    auto weak = static_cast<std::weak_ptr<DownloadTask>**>(lua_touserdata(L, lua_upvalueindex(1)));
    auto task = *weak ? (*weak)->lock() : std::shared_ptr<DownloadTask>{};
    if (task)
        task->cancel();
    lua_pushboolean(L, task != nullptr);
    return 1;
}

static int lua_download_task_cleanup(lua_State* L)
{
    auto weak = static_cast<std::weak_ptr<DownloadTask>**>(luaL_checkudata(L, 1, "cc.DownloadTaskCancellation"));
    delete *weak;
    *weak = nullptr;
    return 0;
}

static void pushTaskTable(lua_State* L, const LuaDownloadSnapshot& task)
{
    lua_newtable(L);
    set_field_string(L, "identifier", task.identifier.c_str());
    set_field_string(L, "requestURL", task.requestURL.c_str());
    set_field_string(L, "storagePath", task.storagePath.c_str());
}

static void pushTaskTable(lua_State* L, const std::shared_ptr<DownloadTask>& task)
{
    pushTaskTable(L, LuaDownloadSnapshot(*task));
    auto weak = static_cast<std::weak_ptr<DownloadTask>**>(lua_newuserdata(L, sizeof(std::weak_ptr<DownloadTask>*)));
    *weak = new std::weak_ptr<DownloadTask>(task);
    luaL_getmetatable(L, "cc.DownloadTaskCancellation");
    lua_setmetatable(L, -2);
    lua_pushcclosure(L, lua_download_task_cancel, 1);
    lua_setfield(L, -2, "cancel");
}

static void pushCallbackStore(lua_State* L)
{
    static char storeKey;
    lua_pushlightuserdata(L, &storeKey);
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
        return;
    lua_pop(L, 1);
    lua_newtable(L);
    lua_newtable(L);
    lua_pushliteral(L, "v");
    lua_setfield(L, -2, "__mode");
    lua_setmetatable(L, -2);
    lua_pushlightuserdata(L, &storeKey);
    lua_pushvalue(L, -2);
    lua_rawset(L, LUA_REGISTRYINDEX);
}

static void saveCallback(lua_State* L, void* addr, const char* callbackName)
{
    // stack [fn]
    pushCallbackStore(L);
    lua_pushlightuserdata(L, (void*)addr);  // stack fn, ud
    lua_rawget(L, -2);
    lua_remove(L, -2);                     // stack fn, callbacks_tb
    lua_pushstring(L, callbackName);        // stack fn, callbacks_tb, callbackName
    lua_pushvalue(L, -3);                   // stack fn, callbacks_tb, callbackName, fn
    lua_settable(L, -3);                    // stack fn, callbacks_tb
    lua_pop(L, 2);                          // stack
}

static int getCallback(lua_State* L, void* addr, const char* callbackName)
{
    // stack []
    pushCallbackStore(L);
    lua_pushlightuserdata(L, (void*)addr);  // stack ud
    lua_rawget(L, -2);
    lua_remove(L, -2);                     // stack callbacks_tb
    if (!lua_istable(L, -1))
        return 0;
    lua_pushstring(L, callbackName);        // stack callbacks_tb, callbackName
    lua_gettable(L, -2);                    // stack callbacks_tb, callbackfn
    lua_remove(L, -2);                      // stack callbackfn
    return lua_isfunction(L, -1) ? 1 : 0;
}

static void postDownloadCallback(std::weak_ptr<LuaDownloaderState> weak, LuaDownloadSnapshot task,
                                 const char* callbackName, std::function<int(lua_State*)> pushArguments = {})
{
    auto state = weak.lock();
    if (!state || !state->alive)
        return;
    // Never run Lua inside the native downloader's update/worker call stack.
    // Snapshots own all data; the queue retains neither downloader nor task.
    state->scheduler->performFunctionInCocosThread([weak, task = std::move(task), callbackName,
                                                   pushArguments = std::move(pushArguments)] {
        auto state = weak.lock();
        if (!state || !state->alive)
            return;
        auto callbackStack = LuaEngine::getInstance()->getLuaStack();
        auto key = state->downloader.get();
        callbackStack->executeCallback([=] {
            auto L = callbackStack->getLuaState();
            if (!state->alive)
                return 0;
            if (!getCallback(L, key, callbackName))
            {
                lua_pop(L, 1);
                return 0;
            }
            pushTaskTable(L, task);
            int count = 1 + (pushArguments ? pushArguments(L) : 0);
            if (!state->alive)
            {
                lua_pop(L, count + 1);
                return 0;
            }
            if (lua_pcall(L, count, 0, 0) != 0)
            {
                lua_pop(L, 1);
                return luaL_error(L, "cc.Downloader.%s invoke callback error!", callbackName);
            }
            return 0;
        });
    });
}

static int lua_downloader_new(lua_State* L)
{
    std::unique_ptr<Downloader> downloader;
    int argc               = lua_gettop(L) - 1;
    if (argc >= 1)
    {
        // parse DownloaderHints
        if (!lua_istable(L, -1))
        {
            luaL_error(L, "cc.Downloader.new: first argument should be table if set");
            return 0;
        }
        DownloaderHints hints;
        hints.countOfMaxProcessingTasks = get_field_int(L, "countOfMaxProcessingTasks", 6);
        hints.timeoutInSeconds          = get_field_int(L, "timeoutInSeconds", 45);
        hints.tempFileNameSuffix        = get_field_string(L, "tempFileNameSuffix", ".tmp");

        downloader = std::make_unique<Downloader>(hints);
    }
    else
    {
        downloader = std::make_unique<Downloader>();
    }

    auto key = downloader.get();
    auto handle = static_cast<LuaDownloaderHandle*>(lua_newuserdata(L, sizeof(LuaDownloaderHandle)));
    *handle = new std::shared_ptr<LuaDownloaderState>(std::make_shared<LuaDownloaderState>(std::move(downloader)));

    luaL_getmetatable(L, "cc.Downloader");
    lua_setmetatable(L, -2);

    // The userdata owns its callback table. A weak registry index lets native
    // events find it without rooting callbacks that capture this userdata.
    pushCallbackStore(L);
    lua_pushlightuserdata(L, (void*)key);
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setfenv(L, -5);
    lua_rawset(L, -3);
    lua_pop(L, 1);

    return 1;
}

static int lua_downloader_createDownloadDataTask(lua_State* L)
{
    Downloader* d          = checkDownloader(L);
    int argc               = lua_gettop(L) - 1;
    std::string url        = "";
    std::string identifier = "";

    if (argc == 0)
    {
        luaL_error(L, "cc.Downloader.createDownloadDataTask parameter error");
        return 0;
    }

    if (argc >= 1)
        url = lua_tostring(L, 2);
    if (argc >= 2)
        identifier = lua_tostring(L, 3);
    auto tsk = d->createDownloadDataTask(url, identifier);

    if (tsk)
        pushTaskTable(L, tsk);
    else
        lua_pushnil(L);
    return 1;
}

static int lua_downloader_createDownloadFileTask(lua_State* L)
{
    int argc                = lua_gettop(L) - 1;
    Downloader* d           = checkDownloader(L);
    std::string_view url         = ""sv;
    std::string_view storagePath = ""sv;
    std::string_view identifier  = ""sv;

    if (argc < 2)
    {
        luaL_error(L, "cc.Downloader.createDownloadFileTask parameter error!");
        return 0;
    }

    url         = cclua_tosv(L, 2);
    storagePath = cclua_tosv(L, 3);
    if (argc > 2)
        identifier = cclua_tosv(L, 4);

    std::string_view md5checksum = ""sv;
    std::string_view cacertPath  = ""sv;
    bool background = false;

    if (argc > 3)
        md5checksum = cclua_tosv(L, 5);

    if (argc > 4)
        background = lua_toboolean(L, 6);

    if (argc > 5)
        cacertPath = cclua_tosv(L, 7);

    auto tsk = d->createDownloadFileTask(url, storagePath, identifier, md5checksum, background, cacertPath);

    if (tsk)
        pushTaskTable(L, tsk);
    else
        lua_pushnil(L);
    return 1;
}
static int lua_downloader_setOnFileTaskSuccess(lua_State* L)
{
    int argc      = lua_gettop(L) - 1;
    Downloader* d = checkDownloader(L);
    if (argc != 1)
    {
        luaL_error(L, "cc.Downloader.setOnFileTaskSuccess parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnFileTaskSuccess");

    std::weak_ptr<LuaDownloaderState> weak = **checkDownloaderHandle(L);
    d->setOnFileTaskSuccess([weak](const DownloadTask& task) {
        postDownloadCallback(weak, LuaDownloadSnapshot(task), "setOnFileTaskSuccess");
    });

    return 0;
}
static int lua_downloader_setOnTaskProgress(lua_State* L)
{
    Downloader* d = checkDownloader(L);
    int argc      = lua_gettop(L) - 1;
    if (argc != 1)
    {
        luaL_error(L, "cc.Downloader.setOnTaskProgress parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnTaskProgress");

    std::weak_ptr<LuaDownloaderState> weak = **checkDownloaderHandle(L);
    d->setOnTaskProgress([weak](const DownloadTask& task) {
        auto snapshot = LuaDownloadSnapshot(task);
        postDownloadCallback(weak, snapshot, "setOnTaskProgress", [snapshot](lua_State* L) {
            lua_pushnumber(L, static_cast<lua_Number>(snapshot.bytesReceived));
            lua_pushnumber(L, static_cast<lua_Number>(snapshot.totalBytesReceived));
            lua_pushnumber(L, static_cast<lua_Number>(snapshot.totalBytesExpected));
            return 3;
        });
    });

    return 0;
}
static int lua_downloader_setOnTaskError(lua_State* L)
{
    Downloader* d = checkDownloader(L);
    int argc      = lua_gettop(L) - 1;
    if (argc != 1)
    {
        luaL_error(L, "cc.Downloader.setOnTaskError parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnTaskError");

    std::weak_ptr<LuaDownloaderState> weak = **checkDownloaderHandle(L);
    d->setOnTaskError([weak](
                          const DownloadTask& task, int errorCode, int errorCodeInternal, std::string_view errorSt) {
        postDownloadCallback(weak, LuaDownloadSnapshot(task), "setOnTaskError",
                             [errorCode, errorCodeInternal, error = std::string(errorSt)](lua_State* L) {
            lua_pushnumber(L, errorCode);
            lua_pushnumber(L, errorCodeInternal);
            lua_pushlstring(L, error.data(), error.size());
            return 3;
        });
    });

    return 0;
}

static int lua_downloader_cleanup(lua_State* L)
{
    auto handle = static_cast<LuaDownloaderHandle*>(luaL_checkudata(L, 1, "cc.Downloader"));
    if (!*handle)
        return 0;
    auto state = std::move(**handle);
    delete *handle;
    *handle = nullptr;
    state->alive = false;

    // remove callback table
    pushCallbackStore(L);
    lua_pushlightuserdata(L, (void*)state->downloader.get());
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_pop(L, 1);
    // Stops and joins the worker before its owner can disappear. Any already
    // queued Lua callbacks only hold a weak, now invalid lifetime token.
    state->downloader.reset();
    return 0;
}

static int lua_downloader_tostring(lua_State* L)
{
    lua_pushstring(L, "[cc.Downloader]");
    return 1;
}

static const struct luaL_Reg downloaderStaticFns[] = {{"new", lua_downloader_new},
                                                      /*
                                                       * cocos2d::Downloader is not a subclass of cocos2d::Ref,
                                                       * `create()` is not provided.
                                                       */
                                                      //{ "create", lua_downloader_new },
                                                      {nullptr, nullptr}};

static const struct luaL_Reg downloaderMemberFns[] = {{"createDownloadDataTask", lua_downloader_createDownloadDataTask},
                                                      {"createDownloadFileTask", lua_downloader_createDownloadFileTask},
                                                      {"setOnFileTaskSuccess", lua_downloader_setOnFileTaskSuccess},
                                                      {"setOnTaskProgress", lua_downloader_setOnTaskProgress},
                                                      {"setOnTaskError", lua_downloader_setOnTaskError},
                                                      {"__gc", lua_downloader_cleanup},
                                                      {"__tostring", lua_downloader_tostring},
                                                      {nullptr, nullptr}};

int register_downloader(lua_State* L)
{
    luaL_newmetatable(L, "cc.DownloadTaskCancellation");
    lua_pushcfunction(L, lua_download_task_cleanup);
    lua_setfield(L, -2, "__gc");
    lua_pop(L, 1);

    luaL_newmetatable(L, "cc.Downloader");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2); /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */

    luaL_register(L, nullptr, downloaderMemberFns);
    luaL_register(L, "cc.Downloader", downloaderStaticFns);
    return 1;
}
