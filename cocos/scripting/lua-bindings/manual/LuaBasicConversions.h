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
#ifndef __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
#define __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__

#include <unordered_map>
#include <string>

#include <stdint.h>

#include "scripting/lua-bindings/manual/tolua_fix.h"

#include "scripting/lua-bindings/manual/Lua-BindingsExport.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "3d/CCBundle3D.h"
#include "base/CCValue.h"
#include "base/ccTypes.h"
#include "physics/CCPhysicsContact.h"
#include "physics/CCPhysicsJoint.h"
#include "physics/CCPhysicsShape.h"
#include "physics/CCPhysicsWorld.h"
#include "renderer/backend/Types.h"
#include "renderer/backend/VertexLayout.h"
#include "ui/GUIDefine.h"

#include <string_view>
#include <thread>

USING_NS_CC;

extern std::unordered_map<uintptr_t, const char*> g_luaType;
extern std::unordered_map<std::string, const char*> g_typeCast;

#if CC_DEBUG >= 1
void luaval_to_native_err(lua_State* L, const char* msg, tolua_Error* err, const char* funcName = "");
#endif

#define LUA_PRECONDITION(condition, ...)                                                               \
    if (!(condition))                                                                                  \
    {                                                                                                  \
        cocos2d::log("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__); \
        cocos2d::log(__VA_ARGS__);                                                                     \
    }

/**
 * @addtogroup lua
 * @{
 */

/**
 * If the typename of userdata at the given acceptable index of stack is equal to type it return true, otherwise return
 * false. If def != 0, lo could greater than the top index of stack, return value is true. If the value of the given
 * index is nil, return value also is true.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param type the typename used to judge.
 * @param def whether has default value.
 * @return Return true if the typename of userdata at the given acceptable index of stack is equal to type, otherwise
 * return false.
 */
extern bool luaval_is_usertype(lua_State* L, int lo, const char* type, int def);
// to native

/**
 * @name luaval_to_native
 * The following function are all used to convert the Lua values at the given acceptable index to the corresponding c++
 *values. If the Lua values can be converted the return value is true, otherwise return false. If it happens error
 *during the conversion process, it outputs the error msg in the console to provide information about the name of
 *calling function, the typename of value at the given acceptable index, and so on.
 * @{
 **/

/**
 * Get a float value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the float value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_float(lua_State* L, int lo, float* outValue, const char* funcName = "");

/**
 * Get a int value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the int value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_int32(lua_State* L, int lo, int* outValue, const char* funcName = "");

/**
 * Get a unsigned int value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the unsigned int value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName = "");

/**
 * Get a uint16_t value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the uint16_t value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_uint16(lua_State* L, int lo, uint16_t* outValue, const char* funcName = "");

/**
 * Get a boolean value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack has type boolean it returns true, otherwise returns false.
 * Any Lua value is different from false and nil, the value of conversion is true, otherwise the value is false.
 * If the lo is non-valid index, the value of conversion also is false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the boolean value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern CC_LUA_DLL bool luaval_to_boolean(lua_State* L, int lo, bool* outValue, const char* funcName = "");

/**
 * Get a double value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the double value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_number(lua_State* L, int lo, double* outValue, const char* funcName = "");

/**
 * Get a std::string value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a string or a number convertible to a string it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store std::string value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a string or a number convertible to a
 * string, otherwise return false.
 */
extern CC_LUA_DLL bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName = "");
/**
 * Get a ssize_t value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a number or a string convertible to a number it returns true,
 * otherwise returns false.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to store the ssize_t value converted from the Lua value.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a number or a string convertible to a
 * number, otherwise return false.
 */
extern bool luaval_to_ssize_t(lua_State* L, int lo, ssize_t* outValue, const char* funcName = "");

/**
 * Get a Color4B object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `r`,`g`, `b` and 'a' keys and the corresponding values are not nil, this function would assign
 * the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a Color4B object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_color4b(lua_State* L, int lo, Color4B* outValue, const char* funcName = "");

/**
 * Get a Mat object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * The table is array-table which begin the index starts at 1.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a Mat object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_mat4(lua_State* L, int lo, cocos2d::Mat4* outValue, const char* funcName = "");

/**
 * Get a cocos2d::ValueVector object value by the argc numbers of Lua values in the stack.
 *
 * @param L the current lua_State.
 * @param argc the numbers of Lua values in the stack.
 * @param ret the pointer to a ValueVector object which stores the values from the Lua table.
 * @return Return false if argc equal to 0 or L equal to nullptr, otherwise return true.
 */
extern bool luavals_variadic_to_ccvaluevector(lua_State* L, int argc, cocos2d::ValueVector* ret);

/**
 * Get a Vec2 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`,and 'y' keys and the corresponding values are not nil, this function would assign the values
 * to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a Vec2 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec2(lua_State* L, int lo, cocos2d::Vec2* outValue, const char* funcName = "");

/**
 * Get a Vec3 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y' and `z` keys and the corresponding values are not nil, this function would assign the
 * values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a Vec3 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec3(lua_State* L, int lo, cocos2d::Vec3* outValue, const char* funcName = "");

/**
 * Get a Vec4 object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, 'y', `z` and `w` keys and the corresponding values are not nil, this function would assign
 * the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a Vec4 object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_vec4(lua_State* L, int lo, cocos2d::Vec4* outValue, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<std::string> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<std::string>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
CC_LUA_DLL bool luaval_to_std_vector_string(lua_State* L,
                                            int lo,
                                            std::vector<std::string>* ret,
                                            const char* funcName = "");

/**
 * Get a pointer points to a std::vector<std::int> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<int>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName = "");

/**
 * Get a cocos2d::ValueMap object from the given acceptable index of stack.
 * The type of Lua value at the index should be a Lua table.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a cocos2d::ValueMap object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 */
extern bool luaval_to_ccvaluemap(lua_State* L, int lo, cocos2d::ValueMap* ret, const char* funcName = "");

/**
 * Get a cocos2d::ValueVector object from the given acceptable index of stack.
 * The type of Lua value at the index should be a Lua array table.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a cocos2d::ValueVector object.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the type of Lua value at the index is a Lua table, otherwise return false.
 */
extern bool luaval_to_ccvaluevector(lua_State* L, int lo, cocos2d::ValueVector* ret, const char* funcName = "");

/**
 * Get a Type T object from the given acceptable index of stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param type a string pointer points to the type name.
 * @param ret the pointer points to a Type T object.
 * @return Return true if the type of Lua value at the index is a Lua userdata, otherwise return false.
 */
template <class T>
bool luaval_to_object(lua_State* L, int lo, const char* type, T** ret, const char* funcName = "")
{
    if (nullptr == L || lua_gettop(L) < lo)
        return false;

    if (!luaval_is_usertype(L, lo, type, 0))
        return false;

    *ret = static_cast<T*>(tolua_tousertype(L, lo, 0));

    if (nullptr == *ret)
        CCLOG("Warning: %s argument %d is invalid native object(nullptr)", funcName, lo);

    return true;
}

/**
 * Get a pointer points to a std::vector<float> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<float>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<unsigned shortt> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<unsigned short>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_ushort(lua_State* L,
                                        int lo,
                                        std::vector<unsigned short>* ret,
                                        const char* funcName = "");

/**
 * Get a cocos2d::Quaternion object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `x`, `y`, `z` and `w` keys and the corresponding values are not nil, this function would assign
 * the values to the corresponding members of outValue.Otherwise, the value of members of outValue would be 0.
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param outValue the pointer to a cocos2d::Quaternion object which stores the values from the Lua table.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_quaternion(lua_State* L, int lo, cocos2d::Quaternion* outValue, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<cocos2d::Vec2> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<cocos2d::Vec2>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_vec2(lua_State* L, int lo, std::vector<cocos2d::Vec2>* ret, const char* funcName = "");

/**
 * Get a pointer points to a std::vector<cocos2d::Vec3> from a Lua array table in the stack.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index of stack.
 * @param ret a pointer points to a std::vector<cocos2d::Vec3>.
 * @param funcName the name of calling function, it is used for error output in the debug model.
 * @return Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 */
extern bool luaval_to_std_vector_vec3(lua_State* L, int lo, std::vector<cocos2d::Vec3>* ret, const char* funcName = "");

/**@}**/

// from native

/**
 * @name native_to_luaval
 * The following function are all used to convert native c++ values to the corresponding Lua values, then push it into
 *the Lua stack.
 *
 * @{
 **/

/**
 * Push a table converted from a cocos2d::Vec2 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2}
 *
 * @param L the current lua_State.
 * @param vec2  a cocos2d::Vec2 object.
 */
extern int vec2_to_luaval(lua_State* L, const cocos2d::Vec2& vec2);

/**
 * Push a table converted from a cocos2d::Vec3 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3}
 *
 * @param L the current lua_State.
 * @param vec3  a cocos2d::Vec3 object.
 */
extern int vec3_to_luaval(lua_State* L, const cocos2d::Vec3& vec3);

/**
 * Push a table converted from a cocos2d::Vec4 object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @param L the current lua_State.
 * @param vec4  a cocos2d::Vec4 object.
 */
extern int vec4_to_luaval(lua_State* L, const cocos2d::Vec4& vec4);

/**
 * Push a table converted from a cocos2d::Mat4 object into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberValue16}
 *
 * @param L the current lua_State.
 * @param mat a cocos2d::Mat4 object.
 */
extern void mat4_to_luaval(lua_State* L, const cocos2d::Mat4& mat);

/**
 * Get the real typename for the specified typename.
 * Because all override functions wouldn't be bound,so we must use `typeid` to get the real class name.
 *
 * @param ret the pointer points to a type T object.
 * @param type the string pointer points to specified typename.
 * @return return the pointer points to the real typename, or nullptr.
 */
template <class T>
const char* getLuaTypeName(T* ret, const char* defaultTypeName)
{
    if (nullptr != ret)
    {
        auto typeName = typeid(*ret).name();
        auto iter     = g_luaType.find(reinterpret_cast<uintptr_t>(typeName));
        if (g_luaType.end() != iter)
        {
            return iter->second;
        }
        else
        {  // unlike logic, for windows dll only
            decltype(g_typeCast)::key_type strkey(typeName);
            auto iter2 = g_typeCast.find(strkey);
            if (iter2 != g_typeCast.end())
            {
                g_luaType.emplace(reinterpret_cast<uintptr_t>(typeName), iter2->second);
                return iter2->second;
            }
            return defaultTypeName;
        }
    }

    return nullptr;
}

/**@}**/

/**
 * Push the native object by userdata format into the Lua stack by typename.
 *
 * @param L the current lua_State.
 * @param type the string pointer points to the typename.
 * @param ret the native object pointer.
 */
template <class T>
void object_to_luaval(lua_State* L, const char* type, T* ret)
{
    if (nullptr != ret)
    {
        if (std::is_base_of<cocos2d::Ref, T>::value)
        {
            // use c style cast, T may not polymorphic
            cocos2d::Ref* dynObject = (cocos2d::Ref*)(ret);
            int ID                  = (int)(dynObject->_ID);
            int* luaID              = &(dynObject->_luaID);
            toluafix_pushusertype_ccobject(L, ID, luaID, (void*)ret, type);
        }
        else
        {
            tolua_pushusertype(L, (void*)ret, getLuaTypeName(ret, type));
        }
    }
    else
    {
        lua_pushnil(L);
    }
}

/**
 * Push a Lua array table converted from a std::vector<int> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<int> value.
 */
void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue);

/**
 * Push a Lua array table converted from a std::vector<float> into the Lua stack.
 * The format of table as follows: {numberValue1, numberValue2, ..., numberVectorSize}
 *
 * @param L the current lua_State.
 * @param inValue a std::vector<float> value.
 */
void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue);

/**
 * Push a table converted from a cocos2d::Quaternion object into the Lua stack.
 * The format of table as follows: {x=numberValue1, y=numberValue2, z=numberValue3, w=numberValue4}
 *
 * @param L the current lua_State.
 * @param inValue a cocos2d::Quaternion object.
 */
void quaternion_to_luaval(lua_State* L, const cocos2d::Quaternion& inValue);

// end group
/// @}
#endif  //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
