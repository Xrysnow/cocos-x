/****************************************************************************
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

#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "base/ccUtils.h"
#include <sstream>

std::unordered_map<uintptr_t, const char*> g_luaType;
std::unordered_map<std::string, const char*> g_typeCast;

#ifdef tolua_iscppstring
#undef tolua_iscppstring
int tolua_iscppstring(lua_State* L, int lo, int def, tolua_Error* err)
{
    if (def && lua_gettop(L) < abs(lo))
        return 1;
    if (lua_isstring(L, lo))
        return 1;
    err->index = lo;
    err->array = 0;
    err->type = "string";
    return 0;
}
#endif

#if CC_DEBUG >= 1
void luaval_to_native_err(lua_State* L, const char* msg, tolua_Error* err, const char* funcName)
{
    if (NULL == L || NULL == err || NULL == msg || 0 == strlen(msg))
        return;

    if (msg[0] == '#')
    {
        const char* expected = err->type;
        const char* provided = tolua_typename(L, err->index);
        if (msg[1] == 'f')
        {
            int narg = err->index;
            if (err->array)
                CCLOG("%s\n     %s argument #%d is array of '%s'; array of '%s' expected.\n", msg + 2, funcName, narg,
                      provided, expected);
            else
                CCLOG("%s\n     %s argument #%d is '%s'; '%s' expected.\n", msg + 2, funcName, narg, provided,
                      expected);
        }
        else if (msg[1] == 'v')
        {
            if (err->array)
                CCLOG("%s\n     %s value is array of '%s'; array of '%s' expected.\n", funcName, msg + 2, provided,
                      expected);
            else
                CCLOG("%s\n     %s value is '%s'; '%s' expected.\n", msg + 2, funcName, provided, expected);
        }
    }
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int lua_isusertype(lua_State* L, int lo, const char* type);
#ifdef __cplusplus
}
#endif

bool luaval_is_usertype(lua_State* L, int lo, const char* type, int def)
{
    if (def && lua_gettop(L) < std::abs(lo))
        return true;

    if (lua_isnil(L, lo) || lua_isusertype(L, lo, type))
        return true;

    return false;
}

bool luaval_to_float(lua_State* L, int lo, float* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (float)lua_tonumber(L, lo);
    }

    return ok;
}

bool luaval_to_int32(lua_State* L, int lo, int* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        /**
         When we want to convert the number value from the Lua to int, we would call lua_tonumber to implement.It would
         experience two phase conversion: int -> double, double->int.But,for the 0x80000000 which the min value of int,
         the int cast may return an undefined result,like 0x7fffffff.So we must use the (int)(unsigned
         int)lua_tonumber() to get predictable results for 0x80000000.In this place,we didn't use lua_tointeger, because
         it may produce different results depending on the compiler,e.g:for iPhone4s,it also get wrong value for
         0x80000000.
         */
        unsigned int estimateValue = (unsigned int)lua_tonumber(L, lo);
        if (estimateValue == std::numeric_limits<int>::min())
        {
            *outValue = (int)estimateValue;
        }
        else
        {
            *outValue = (int)lua_tonumber(L, lo);
        }
    }

    return ok;
}

bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (unsigned int)tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_uint16(lua_State* L, int lo, uint16_t* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (unsigned char)tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_boolean(lua_State* L, int lo, bool* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isboolean(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (bool)tolua_toboolean(L, lo, 0);
    }

    return ok;
}

bool luaval_to_number(lua_State* L, int lo, double* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = tolua_tonumber(L, lo, 0);
    }

    return ok;
}

bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_iscppstring(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t size;
        auto rawString = lua_tolstring(L, lo, &size);
        *outValue      = std::string(rawString, size);
    }

    return ok;
}

bool luaval_to_vec2(lua_State* L, int lo, cocos2d::Vec2* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    // assertion: since we only have vec2, you should never passing rect as vec2 to native
    const auto objlen = lua_objlen(L, lo);
    assert(objlen != 4);

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            lua_pushstring(L, "width");
            lua_gettable(L, lo);
        }

        outValue->x = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            lua_pushstring(L, "height");
            lua_gettable(L, lo);
        }

        outValue->y = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_vec3(lua_State* L, int lo, cocos2d::Vec3* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, lo);
        outValue->z = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_vec4(lua_State* L, int lo, cocos2d::Vec4* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, lo);
        outValue->z = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "w");
        lua_gettable(L, lo);
        outValue->w = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_ssize_t(lua_State* L, int lo, ssize_t* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        *outValue = (ssize_t)tolua_tointeger(L, lo, 0);
    }

    return ok;
}

bool luaval_to_color4b(lua_State* L, int lo, Color4B* outValue, const char* funcName)
{
    if (NULL == L || NULL == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L, lo);
        outValue->r = lua_isnil(L, -1) ? 0 : static_cast<uint8_t>(lua_tonumber(L, -1));
        lua_pop(L, 1);

        lua_pushstring(L, "g");
        lua_gettable(L, lo);
        outValue->g = lua_isnil(L, -1) ? 0 : static_cast<uint8_t>(lua_tonumber(L, -1));
        lua_pop(L, 1);

        lua_pushstring(L, "b");
        lua_gettable(L, lo);
        outValue->b = lua_isnil(L, -1) ? 0 : static_cast<uint8_t>(lua_tonumber(L, -1));
        lua_pop(L, 1);

        lua_pushstring(L, "a");
        lua_gettable(L, lo);
        outValue->a = lua_isnil(L, -1) ? 255 : static_cast<uint8_t>(lua_tonumber(L, -1));
        lua_pop(L, 1);
    }

    return ok;
}

bool luaval_to_mat4(lua_State* L, int lo, cocos2d::Mat4* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
        ok = false;
#endif
    }

    if (ok)
    {
        do
        {
            size_t len = lua_objlen(L, lo);
            if (len != 16)
            {
                ok = false;
                break;
            }
            for (size_t i = 0; i < len; i++)
            {
                lua_pushnumber(L, i + 1);
                lua_gettable(L, lo);
                if (tolua_isnumber(L, -1, 0, &tolua_err))
                {
                    outValue->m[i] = (float)tolua_tonumber(L, -1, 0);
                }
                else
                {
                    outValue->m[i] = 0;
                }
                lua_pop(L, 1);
            }
        } while (0);
    }

    return ok;
}

bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret)
{
    if (nullptr == L || argc == 0)
        return false;

    for (int i = 0; i < argc; i++)
    {
        if (lua_istable(L, i + 2))
        {
            lua_pushnumber(L, 1);
            lua_gettable(L, i + 2);
            if (lua_isnil(L, -1))
            {
                lua_pop(L, 1);
                ValueMap dictVal;
                if (luaval_to_ccvaluemap(L, i + 2, &dictVal))
                {
                    ret->emplace_back(Value(dictVal));
                }
            }
            else
            {
                lua_pop(L, 1);
                ValueVector arrVal;
                if (luaval_to_ccvaluevector(L, i + 2, &arrVal))
                {
                    ret->emplace_back(Value(arrVal));
                }
            }
        }
        else if (lua_type(L, i + 2) == LUA_TSTRING)
        {
            std::string stringValue = "";
            if (luaval_to_std_string(L, i + 2, &stringValue))
            {
                ret->emplace_back(Value(stringValue));
            }
        }
        else if (lua_isboolean(L, i + 2))
        {
            bool boolVal = false;
            if (luaval_to_boolean(L, i + 2, &boolVal))
            {
                ret->emplace_back(Value(boolVal));
            }
        }
        else if (lua_type(L, i + 2) == LUA_TNUMBER)
        {
            ret->emplace_back(Value(tolua_tonumber(L, i + 2, 0)));
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
    }

    return true;
}

bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        std::string stringKey   = "";
        std::string stringValue = "";
        bool boolVal            = false;
        ValueMap& dict          = *ret;
        lua_pushnil(L);              /* first key L: lotable ..... nil */
        while (0 != lua_next(L, lo)) /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1); /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }

            if (luaval_to_std_string(L, -2, &stringKey))
            {

                if (lua_istable(L, -1))
                {
                    lua_pushnumber(L, 1);
                    lua_gettable(L, -2);

                    if (lua_isnil(L, -1)) /** if table[1] = nil,we don't think it is a pure array */
                    {
                        lua_pop(L, 1);
                        ValueMap dictVal;
                        if (luaval_to_ccvaluemap(L, lua_gettop(L), &dictVal))
                        {
                            dict[stringKey] = Value(dictVal);
                        }
                    }
                    else
                    {
                        lua_pop(L, 1);
                        ValueVector arrVal;
                        if (luaval_to_ccvaluevector(L, lua_gettop(L), &arrVal))
                        {
                            dict[stringKey] = Value(arrVal);
                        }
                    }
                }
                else if (lua_type(L, -1) == LUA_TSTRING)
                {
                    if (luaval_to_std_string(L, -1, &stringValue))
                    {
                        dict[stringKey] = Value(stringValue);
                    }
                }
                else if (lua_type(L, -1) == LUA_TBOOLEAN)
                {
                    if (luaval_to_boolean(L, -1, &boolVal))
                    {
                        dict[stringKey] = Value(boolVal);
                    }
                }
                else if (lua_type(L, -1) == LUA_TNUMBER)
                {
                    dict[stringKey] = Value(tolua_tonumber(L, -1, 0));
                }
                else
                {
                    CCASSERT(false, "not supported type");
                }
            }

            lua_pop(L, 1); /* L: lotable ..... key */
        }
    }

    return ok;
}
bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isnil(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }

            if (lua_istable(L, -1))
            {
                lua_pushnumber(L, 1);
                lua_gettable(L, -2);
                if (lua_isnil(L, -1))
                {
                    lua_pop(L, 1);
                    ValueMap dictVal;
                    if (luaval_to_ccvaluemap(L, lua_gettop(L), &dictVal))
                    {
                        ret->emplace_back(Value(dictVal));
                    }
                }
                else
                {
                    lua_pop(L, 1);
                    ValueVector arrVal;
                    if (luaval_to_ccvaluevector(L, lua_gettop(L), &arrVal))
                    {
                        ret->emplace_back(Value(arrVal));
                    }
                }
            }
            else if (lua_type(L, -1) == LUA_TSTRING)
            {
                std::string stringValue = "";
                if (luaval_to_std_string(L, -1, &stringValue))
                {
                    ret->emplace_back(Value(stringValue));
                }
            }
            else if (lua_type(L, -1) == LUA_TBOOLEAN)
            {
                bool boolVal = false;
                if (luaval_to_boolean(L, -1, &boolVal))
                {
                    ret->emplace_back(Value(boolVal));
                }
            }
            else if (lua_type(L, -1) == LUA_TNUMBER)
            {
                ret->emplace_back(Value(tolua_tonumber(L, -1, 0)));
            }
            else
            {
                CCASSERT(false, "not supported type");
            }
            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len        = lua_objlen(L, lo);
        std::string value = "";
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isstring(L, -1))
            {
                ok = luaval_to_std_string(L, -1, &value);
                if (ok)
                    ret->emplace_back(value);
            }
            else
            {
                CCASSERT(false, "string type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isnumber(L, -1))
            {
                ret->emplace_back((int)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCASSERT(false, "int type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isnumber(L, -1))
            {
                ret->emplace_back((float)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCASSERT(false, "float type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_isnumber(L, -1))
            {
                ret->emplace_back((unsigned short)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCASSERT(false, "unsigned short type is needed");
            }

            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_quaternion(lua_State* L, int lo, cocos2d::Quaternion* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "z");
        lua_gettable(L, lo);
        outValue->z = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "w");
        lua_gettable(L, lo);
        outValue->w = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_std_vector_vec2(lua_State* L, int lo, std::vector<cocos2d::Vec2>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        cocos2d::Vec2 value;
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_istable(L, lua_gettop(L)))
            {
                ok &= luaval_to_vec2(L, lua_gettop(L), &value);
                if (ok)
                {
                    ret->emplace_back(value);
                }
            }
            else
            {
                CCASSERT(false, "vec2 type is needed");
            }
            lua_pop(L, 1);
        }
    }

    return ok;
}

bool luaval_to_std_vector_vec3(lua_State* L, int lo, std::vector<cocos2d::Vec3>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;

    tolua_Error tolua_err;
    bool ok = true;

    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }

    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        cocos2d::Vec3 value;
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if (lua_istable(L, lua_gettop(L)))
            {
                ok &= luaval_to_vec3(L, lua_gettop(L), &value);
                if (ok)
                {
                    ret->emplace_back(value);
                }
            }
            else
            {
                CCASSERT(false, "vec3 type is needed");
            }
            lua_pop(L, 1);
        }
    }

    return ok;
}

static int vec2_index(lua_State* L)
{  // t k
    const char signature = lua_tostring(L, 2)[0];
    int n                = 0;
    if (signature == 'x' || signature == 'w' || signature == 'u')
    {
        lua_pop(L, 1);  // pop the string key
        n = 1;
    }
    else if (signature == 'y' || signature == 'h' || signature == 'v')
    {
        lua_pop(L, 1);  // pop the string key
        n = 2;
    }
    if (n)
        lua_rawgeti(L, -1, n);
    else
        lua_pushnil(L);
    return 1;
}
static int vec2_newindex(lua_State* L)
{  // t k v
    const char signature = lua_tostring(L, 2)[0];
    int n                = 0;
    if (signature == 'x' || signature == 'w' || signature == 'u')
    {
        lua_remove(L, 2);  // remove the string key
        n = 1;
    }
    else if (signature == 'y' || signature == 'h' || signature == 'v')
    {
        lua_remove(L, 2);  // remove the string key
        n = 2;
    }

    if (n)
        lua_rawseti(L, -2, n);

    return 0;
}

int vec2_to_luaval(lua_State* L, const cocos2d::Vec2& vec2)
{
    lua_createtable(L, 2, 0);              /* L: table */
    lua_pushnumber(L, (lua_Number)vec2.x); /* L: table key value*/
    lua_rawseti(L, -2, 1);                 /* table[key] = value, L: table */
    lua_pushnumber(L, (lua_Number)vec2.y); /* L: table key value*/
    lua_rawseti(L, -2, 2);

    int top = lua_gettop(L);
    luaL_getmetatable(L, "_vec2mt");
    if (!lua_istable(L, -1))
    {
        lua_settop(L, top);  // restore stack
        luaL_newmetatable(L, "_vec2mt");
        lua_pushcfunction(L, vec2_index);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, vec2_newindex);
        lua_setfield(L, -2, "__newindex");
    }
    lua_setmetatable(L, -2);

    return 1;
}

static int vec3_index(lua_State* L)
{  // t k
    const char signature = lua_tostring(L, 2)[0];
    assert(signature >= 'x' || signature <= 'z');
    lua_pop(L, 1);  // pop the string key
    const int n = signature - 'x' + 1;
    lua_rawgeti(L, -1, n);
    return 1;
}
static int vec3_newindex(lua_State* L)
{  // t k v
    const char signature = lua_tostring(L, 2)[0];
    assert(signature >= 'x' || signature <= 'z');
    lua_remove(L, 2);  // remove the string key
    const int n = signature - 'x' + 1;
    lua_rawseti(L, -2, n);

    return 0;
}

int vec3_to_luaval(lua_State* L, const cocos2d::Vec3& vec3)
{
    lua_createtable(L, 3, 0);              /* L: table */
    lua_pushnumber(L, (lua_Number)vec3.x); /* L: table key value*/
    lua_rawseti(L, -2, 1);                 /* table[key] = value, L: table */
    lua_pushnumber(L, (lua_Number)vec3.y); /* L: table key value*/
    lua_rawseti(L, -2, 2);
    lua_pushnumber(L, (lua_Number)vec3.z); /* L: table key value*/
    lua_rawseti(L, -2, 3);

    int top = lua_gettop(L);
    luaL_getmetatable(L, "_vec3mt");
    if (!lua_istable(L, -1))
    {
        lua_settop(L, top);  // restore stack
        luaL_newmetatable(L, "_vec3mt");
        lua_pushcfunction(L, vec3_index);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, vec3_newindex);
        lua_setfield(L, -2, "__newindex");
    }
    lua_setmetatable(L, -2);

    return 1;
}

static int vec4_index(lua_State* L)
{  // t k
    const char signature = lua_tostring(L, 2)[0];
    assert(signature >= 'w' || signature <= 'z');
    lua_pop(L, 1);  // pop the string key
    const int n = signature != 'w' ? signature - 'x' + 1 : 4;
    lua_rawgeti(L, -1, n);
    return 1;
}
static int vec4_newindex(lua_State* L)
{  // t k v
    const char signature = lua_tostring(L, 2)[0];
    assert(signature >= 'w' || signature <= 'z');
    lua_remove(L, 2);  // remove the string key
    const int n = signature != 'w' ? signature - 'x' + 1 : 4;
    lua_rawseti(L, -2, n);

    return 0;
}

int vec4_to_luaval(lua_State* L, const cocos2d::Vec4& vec4)
{
    lua_createtable(L, 4, 0);              /* L: table */
    lua_pushnumber(L, (lua_Number)vec4.x); /* L: table key value*/
    lua_rawseti(L, -2, 1);                 /* table[key] = value, L: table */
    lua_pushnumber(L, (lua_Number)vec4.y); /* L: table key value*/
    lua_rawseti(L, -2, 2);
    lua_pushnumber(L, (lua_Number)vec4.z); /* L: table key value*/
    lua_rawseti(L, -2, 3);
    lua_pushnumber(L, (lua_Number)vec4.w); /* L: table key value*/
    lua_rawseti(L, -2, 4);

    int top = lua_gettop(L);
    luaL_getmetatable(L, "_vec4mt");
    if (!lua_istable(L, -1))
    {
        lua_settop(L, top);  // restore stack
        luaL_newmetatable(L, "_vec4mt");
        lua_pushcfunction(L, vec4_index);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, vec4_newindex);
        lua_setfield(L, -2, "__newindex");
    }
    lua_setmetatable(L, -2);

    return 1;
}


void mat4_to_luaval(lua_State* L, const cocos2d::Mat4& mat)
{
    if (nullptr == L)
        return;

    lua_newtable(L); /* L: table */
    int indexTable = 1;

    for (int i = 0; i < 16; i++)
    {
        lua_pushnumber(L, (lua_Number)indexTable);
        lua_pushnumber(L, (lua_Number)mat.m[i]);
        lua_rawset(L, -3);
        ++indexTable;
    }
}

void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue)
{
    if (nullptr == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (const int value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)value);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue)
{
    if (nullptr == L)
        return;

    lua_newtable(L);

    int index = 1;
    for (const float value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)value);
        lua_rawset(L, -3);
        ++index;
    }
}

void quaternion_to_luaval(lua_State* L, const cocos2d::Quaternion& inValue)
{
    if (NULL == L)
        return;

    lua_newtable(L);                          /* L: table */
    lua_pushstring(L, "x");                   /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.x); /* L: table key value*/
    lua_rawset(L, -3);                        /* table[key] = value, L: table */
    lua_pushstring(L, "y");                   /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.y); /* L: table key value*/
    lua_rawset(L, -3);
    lua_pushstring(L, "z");                   /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.z); /* L: table key value*/
    lua_rawset(L, -3);
    lua_pushstring(L, "w");                   /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.w); /* L: table key value*/
    lua_rawset(L, -3);
}
