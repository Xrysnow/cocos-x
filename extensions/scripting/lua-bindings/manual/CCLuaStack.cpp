/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

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

#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include <string.h>
extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "scripting/lua-bindings/manual/AxluaLoader.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#    include "scripting/lua-bindings/manual/platform/ios/CCLuaObjcBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#    include "scripting/lua-bindings/manual/platform/android/CCLuaJavaBridge.h"
#endif

#include "scripting/lua-bindings/manual/base/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/auto/axlua_base_auto.hpp"
#include "scripting/lua-bindings/manual/base/axlua_base_manual.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/auto/axlua_physics_auto.hpp"
#include "scripting/lua-bindings/manual/physics/axlua_physics_manual.hpp"
#include "scripting/lua-bindings/auto/axlua_backend_auto.hpp"
#include "base/ZipUtils.h"
#include "platform/CCFileUtils.h"

namespace
{
int get_string_for_print(lua_State* L, std::string* out)
{
    int n = lua_gettop(L); /* number of arguments */
    int i;

    lua_getglobal(L, "tostring");
    for (i = 1; i <= n; i++)
    {
        const char* s;
        lua_pushvalue(L, -1); /* function to be called */
        lua_pushvalue(L, i);  /* value to print */
        lua_call(L, 1, 1);
        size_t sz;
        s = lua_tolstring(L, -1, &sz); /* get result */
        if (s == NULL)
            return luaL_error(L, "'tostring' must return a string to 'print'");
        if (i > 1)
            out->append("\t");
        out->append(s, sz);
        lua_pop(L, 1); /* pop result */
    }
    return 0;
}

int lua_print(lua_State* L)
{
    std::string t;
    get_string_for_print(L, &t);
    CCLOG("[LUA-print] %s", t.c_str());

    return 0;
}

int lua_release_print(lua_State* L)
{
    std::string t;
    get_string_for_print(L, &t);
    log("[LUA-print] %s", t.c_str());

    return 0;
}

int lua_version(lua_State* L)
{
    lua_pushinteger(L, LUA_VERSION_NUM);
    return 1;
}
}  // namespace

NS_CC_BEGIN

LuaStack::~LuaStack()
{
    if (nullptr != _state)
    {
        lua_close(_state);
    }
}

LuaStack* LuaStack::create()
{
    LuaStack* stack = new LuaStack();
    stack->init();
    stack->autorelease();
    return stack;
}

LuaStack* LuaStack::attach(lua_State* L)
{
    LuaStack* stack = new LuaStack();
    stack->initWithLuaState(L);
    stack->autorelease();
    return stack;
}

bool LuaStack::init()
{
    _state = lua_open();
    luaL_openlibs(_state);
    toluafix_open(_state);

    // Register our version of the global "print" function
    const luaL_Reg global_functions[] = {
        {"print", lua_print}, {"release_print", lua_release_print}, {"version", lua_version}, {nullptr, nullptr}};
    luaL_register(_state, "_G", global_functions);

    g_luaType.clear();
    register_all_ax_base(_state);
    register_all_ax_backend(_state);
    register_all_ax_manual(_state);
    register_all_ax_module_manual(_state);
    register_all_ax_math_manual(_state);
    register_all_ax_shaders_manual(_state);
    register_all_ax_bytearray_manual(_state);

    tolua_luanode_open(_state);
    register_luanode_manual(_state);
#if CC_USE_PHYSICS
    register_all_ax_physics(_state);
    register_all_ax_physics_manual(_state);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    LuaObjcBridge::luaopen_luaoc(_state);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    LuaJavaBridge::luaopen_luaj(_state);
#endif

    tolua_script_handler_mgr_open(_state);

    // add cocos2dx loader
    addLuaLoader(axlua_loader);

    return true;
}

bool LuaStack::initWithLuaState(lua_State* L)
{
    _state = L;
    return true;
}

void LuaStack::addSearchPath(const char* path)
{
    lua_getglobal(_state, "package"); /* L: package */
    lua_getfield(_state, -1, "path"); /* get package.path, L: package path */
    const char* cur_path = lua_tostring(_state, -1);
    lua_pushfstring(_state, "%s/?.lua;%s", path, cur_path); /* L: package path newpath */
    lua_setfield(_state, -3, "path");                       /* package.path = newpath, L: package path */
    lua_pop(_state, 2);                                     /* L: - */
}

void LuaStack::addLuaLoader(lua_CFunction func)
{
    if (!func)
        return;

#if LUA_VERSION_NUM >= 504 || (LUA_VERSION_NUM >= 502 && !defined(LUA_COMPAT_LOADERS))
    const char* realname = "searchers";
#else
    const char* realname = "loaders";
#endif

    // stack content after the invoking of the function
    // get loader table
    lua_getglobal(_state, "package");   /* L: package */
    lua_getfield(_state, -1, realname); /* L: package, loaders */

    // insert loader into index 2
    lua_pushcfunction(_state, func); /* L: package, loaders, func */
    for (int i = (int)(lua_objlen(_state, -2) + 1); i > 2; --i)
    {
        lua_rawgeti(_state, -2, i - 1); /* L: package, loaders, func, function */
        // we call lua_rawgeti, so the loader table now is at -3
        lua_rawseti(_state, -3, i); /* L: package, loaders, func */
    }
    lua_rawseti(_state, -2, 2); /* L: package, loaders */

    // set loaders into package
    lua_setfield(_state, -2, realname); /* L: package */

    lua_pop(_state, 1);
}

void LuaStack::removeScriptObjectByObject(Ref* pObj)
{
    toluafix_remove_ccobject_by_refid(_state, pObj->_luaID);
}

void LuaStack::removeScriptHandler(int nHandler)
{
    toluafix_remove_function_by_refid(_state, nHandler);
}

int LuaStack::executeString(const char* codes)
{
    luaL_loadstring(_state, codes);
    return executeFunction(0);
}

int LuaStack::executeScriptFile(const char* filename)
{
    CCAssert(filename, "CCLuaStack::executeScriptFile() - invalid filename");

    std::string filePath{filename};
    Data data = FileUtils::getInstance()->getDataFromFile(filePath);
    int rn    = 0;
    if (!data.isNull())
    {
        filePath.insert(filePath.begin(), '@');  // lua standard, add file chunck mark '@'
        if (luaLoadBuffer(_state, (const char*)data.getBytes(), (int)data.getSize(), filePath.c_str()) == 0)
        {
            rn = executeFunction(0);
        }
    }
    return rn;
}

int LuaStack::executeGlobalFunction(const char* functionName)
{
    lua_getglobal(_state, functionName); /* query function by name, stack: function */
    if (!lua_isfunction(_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(_state, 1);
        return 0;
    }
    return executeFunction(0);
}

void LuaStack::clean()
{
    lua_settop(_state, 0);
}

void LuaStack::pushInt(int intValue)
{
    lua_pushinteger(_state, intValue);
}

void LuaStack::pushFloat(float floatValue)
{
    lua_pushnumber(_state, floatValue);
}

void LuaStack::pushLong(long longValue)
{
    lua_pushnumber(_state, longValue);
}

void LuaStack::pushBoolean(bool boolValue)
{
    lua_pushboolean(_state, boolValue);
}

void LuaStack::pushString(std::string_view stringValue)
{
    lua_pushlstring(_state, stringValue.data(), stringValue.length());
}

void LuaStack::pushString(const char* stringValue, int length)
{
    lua_pushlstring(_state, stringValue, length);
}

void LuaStack::pushNil()
{
    lua_pushnil(_state);
}

void LuaStack::pushObject(Ref* objectValue, const char* typeName)
{
    toluafix_pushusertype_ccobject(_state, objectValue->_ID, &objectValue->_luaID, objectValue, typeName);
}

void LuaStack::pushLuaValue(const LuaValue& value)
{
    const LuaValueType type = value.getType();
    if (type == LuaValueTypeInt)
    {
        return pushInt(value.intValue());
    }
    else if (type == LuaValueTypeFloat)
    {
        return pushFloat(value.floatValue());
    }
    else if (type == LuaValueTypeBoolean)
    {
        return pushBoolean(value.booleanValue());
    }
    else if (type == LuaValueTypeString)
    {
        return pushString(value.stringValue());
    }
    else if (type == LuaValueTypeDict)
    {
        pushLuaValueDict(value.dictValue());
    }
    else if (type == LuaValueTypeArray)
    {
        pushLuaValueArray(value.arrayValue());
    }
    else if (type == LuaValueTypeObject)
    {
        pushObject(value.ccobjectValue(), value.getObjectTypename().data());
    }
}

void LuaStack::pushLuaValueDict(const LuaValueDict& dict)
{
    lua_newtable(_state); /* L: table */
    for (LuaValueDictIterator it = dict.begin(); it != dict.end(); ++it)
    {
        lua_pushlstring(_state, it->first.c_str(), it->first.length()); /* L: table key */
        pushLuaValue(it->second);                                       /* L: table key value */
        lua_rawset(_state, -3);                                         /* table.key = value, L: table */
    }
}

void LuaStack::pushLuaValueArray(const LuaValueArray& array)
{
    lua_newtable(_state); /* L: table */
    int index = 1;
    for (LuaValueArrayIterator it = array.begin(); it != array.end(); ++it)
    {
        pushLuaValue(*it);              /* L: table value */
        lua_rawseti(_state, -2, index); /* table[index] = value, L: table */
        ++index;
    }
}

bool LuaStack::pushFunctionByHandler(int nHandler)
{
    toluafix_get_function_by_refid(_state, nHandler); /* L: ... func */
    if (!lua_isfunction(_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(_state, 1);
        return false;
    }
    return true;
}

int LuaStack::executeFunction(int numArgs)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(_state, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(_state, numArgs + 1);  // remove function and arguments
        return 0;
    }

    int traceback = 0;
    lua_getglobal(_state, "__G__TRACKBACK__"); /* L: ... func arg1 arg2 ... G */
    if (!lua_isfunction(_state, -1))
    {
        lua_pop(_state, 1); /* L: ... func arg1 arg2 ... */
    }
    else
    {
        lua_insert(_state, functionIndex - 1); /* L: ... G func arg1 arg2 ... */
        traceback = functionIndex - 1;
    }

    int error = 0;
    ++_callFromLua;
    error = lua_pcall(_state, numArgs, 1, traceback); /* L: ... [G] ret */
    --_callFromLua;
    if (error)
    {
        if (traceback == 0)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(_state, -1)); /* L: ... error */
            lua_pop(_state, 1);                                // remove error message from stack
        }
        else /* L: ... G error */
        {
            lua_pop(_state, 2);  // remove __G__TRACKBACK__ and error message from stack
        }
        return 0;
    }

    // get return value
    int ret = 0;
    if (lua_isnumber(_state, -1))
    {
        ret = (int)lua_tointeger(_state, -1);
    }
    else if (lua_isboolean(_state, -1))
    {
        ret = (int)lua_toboolean(_state, -1);
    }
    // remove return value from stack
    lua_pop(_state, 1); /* L: ... [G] */

    if (traceback)
    {
        lua_pop(_state, 1);  // remove __G__TRACKBACK__ from stack      /* L: ... */
    }

    return ret;
}

int LuaStack::executeFunctionByHandler(int nHandler, int numArgs)
{
    int ret = 0;
    if (pushFunctionByHandler(nHandler)) /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(_state, -(numArgs + 1)); /* L: ... func arg1 arg2 ... */
        }
        ret = executeFunction(numArgs);
    }
    lua_settop(_state, 0);
    return ret;
}

bool LuaStack::handleAssert(const char* msg)
{
    if (_callFromLua == 0)
        return false;

    lua_pushfstring(_state, "ASSERT FAILED ON LUA EXECUTE: %s", msg ? msg : "unknown");
    lua_error(_state);
    return true;
}

int LuaStack::reallocateScriptHandler(int nHandler)
{
    LUA_FUNCTION nNewHandle = -1;

    if (pushFunctionByHandler(nHandler))
    {
        nNewHandle = toluafix_ref_function(_state, lua_gettop(_state), 0);
    }
    /*
        toluafix_get_function_by_refid(_state,nNewHandle);
        if (!lua_isfunction(_state, -1))
        {
            CCLOG("Error!");
        }
        lua_settop(_state, 0);
    */
    return nNewHandle;
}

int LuaStack::executeFunction(int handler,
                              int numArgs,
                              int numResults,
                              const std::function<void(lua_State*, int)>& func)
{
    if (pushFunctionByHandler(handler)) /* L: ... arg1 arg2 ... func */
    {
        if (numArgs > 0)
        {
            lua_insert(_state, -(numArgs + 1)); /* L: ... func arg1 arg2 ... */
        }

        int functionIndex = -(numArgs + 1);

        if (!lua_isfunction(_state, functionIndex))
        {
            CCLOG("value at stack [%d] is not function", functionIndex);
            lua_pop(_state, numArgs + 1);  // remove function and arguments
            return 0;
        }

        int traceCallback = 0;
        lua_getglobal(_state, "__G__TRACKBACK__"); /* L: ... func arg1 arg2 ... G */
        if (!lua_isfunction(_state, -1))
        {
            lua_pop(_state, 1); /* L: ... func arg1 arg2 ... */
        }
        else
        {
            lua_insert(_state, functionIndex - 1); /* L: ... G func arg1 arg2 ... */
            traceCallback = functionIndex - 1;
        }

        int error = 0;
        ++_callFromLua;
        error = lua_pcall(_state, numArgs, numResults, traceCallback); /* L: ... [G] ret1 ret2 ... retResults*/
        --_callFromLua;

        if (error)
        {
            if (traceCallback == 0)
            {
                CCLOG("[LUA ERROR] %s", lua_tostring(_state, -1)); /* L: ... error */
                lua_pop(_state, 1);                                // remove error message from stack
            }
            else /* L: ... G error */
            {
                lua_pop(_state, 2);  // remove __G__TRACKBACK__ and error message from stack
            }
            return 0;
        }

        // get return value,don't pass LUA_MULTRET to numResults,
        do
        {

            if (numResults <= 0 || nullptr == func)
                break;

            func(_state, numResults);

        } while (0);

        if (traceCallback)
        {
            lua_pop(_state, 1);  // remove __G__TRACKBACK__ from stack      /* L: ... */
        }
    }

    return 1;
}

int LuaStack::reload(const char* moduleFileName)
{
    if (nullptr == moduleFileName || strlen(moduleFileName) == 0)
    {
        CCLOG("moudulFileName is null");
        return 1;
    }

    lua_getglobal(_state, "package");   /* L: package */
    lua_getfield(_state, -1, "loaded"); /* L: package loaded */
    lua_pushstring(_state, moduleFileName);
    lua_gettable(_state, -2); /* L:package loaded module */
    if (!lua_isnil(_state, -1))
    {
        lua_pushstring(_state, moduleFileName); /* L:package loaded module name */
        lua_pushnil(_state);                    /* L:package loaded module name nil*/
        lua_settable(_state, -4);               /* L:package loaded module */
    }
    lua_pop(_state, 3);

    std::string name    = moduleFileName;
    std::string require = "require \'" + name + "\'";
    return executeString(require.c_str());
}

int LuaStack::loadChunksFromZIP(const char* zipFilePath)
{
    pushString(zipFilePath);
    luaLoadChunksFromZIP(_state);
    int ret = lua_toboolean(_state, -1);
    lua_pop(_state, 1);
    return ret;
}

int LuaStack::luaLoadChunksFromZIP(lua_State* L)
{
    if (lua_gettop(L) < 1)
    {
        CCLOG("luaLoadChunksFromZIP() - invalid arguments");
        return 0;
    }

    using namespace cxx17;
    const auto BYTECODE_FILE_EXT     = ".luac"_sv;
    const auto NOT_BYTECODE_FILE_EXT = ".lua"_sv;

    const char* zipFilename = lua_tostring(L, -1);
    lua_settop(L, 0);
    FileUtils* utils        = FileUtils::getInstance();
    std::string zipFilePath = utils->fullPathForFilename(zipFilename);

    LuaStack* stack = this;

    do
    {
        void* buffer = nullptr;
        ZipFile* zip = nullptr;
        Data zipFileData(utils->getDataFromFile(zipFilePath));
        unsigned char* bytes = zipFileData.getBytes();
        ssize_t size         = zipFileData.getSize();

        if (size > 0)
        {
            zip = ZipFile::createWithBuffer(bytes, (unsigned long)size);
        }

        if (zip)
        {
            CCLOG("lua_loadChunksFromZIP() - load zip file: %s", zipFilePath.c_str());
            lua_getglobal(L, "package");
            lua_getfield(L, -1, "preload");

            int count            = 0;
            std::string filename = zip->getFirstFilename();
            while (filename.length())
            {
                ssize_t bufferSize     = 0;
                unsigned char* zbuffer = zip->getFileData(filename.c_str(), &bufferSize);
                if (bufferSize)
                {
                    // remove .lua or .luac extension
                    size_t pos = filename.find_last_of('.');
                    if (pos != std::string::npos)
                    {
                        std::string suffix = filename.substr(pos, filename.length());
                        if (cxx17::string_view{suffix} == NOT_BYTECODE_FILE_EXT ||
                            cxx17::string_view{suffix} == BYTECODE_FILE_EXT)
                        {
                            filename.erase(pos);
                        }
                    }
                    // replace path separator '/' '\' to '.'
                    for (auto& character : filename)
                    {
                        if (character == '/' || character == '\\')
                        {
                            character = '.';
                        }
                    }
                    CCLOG("[luaLoadChunksFromZIP] add %s to preload", filename.c_str());
                    if (stack->luaLoadBuffer(L, (char*)zbuffer, (int)bufferSize, filename.c_str()) == 0)
                    {
                        lua_setfield(L, -2, filename.c_str());
                        ++count;
                    }
                    free(zbuffer);
                }
                filename = zip->getNextFilename();
            }
            CCLOG("lua_loadChunksFromZIP() - loaded chunks count: %d", count);
            lua_pop(L, 2);
            lua_pushboolean(L, 1);

            delete zip;
        }
        else
        {
            CCLOG("lua_loadChunksFromZIP() - not found or invalid zip file: %s", zipFilePath.c_str());
            lua_pushboolean(L, 0);
        }

        if (buffer)
        {
            free(buffer);
        }
    } while (0);

    return 1;
}

namespace
{

void skipBOM(const char*& chunk, int& chunkSize)
{
    // UTF-8 BOM? skip
    if (chunkSize >= 3 && static_cast<unsigned char>(chunk[0]) == 0xEF &&
        static_cast<unsigned char>(chunk[1]) == 0xBB && static_cast<unsigned char>(chunk[2]) == 0xBF)
    {
        chunk += 3;
        chunkSize -= 3;
    }
}

}  // end anonymous namespace

int LuaStack::luaLoadBuffer(lua_State* L, const char* chunk, int chunkSize, const char* chunkName)
{
    int r = 0;

    skipBOM(chunk, chunkSize);
    r = luaL_loadbuffer(L, chunk, chunkSize, chunkName);

#if defined(_CC_DEBUG) && _CC_DEBUG > 0
    if (r)
    {
        switch (r)
        {
        case LUA_ERRSYNTAX:
            CCLOG("[LUA ERROR] load \"%s\", error: syntax error during pre-compilation.", chunkName);
            break;

        case LUA_ERRMEM:
            CCLOG("[LUA ERROR] load \"%s\", error: memory allocation error.", chunkName);
            break;

        case LUA_ERRFILE:
            CCLOG("[LUA ERROR] load \"%s\", error: cannot open/read file.", chunkName);
            break;

        default:
            CCLOG("[LUA ERROR] load \"%s\", error: unknown.", chunkName);
        }
    }
#endif
    return r;
}

NS_CC_END
