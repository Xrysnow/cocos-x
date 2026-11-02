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

#include "scripting/lua-bindings/manual/platform/android/CCLuaJavaBridge.h"
#if defined(__ANDROID__)
    #include "platform/android/jni/JniHelper.h"
    #include <android/log.h>
    #include <algorithm>
    #include "base/ccUTF8.h"

    #define LOG_TAG "luajc"
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
    #include "scripting/lua-bindings/manual/tolua_fix.h"
}

namespace
{
template <class Callback>
int protectedBridgeCallback(lua_State* L, const Callback& callback)
{
    if (!L)
        return -1;
    struct Context
    {
        const Callback* callback;
        int result;
    } context{&callback, 0};
    const int status = lua_cpcall(L, [](lua_State* L) -> int {
        auto* context = lua_type(L, 1) == LUA_TLIGHTUSERDATA
                            ? static_cast<Context*>(lua_touserdata(L, 1)) : nullptr;
        if (!context)
            return luaL_error(L, "expired LuaJavaBridge callback invocation");
        lua_settop(L, 0);
        context->result = (*context->callback)();
        return 0;
    }, &context);
    if (status != 0)
    {
        lua_pop(L, 1);
        return -status;
    }
    return context.result;
}
} // namespace

LuaJavaBridge::CallInfo::~CallInfo()
{
    if (m_returnType == TypeString && m_ret.stringValue)
    {
        delete m_ret.stringValue;
    }
    if (m_env)
    {
        if (m_retjs)
            m_env->DeleteLocalRef(m_retjs);
        if (m_classID)
            m_env->DeleteLocalRef(m_classID);
    }
}

bool LuaJavaBridge::CallInfo::execute()
{
    switch (m_returnType)
    {
    case TypeVoid:
        m_env->CallStaticVoidMethod(m_classID, m_methodID);
        break;

    case TypeInteger:
        m_ret.intValue = m_env->CallStaticIntMethod(m_classID, m_methodID);
        break;

    case TypeFloat:
        m_ret.floatValue = m_env->CallStaticFloatMethod(m_classID, m_methodID);
        break;

    case TypeBoolean:
        m_ret.boolValue = m_env->CallStaticBooleanMethod(m_classID, m_methodID);
        break;

    case TypeString:
    {
        m_retjs              = (jstring)m_env->CallStaticObjectMethod(m_classID, m_methodID);
        if (m_env->ExceptionCheck() == JNI_TRUE)
            break;
        bool bValidStr       = true;
        std::string strValue = cocos2d::StringUtils::getStringUTFCharsJNI(m_env, m_retjs, &bValidStr);
        m_ret.stringValue    = (false == bValidStr) ? nullptr : new string(strValue);
        break;
    }

    default:
        m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
        LOGD("Return type '%d' is not supported", static_cast<int>(m_returnType));
        return false;
    }

    if (m_env->ExceptionCheck() == JNI_TRUE)
    {
        m_env->ExceptionDescribe();
        m_env->ExceptionClear();
        m_error = LUAJ_ERR_EXCEPTION_OCCURRED;
        return false;
    }

    return true;
}

bool LuaJavaBridge::CallInfo::executeWithArgs(jvalue* args)
{
    switch (m_returnType)
    {
    case TypeVoid:
        m_env->CallStaticVoidMethodA(m_classID, m_methodID, args);
        break;

    case TypeInteger:
        m_ret.intValue = m_env->CallStaticIntMethodA(m_classID, m_methodID, args);
        break;

    case TypeFloat:
        m_ret.floatValue = m_env->CallStaticFloatMethodA(m_classID, m_methodID, args);
        break;

    case TypeBoolean:
        m_ret.boolValue = m_env->CallStaticBooleanMethodA(m_classID, m_methodID, args);
        break;

    case TypeString:
    {
        m_retjs              = (jstring)m_env->CallStaticObjectMethodA(m_classID, m_methodID, args);
        if (m_env->ExceptionCheck() == JNI_TRUE)
            break;
        bool bValidStr       = true;
        std::string strValue = cocos2d::StringUtils::getStringUTFCharsJNI(m_env, m_retjs, &bValidStr);
        m_ret.stringValue    = (false == bValidStr) ? nullptr : new string(strValue);
        break;
    }

    default:
        m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
        LOGD("Return type '%d' is not supported", static_cast<int>(m_returnType));
        return false;
    }

    if (m_env->ExceptionCheck() == JNI_TRUE)
    {
        m_env->ExceptionDescribe();
        m_env->ExceptionClear();
        m_error = LUAJ_ERR_EXCEPTION_OCCURRED;
        return false;
    }

    return true;
}

int LuaJavaBridge::CallInfo::pushReturnValue(lua_State* L)
{
    if (m_error != LUAJ_ERR_OK)
    {
        lua_pushinteger(L, m_error);
        return 1;
    }

    switch (m_returnType)
    {
    case TypeInteger:
        lua_pushinteger(L, m_ret.intValue);
        return 1;
    case TypeFloat:
        lua_pushnumber(L, m_ret.floatValue);
        return 1;
    case TypeBoolean:
        lua_pushboolean(L, m_ret.boolValue);
        return 1;
    case TypeString:
        if (m_ret.stringValue == nullptr)
        {
            lua_pushnil(L);
        }
        else
        {
            lua_pushstring(L, m_ret.stringValue->c_str());
        }
        return 1;
    default:
        break;
    }

    return 0;
}

bool LuaJavaBridge::CallInfo::validateMethodSig()
{
    size_t len = m_methodSig.length();
    if (len < 3 || m_methodSig[0] != '(')  // min sig is "()V"
    {
        m_error = LUAJ_ERR_INVALID_SIGNATURES;
        return false;
    }

    size_t pos = 1;
    while (pos < len && m_methodSig[pos] != ')')
    {
        LuaJavaBridge::ValueType type = checkType(m_methodSig, &pos);
        if (type == TypeInvalid)
            return false;
        if (type == TypeVoid || type == TypeVector)
        {
            m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
            return false;
        }

        m_argumentsCount++;
        m_argumentsType.emplace_back(type);
        pos++;
    }

    if (pos >= len || m_methodSig[pos] != ')')
    {
        m_error = LUAJ_ERR_INVALID_SIGNATURES;
        return false;
    }

    pos++;
    if (pos >= len)
    {
        m_error = LUAJ_ERR_INVALID_SIGNATURES;
        return false;
    }
    m_returnType = checkType(m_methodSig, &pos);
    if (m_returnType == TypeInvalid)
        return false;
    if (m_returnType == TypeVector)
    {
        m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
        return false;
    }
    if (pos + 1 != len)
    {
        m_error = LUAJ_ERR_INVALID_SIGNATURES;
        return false;
    }
    return true;
}

LuaJavaBridge::ValueType LuaJavaBridge::CallInfo::checkType(const string& sig, size_t* pos)
{
    switch (sig[*pos])
    {
    case 'I':
        return TypeInteger;
    case 'F':
        return TypeFloat;
    case 'Z':
        return TypeBoolean;
    case 'V':
        return TypeVoid;
    case 'L':
        size_t pos2 = sig.find_first_of(';', *pos + 1);
        if (pos2 == string::npos)
        {
            m_error = LUAJ_ERR_INVALID_SIGNATURES;
            return TypeInvalid;
        }

        const string t = sig.substr(*pos, pos2 - *pos + 1);
        if (t.compare("Ljava/lang/String;") == 0)
        {
            *pos = pos2;
            return TypeString;
        }
        else if (t.compare("Ljava/util/Vector;") == 0)
        {
            *pos = pos2;
            return TypeVector;
        }
        else
        {
            m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
            return TypeInvalid;
        }
    }

    m_error = LUAJ_ERR_TYPE_NOT_SUPPORT;
    return TypeInvalid;
}

bool LuaJavaBridge::CallInfo::getMethodInfo()
{
    m_methodID = nullptr;
    m_env      = nullptr;

    if (!cocos2d::JniHelper::getJavaVM() || !(m_env = cocos2d::JniHelper::getEnv()))
    {
        LOGD("Failed to get the JNI environment for %s.%s", m_className.c_str(), m_methodName.c_str());
        m_error = LUAJ_ERR_VM_FAILURE;
        return false;
    }

    // ClassLoader.loadClass takes binary names; Lua helpers also accept JNI slash names.
    std::string className = m_className;
    std::replace(className.begin(), className.end(), '/', '.');
    if (!cocos2d::JniHelper::classloader || !cocos2d::JniHelper::loadclassMethod_methodID)
    {
        LOGD("Classloader is not initialized for %s", className.c_str());
        m_error = LUAJ_ERR_VM_FAILURE;
        return false;
    }
    jstring classString = m_env->NewStringUTF(className.c_str());
    if (!classString || m_env->ExceptionCheck() == JNI_TRUE)
    {
        m_env->ExceptionDescribe();
        m_env->ExceptionClear();
        if (classString)
            m_env->DeleteLocalRef(classString);
        m_error = LUAJ_ERR_EXCEPTION_OCCURRED;
        return false;
    }
    m_classID = static_cast<jclass>(m_env->CallObjectMethod(cocos2d::JniHelper::classloader,
        cocos2d::JniHelper::loadclassMethod_methodID, classString));
    m_env->DeleteLocalRef(classString);
    if (!m_classID || m_env->ExceptionCheck() == JNI_TRUE)
    {
        m_env->ExceptionDescribe();
        m_env->ExceptionClear();
        LOGD("Failed to find class %s", m_className.c_str());
        m_error = LUAJ_ERR_METHOD_NOT_FOUND;
        return false;
    }
    m_methodID = m_env->GetStaticMethodID(m_classID, m_methodName.c_str(), m_methodSig.c_str());
    if (!m_methodID || m_env->ExceptionCheck() == JNI_TRUE)
    {
        m_env->ExceptionDescribe();
        m_env->ExceptionClear();
        LOGD("Failed to find %s.%s %s", m_className.c_str(), m_methodName.c_str(), m_methodSig.c_str());
        m_error = LUAJ_ERR_METHOD_NOT_FOUND;
        return false;
    }
    return true;
}

/* ---------------------------------------- */

lua_State* LuaJavaBridge::s_luaState = NULL;
int LuaJavaBridge::s_newFunctionId   = 0;

void LuaJavaBridge::luaopen_luaj(lua_State* L)
{
    s_luaState = L;
    lua_newtable(L);
    lua_pushstring(L, "callStaticMethod");
    lua_pushcfunction(L, LuaJavaBridge::callJavaStaticMethod);
    lua_rawset(L, -3);
    lua_setglobal(L, "LuaJavaBridge");
}

/*
args:
    const char *className
    const char *methodName
    LUA_TABLE   args
    const char *sig
*/
int LuaJavaBridge::callJavaStaticMethod(lua_State* L)
{
    if (!lua_isstring(L, -4) || !lua_isstring(L, -3) || !lua_istable(L, -2) || !lua_isstring(L, -1))
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_INVALID_SIGNATURES);
        return 2;
    }

    LOGD("%s", "LuaJavaBridge::callJavaStaticMethod(lua_State *L)");

    const char* className  = lua_tostring(L, -4);
    const char* methodName = lua_tostring(L, -3);
    const char* methodSig  = lua_tostring(L, -1);

    CallInfo call(className, methodName, methodSig);
    if (!call.isValid())
    {
        lua_pushboolean(L, 0);
        lua_pushinteger(L, call.getErrorCode());
        return 2;
    }

    // check args
    lua_pop(L, 1);                            /* L: args */
    int count    = fetchArrayElements(L, -1); /* L: args e1 e2 e3 e4 ... */
    bool validArguments = count == call.getArgumentsCount();
    for (int i = 0; validArguments && i < count; ++i)
    {
        const int index = -count + i;
        switch (call.argumentTypeAtIndex(i))
        {
        case TypeInteger:
            validArguments = lua_isnumber(L, index) || lua_isfunction(L, index);
            break;
        case TypeFloat:
            validArguments = lua_isnumber(L, index);
            break;
        case TypeBoolean:
            validArguments = lua_isboolean(L, index);
            break;
        case TypeString:
            validArguments = lua_isstring(L, index);
            break;
        default:
            validArguments = false;
            break;
        }
    }
    if (!validArguments)
    {
        lua_pop(L, count);
        LOGD("Invalid arguments for %s.%s %s", className, methodName, methodSig);
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_INVALID_SIGNATURES);
        return 2;
    }
    jvalue* args = NULL;
    std::vector<int> retainedFunctions;
    if (count > 0)
    {
        args = new jvalue[count]{};
        for (int i = 0; i < count; ++i)
        {
            int index = -count + i;
            switch (call.argumentTypeAtIndex(i))
            {
            case TypeInteger:
                if (lua_isfunction(L, index))
                {
                    args[i].i = retainLuaFunction(L, index, NULL);
                    retainedFunctions.push_back(args[i].i);
                }
                else
                {
                    args[i].i = (int)lua_tonumber(L, index);
                }
                break;

            case TypeFloat:
                args[i].f = lua_tonumber(L, index);
                break;

            case TypeBoolean:
                args[i].z = lua_toboolean(L, index) != 0 ? JNI_TRUE : JNI_FALSE;
                break;

            case TypeString:
            default:
                args[i].l = call.getEnv()->NewStringUTF(lua_tostring(L, index));
                break;
            }
            if (call.getEnv()->ExceptionCheck() == JNI_TRUE)
                break;
        }
        lua_pop(L, count); /* L: args */
    }

    bool argumentException = call.getEnv()->ExceptionCheck() == JNI_TRUE;
    bool success = false;
    if (argumentException)
    {
        call.getEnv()->ExceptionDescribe();
        call.getEnv()->ExceptionClear();
    }
    else
        success = args ? call.executeWithArgs(args) : call.execute();
    if (args)
    {
        for (int i = 0; i < count; ++i)
        {
            if (call.argumentTypeAtIndex(i) == TypeString && args[i].l)
                call.getEnv()->DeleteLocalRef(args[i].l);
        }
        delete[] args;
    }
    if (argumentException)
    {
        // No Java call ran, so none of the newly retained callbacks was transferred.
        for (int functionId : retainedFunctions)
            releaseLuaFunctionById(functionId);
        lua_pushboolean(L, 0);
        lua_pushinteger(L, LUAJ_ERR_EXCEPTION_OCCURRED);
        return 2;
    }

    if (!success)
    {
        LOGD("LuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") EXECUTE FAILURE, ERROR CODE: %d",
             className, methodName, methodSig, call.getErrorCode());

        lua_pushboolean(L, 0);
        lua_pushinteger(L, call.getErrorCode());
        return 2;
    }

    LOGD("LuaJavaBridge::callJavaStaticMethod(\"%s\", \"%s\", args, \"%s\") SUCCESS", className, methodName, methodSig);

    lua_pushboolean(L, 1);
    return 1 + call.pushReturnValue(L);
}

// increase lua function reference counter, return counter
int LuaJavaBridge::retainLuaFunctionById(int functionId)
{
    lua_State* L = s_luaState;
    if (!L)
        return 0;

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN); /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);        /* L: id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }

    // get counter
    lua_pushinteger(L, functionId); /* L: id_r id */
    lua_rawget(L, -2);              /* L: id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 2);
        return 0;
    }

    // increase counter
    int retainCount = lua_tonumber(L, -1);
    retainCount++;
    lua_pop(L, 1);                   /* L: id_r */
    lua_pushinteger(L, functionId);  /* L: id_r id */
    lua_pushinteger(L, retainCount); /* L: id_r id r */
    lua_rawset(L, -3);               /* id_r[id] = r, L: id_r */
    lua_pop(L, 1);

    LOGD("luajretainLuaFunctionById(%d) - retain count = %d", functionId, retainCount);

    return retainCount;
}

// decrease lua function reference counter, return counter
int LuaJavaBridge::releaseLuaFunctionById(int functionId)
{
    lua_State* L = s_luaState;
    if (!L)
        return 0;
    /* L: */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION); /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);          /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        LOGD("%s", "luajreleaseLuaFunctionById() - LUAJ_REGISTRY_FUNCTION not exists");
        return 0;
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN); /* L: f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);        /* L: f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 2);
        LOGD("%s", "luajreleaseLuaFunctionById() - LUAJ_REGISTRY_RETAIN not exists");
        return 0;
    }

    lua_pushinteger(L, functionId); /* L: f_id id_r id */
    lua_rawget(L, -2);              /* L: f_id id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 3);
        LOGD("luajreleaseLuaFunctionById() - function id %d not found", functionId);
        return 0;
    }

    int retainCount = lua_tonumber(L, -1);
    retainCount--;

    if (retainCount > 0)
    {
        // update counter
        lua_pop(L, 1);                   /* L: f_id id_r */
        lua_pushinteger(L, functionId);  /* L: f_id id_r id */
        lua_pushinteger(L, retainCount); /* L: f_id id_r id r */
        lua_rawset(L, -3);               /* id_r[id] = r, L: f_id id_r */
        lua_pop(L, 2);
        LOGD("luajreleaseLuaFunctionById() - function id %d retain count = %d", functionId, retainCount);
        return retainCount;
    }

    // remove lua function reference
    lua_pop(L, 1);                  /* L: f_id id_r */
    lua_pushinteger(L, functionId); /* L: f_id id_r id */
    lua_pushnil(L);                 /* L: f_id id_r id nil */
    lua_rawset(L, -3);              /* id_r[id] = nil, L: f_id id_r */

    lua_pop(L, 1);               /* L: f_id */
    lua_pushnil(L);              /* L: f_id nil */
    while (lua_next(L, -2) != 0) /* L: f_id f id */
    {
        int value = lua_tonumber(L, -1);
        lua_pop(L, 1); /* L: f_id f */
        if (value == functionId)
        {
            lua_pushnil(L);    /* L: f_id f nil */
            lua_rawset(L, -3); /* f_id[f] = nil, L: f_id */
            break;
        }
    } /* L: f_id */

    lua_pop(L, 1);
    LOGD("luajreleaseLuaFunctionById() - function id %d released", functionId);
    return 0;
}

int LuaJavaBridge::callLuaFunctionById(int functionId, const char* arg)
{
    return protectedBridgeCallback(s_luaState, [&]() -> int {
        lua_State* L = s_luaState;
        int top      = lua_gettop(L);
        /* L: */
        lua_pushstring(L, LUAJ_REGISTRY_FUNCTION); /* L: key */
        lua_rawget(L, LUA_REGISTRYINDEX);          /* L: f_id */
        if (!lua_istable(L, -1))
        {
            lua_pop(L, 1);
            return -1;
        }

        lua_pushnil(L);              /* L: f_id nil */
        while (lua_next(L, -2) != 0) /* L: f_id f id */
        {
            int value = lua_tonumber(L, -1);
            lua_pop(L, 1); /* L: f_id f */
            if (value == functionId)
            {
                lua_pushstring(L, arg);         /* L: f_id f arg */
                int ok = lua_pcall(L, 1, 1, 0); /* L: f_id ret|err */
                int ret;
                if (ok == 0)
                {
                    ret = lua_tonumber(L, -1);
                }
                else
                {
                    ret = -ok;
                }

                lua_settop(L, top);
                return ret;
            }
        } /* L: f_id */

        lua_settop(L, top);
        return -1;
    });
}

// call lua global function
int LuaJavaBridge::callLuaGlobalFunction(const char* functionName, const char* arg)
{
    return protectedBridgeCallback(s_luaState, [&]() -> int {
        lua_State* L = s_luaState;

        int ret = -1;
        int top = lua_gettop(L);

        lua_getglobal(L, functionName);
        if (lua_isfunction(L, -1))
        {
            lua_pushstring(L, arg);
            int ok = lua_pcall(L, 1, 1, 0);
            if (ok == 0)
            {
                ret = lua_tonumber(L, -1);
            }
            else
            {
                ret = -ok;
            }
        }

        lua_settop(L, top);
        return ret;
    });
}

// ----------------------------------------

// increase lua function reference counter, return functionId
int LuaJavaBridge::retainLuaFunction(lua_State* L, int functionIndex, int* retainCountReturn)
{
    /* L: f ... */
    lua_pushstring(L, LUAJ_REGISTRY_FUNCTION); /* L: f ... key */
    lua_rawget(L, LUA_REGISTRYINDEX);          /* L: f ... f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_FUNCTION);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    lua_pushstring(L, LUAJ_REGISTRY_RETAIN); /* L: f ... f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);        /* L: f ... f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUAJ_REGISTRY_RETAIN);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }

    // get function id
    lua_pushvalue(L, functionIndex - 2); /* L: f ... f_id id_r f */
    lua_rawget(L, -3);                   /* L: f ... f_id id_r id */

    int functionId;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, create new id
        lua_pop(L, 1); /* L: f ... f_id id_r */
        s_newFunctionId++;
        functionId = s_newFunctionId;

        lua_pushvalue(L, functionIndex - 2); /* L: f ... f_id id_r f */
        lua_pushinteger(L, functionId);      /* L: f ... f_id id_r f id */
        lua_rawset(L, -4);                   /* f_id[f] = id, L: f ... f_id id_r */
        lua_pushinteger(L, functionId);      /* L: f ... f_id id_r id */
    }
    else
    {
        functionId = lua_tonumber(L, -1);
    }

    // get function retain
    lua_pushvalue(L, -1); /* L: f ... f_id id_r id id */
    lua_rawget(L, -3);    /* L: f ... f_id id_r id r */
    int retainCount = 1;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, set retain count = 1
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }
    else
    {
        // add retain count
        retainCount = lua_tonumber(L, -1);
        retainCount++;
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }

    lua_rawset(L, -3); /* id_r[id] = r, L: f ... f_id id_r */
    lua_pop(L, 2);     /* L: f ... */

    if (retainCountReturn)
        *retainCountReturn = retainCount;
    return functionId;
}

int LuaJavaBridge::fetchArrayElements(lua_State* L, int index)
{
    int count = 0;
    do
    {
        lua_rawgeti(L, index - count, count + 1);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            break;
        }
        ++count;
    } while (1);
    return count;
}
#endif
