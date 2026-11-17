/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011 Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

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

#pragma once

// Define this before any standard header can include the CRT math headers.
#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
#endif

#include "platform/CCNamespace.h"
#include "base/ccConfig.h"
// Define the common helper before loading platform compatibility fallbacks.
#ifndef CC_UNUSED_PARAM
    #define CC_UNUSED_PARAM(unusedparam) (void)unusedparam
#endif

#include "platform/CCPlatformDefine.h"

// Retain the foundation header contract for targets without a platform adapter.
#ifndef CC_DLL
    #define CC_DLL
#endif

#ifndef CC_DEBUG
    #define CC_DEBUG 0
#endif

#define COCOS2D_DEBUG CC_DEBUG

#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>

// Preserve the Windows CCStdC fallback when math headers were included earlier.
#ifndef M_PI
    #define M_PI 3.14159265358
#endif
#ifndef M_PI_2
    #define M_PI_2 1.57079632679
#endif

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
    #include <BaseTsd.h>
    #if !defined(__SSIZE_T) && !defined(_SSIZE_T_)
        #define __SSIZE_T
typedef SSIZE_T ssize_t;
        #ifndef _SSIZE_T_
            #define _SSIZE_T_
        #endif
        #ifndef _SSIZE_T_DEFINED
            #define _SSIZE_T_DEFINED
        #endif
    #endif // __SSIZE_T
#endif

#include "Assertf.h"
#include "base/ccRandom.h"

/** @def CC_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#ifndef CC_DEGREES_TO_RADIANS
#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__)*0.01745329252f) // PI / 180
#endif

/** @def CC_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#ifndef CC_RADIANS_TO_DEGREES
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__)*57.29577951f) // PI * 180
#endif

#ifndef FLT_EPSILON
    #define FLT_EPSILON 1.192092896e-07F
#endif // FLT_EPSILON

/**
Helper macros which converts 4-byte little/big endian
integral number to the machine native number representation

It should work same as apples CFSwapInt32LittleToHost(..)
*/

#ifndef CC_HOST_IS_BIG_ENDIAN
/// when define returns true it means that our architecture uses big endian
#define CC_HOST_IS_BIG_ENDIAN           (bool)(*(unsigned short *)"\0\xff" < 0x100)
#define CC_SWAP32(i)                    ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define CC_SWAP16(i)                    ((i & 0x00ff) << 8 | (i & 0xff00) >> 8)
#define CC_SWAP_INT32_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true) ? CC_SWAP32(i) : (i))
#define CC_SWAP_INT16_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true) ? CC_SWAP16(i) : (i))
#define CC_SWAP_INT32_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true) ? (i) : CC_SWAP32(i))
#define CC_SWAP_INT16_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true) ? (i) : CC_SWAP16(i))
#endif

#ifndef CC_CALLBACK_0
// new callbacks based on C++11
#define CC_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define CC_CALLBACK_2(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CC_CALLBACK_3(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
#endif

// Generic macros

#ifndef CC_SAFE_DELETE
#define CC_SAFE_DELETE(p) \
    do {                  \
        delete (p);       \
        (p) = nullptr;    \
    } while (0)
#endif
#ifndef CC_SAFE_DELETE_ARRAY
#define CC_SAFE_DELETE_ARRAY(p) \
    do {                        \
        if (p) {                \
            delete[](p);        \
            (p) = nullptr;      \
        }                       \
    } while (0)
#endif
#ifndef CC_SAFE_FREE
#define CC_SAFE_FREE(p)    \
    do {                   \
        if (p) {           \
            free(p);       \
            (p) = nullptr; \
        }                  \
    } while (0)
#endif
#ifndef CC_SAFE_RELEASE
#define CC_SAFE_RELEASE(p)  \
    do {                    \
        if (p) {            \
            (p)->release(); \
        }                   \
    } while (0)
#endif
#ifndef CC_SAFE_RELEASE_NULL
#define CC_SAFE_RELEASE_NULL(p) \
    do {                        \
        if (p) {                \
            (p)->release();     \
            (p) = nullptr;      \
        }                       \
    } while (0)
#endif
#ifndef CC_SAFE_RETAIN
#define CC_SAFE_RETAIN(p)  \
    do {                   \
        if (p) {           \
            (p)->retain(); \
        }                  \
    } while (0)
#endif
#ifndef CC_BREAK_IF
#define CC_BREAK_IF(cond) \
    if (cond) break
#endif

/** @def CC_DEPRECATED_ATTRIBUTE
 * Only certain compilers support __attribute__((deprecated)).
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 // vs 2005 or higher
    #define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
    #define CC_DEPRECATED_ATTRIBUTE
#endif

/** @def CC_DEPRECATED(...)
 * Macro to mark things deprecated as of a particular version
 * can be used with arbitrary parameters which are thrown away.
 * e.g. CC_DEPRECATED(4.0) or CC_DEPRECATED(4.0, "not going to need this anymore") etc.
 */
#define CC_DEPRECATED(...) CC_DEPRECATED_ATTRIBUTE

#ifdef __GNUC__
    #define CC_UNUSED __attribute__((unused))
#else
    #define CC_UNUSED
#endif

/** @def CC_FORMAT_PRINTF(formatPos, argPos)
 * Only certain compiler support __attribute__((format))
 *
 * @param formatPos 1-based position of format string argument.
 * @param argPos    1-based position of first format-dependent argument.
 */
#if defined(__GNUC__) && (__GNUC__ >= 4)
    #define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
    #if __has_attribute(format)
        #define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
    #else
        #define CC_FORMAT_PRINTF(formatPos, argPos)
    #endif // __has_attribute(format)
#else
    #define CC_FORMAT_PRINTF(formatPos, argPos)
#endif

#if defined(_MSC_VER)
    #define CC_FORMAT_PRINTF_SIZE_T "%08lX"
#else
    #define CC_FORMAT_PRINTF_SIZE_T "%08zX"
#endif

/** @def CC_REQUIRES_NULL_TERMINATION
 *
 */
#if !defined(CC_REQUIRES_NULL_TERMINATION)
    #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
        #define CC_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0, 1)))
    #elif defined(__GNUC__)
        #define CC_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
    #else
        #define CC_REQUIRES_NULL_TERMINATION
    #endif
#endif

// Lightweight logging entry points; the Console class is not needed here.
namespace cc {
void CC_DLL print(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
void CC_DLL log(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
void CC_DLL printWithFunction(const char* function, const char* format, ...) CC_FORMAT_PRINTF(2, 3);
}

#define __CCLOGWITHFUNCTION(...) \
    ::cc::printWithFunction(__FUNCTION__, __VA_ARGS__)

/// @name Cocos2d debug
/// @{
#if !defined(CC_DEBUG) || CC_DEBUG == 0
    #define CCLOG(...)       do {} while (0)
    #define CCLOGINFO(...)   do {} while (0)
    #define CCLOGERROR(...)  do {} while (0)
    #define CCLOGWARN(...)   do {} while (0)

#elif CC_DEBUG == 1
    #define CCLOG(format, ...)      cc::print(format, ##__VA_ARGS__)
    #define CCLOGERROR(format,...)  cc::print(format, ##__VA_ARGS__)
    #define CCLOGINFO(format,...)   do {} while (0)
    #define CCLOGWARN(...) __CCLOGWITHFUNCTION(__VA_ARGS__)

#elif CC_DEBUG > 1
    #define CCLOG(format, ...)      cc::print(format, ##__VA_ARGS__)
    #define CCLOGERROR(format,...)  cc::print(format, ##__VA_ARGS__)
    #define CCLOGINFO(format,...)   cc::print(format, ##__VA_ARGS__)
    #define CCLOGWARN(...) __CCLOGWITHFUNCTION(__VA_ARGS__)
#endif // CC_DEBUG

/** Lua engine debug */
#if !defined(CC_DEBUG) || CC_DEBUG == 0 || CC_LUA_ENGINE_DEBUG == 0
    #define LUALOG(...)
#else
    #define LUALOG(format, ...) cc::print(format, ##__VA_ARGS__)
#endif  // Lua engine debug

//  end of debug group
/// @}

// Factory macro expansion requires base/Ptr.h; the legacy platform header supplies it.
/** @def CREATE_FUNC(__TYPE__)
 * Define a create function for a specific type, such as Layer.
 *
 * @param __TYPE__  class type to add create(), such as Layer.
 */
#define CREATE_FUNC(__TYPE__)                                      \
    static cc::IntrusivePtr<__TYPE__> create()                                      \
    {                                                              \
        cc::IntrusivePtr owner{new __TYPE__()}; \
        if (!owner->init())                                       \
            return nullptr;                                        \
        return owner; \
    }

/** @def NODE_FUNC(__TYPE__)
 * Define a node function for a specific type, such as Layer.
 *
 * @param __TYPE__  class type to add node(), such as Layer.
 * @deprecated  This interface will be deprecated sooner or later.
 */
#define NODE_FUNC(__TYPE__)                                         \
    CC_DEPRECATED_ATTRIBUTE static cc::IntrusivePtr<__TYPE__> node()                 \
    {                                                               \
        cc::IntrusivePtr owner{new __TYPE__()}; \
        if (!owner->init())                                        \
            return nullptr;                                         \
        return owner;  \
    }

/** @def CC_PROPERTY_READONLY
 * It is used to declare a protected variable. We can use getter to read the variable.
 *
 * @param varType     the type of variable.
 * @param varName     variable name.
 * @param funName     "get + funName" will be the name of the getter.
 * @warning   The getter is a public virtual function, you should rewrite it first.
 *            The variables and methods declared after CC_PROPERTY_READONLY are all public.
 *            If you need protected or private, please declare.
 */
#define CC_PROPERTY_READONLY(varType, varName, funName) \
protected:                                              \
    varType varName;                                    \
                                                        \
public:                                                 \
    virtual varType get##funName() const;

#define CC_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName) \
protected:                                                          \
    varType varName;                                                \
                                                                    \
public:                                                             \
    virtual const varType& get##funName() const;

/** @def CC_PROPERTY
 * It is used to declare a protected variable.
 * We can use getter to read the variable, and use the setter to change the variable.
 *
 * @param varType     The type of variable.
 * @param varName     Variable name.
 * @param funName     "get + funName" will be the name of the getter.
 *                    "set + funName" will be the name of the setter.
 * @warning   The getter and setter are public virtual functions, you should rewrite them first.
 *            The variables and methods declared after CC_PROPERTY are all public.
 *            If you need protected or private, please declare.
 */
#define CC_PROPERTY(varType, varName, funName) \
protected:                                     \
    varType varName;                           \
                                               \
public:                                        \
    virtual varType get##funName() const;      \
    virtual void set##funName(varType var);

#define CC_PROPERTY_PASS_BY_REF(varType, varName, funName) \
protected:                                                 \
    varType varName;                                       \
                                                           \
public:                                                    \
    virtual const varType& get##funName() const;           \
    virtual void set##funName(const varType& var);

/** @def CC_SYNTHESIZE_READONLY
 * It is used to declare a protected variable. We can use getter to read the variable.
 *
 * @param varType     The type of variable.
 * @param varName     Variable name.
 * @param funName     "get + funName" will be the name of the getter.
 * @warning   The getter is a public inline function.
 *            The variables and methods declared after CC_SYNTHESIZE_READONLY are all public.
 *            If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE_READONLY(varType, varName, funName) \
protected:                                                \
    varType varName;                                      \
                                                          \
public:                                                   \
    virtual inline varType get##funName() const { return varName; }

#define CC_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName) \
protected:                                                            \
    varType varName;                                                  \
                                                                      \
public:                                                               \
    virtual inline const varType& get##funName() const { return varName; }

/** @def CC_SYNTHESIZE
 * It is used to declare a protected variable.
 * We can use getter to read the variable, and use the setter to change the variable.
 *
 * @param varType     The type of variable.
 * @param varName     Variable name.
 * @param funName     "get + funName" will be the name of the getter.
 *                    "set + funName" will be the name of the setter.
 * @warning   The getter and setter are public inline functions.
 *            The variables and methods declared after CC_SYNTHESIZE are all public.
 *            If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE(varType, varName, funName)                    \
protected:                                                          \
    varType varName;                                                \
                                                                    \
public:                                                             \
    virtual inline varType get##funName() const { return varName; } \
    virtual inline void set##funName(varType var) { varName = var; }

#define CC_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)               \
protected:                                                                 \
    varType varName;                                                       \
                                                                           \
public:                                                                    \
    virtual inline const varType& get##funName() const { return varName; } \
    virtual inline void set##funName(const varType& var) { varName = var; }

#define CC_SYNTHESIZE_RETAIN(varType, varName, funName)             \
private:                                                            \
    varType varName;                                                \
                                                                    \
public:                                                             \
    virtual inline varType get##funName() const { return varName; } \
    virtual inline void set##funName(varType var)                   \
    {                                                               \
        if (varName != var)                                         \
        {                                                           \
            CC_SAFE_RETAIN(var);                                    \
            CC_SAFE_RELEASE(varName);                               \
            varName = var;                                          \
        }                                                           \
    }

#ifndef CCASSERT
    #if CC_DEBUG > 0
        #if CC_ENABLE_SCRIPT_BINDING
extern bool CC_DLL cc_assert_script_compatible(const char* msg);
            #define CCASSERT(cond, msg)                                       \
                do                                                            \
                {                                                             \
                    if (!(cond))                                              \
                    {                                                         \
                        if (msg && *msg && !cc_assert_script_compatible(msg)) \
                            cc::log("Assert failed: %s", msg);           \
                        CC_ASSERT(cond);                                      \
                    }                                                         \
                } while (0)
        #else
            #define CCASSERT(cond, msg) CC_ASSERT(cond)
        #endif
    #else
        #define CCASSERT(cond, msg)
    #endif

#endif  // CCASSERT

#ifndef GP_ASSERT
    #define GP_ASSERT(cond) CCASSERT(cond, "")
#endif
#ifndef CCAssert
    #define CCAssert CCASSERT
#endif

// Initial compiler-related stuff to set.
#define CC_COMPILER_MSVC  1
#define CC_COMPILER_CLANG 2
#define CC_COMPILER_GNUC  3

// CPU Architecture
#define CC_CPU_UNKNOWN 0
#define CC_CPU_X86     1
#define CC_CPU_PPC     2
#define CC_CPU_ARM     3
#define CC_CPU_MIPS    4

// 32-bits or 64-bits CPU
#define CC_CPU_ARCH_32 1
#define CC_CPU_ARCH_64 2

// Endian
#define CC_ENDIAN_LITTLE 1
#define CC_ENDIAN_BIG    2

// Charset
#define CC_CHARSET_UNICODE   1
#define CC_CHARSET_MULTIBYTE 2

// Precision
#define CC_PRECISION_FLOAT  1
#define CC_PRECISION_DOUBLE 2

// Mode
#define CC_MODE_DEBUG   1
#define CC_MODE_RELEASE 2

// Memory Allocator
#define CC_MEMORY_ALLOCATOR_STD        0
#define CC_MEMORY_ALLOCATOR_NEDPOOLING 1
#define CC_MEMORY_ALLOCATOR_JEMALLOC   2

// STL Memory Allocator
#define CC_STL_MEMORY_ALLOCATOR_STANDARD 1
#define CC_STL_MEMORY_ALLOCATOR_CUSTOM   2

// Compiler type and version recognition
#if defined(_MSC_VER)
    #define CC_COMPILER CC_COMPILER_MSVC
#elif defined(__clang__)
    #define CC_COMPILER CC_COMPILER_CLANG
#elif defined(__GNUC__)
    #define CC_COMPILER CC_COMPILER_GNUC
#else
    #error "Unknown compiler. Abort!"
#endif

#if defined(__x86_64__) || defined(_M_X64) || \
    defined(__aarch64__) || defined(_M_ARM64) || \
    defined(__powerpc64__) || defined(__mips64) || \
    defined(__LP64__) || defined(_LP64)
    #define CC_CPU_ARCH CC_CPU_ARCH_64
#else
    #define CC_CPU_ARCH CC_CPU_ARCH_32
#endif

#if defined(__arm64__) || defined(__aarch64__)
    #define CC_ARCH_ARM64 1
#else
    #define CC_ARCH_ARM64 0
#endif

// CC_HAS_ARM64_FP16 set to 1 if the architecture provides an IEEE compliant ARM fp16 type
#if CC_ARCH_ARM64
    #ifndef CC_HAS_ARM64_FP16
        #if defined(__ARM_FP16_FORMAT_IEEE)
            #define CC_HAS_ARM64_FP16 1
        #else
            #define CC_HAS_ARM64_FP16 0
        #endif
    #endif
#endif

// CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC set to 1 if the architecture supports Neon vector intrinsics for fp16.
#if CC_ARCH_ARM64
    #ifndef CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC
        #if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
            #define CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC 1
        #else
            #define CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC 0
        #endif
    #endif
#endif

// CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC set to 1 if the architecture supports Neon scalar intrinsics for fp16.
#if CC_ARCH_ARM64
    #ifndef CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC
        #if defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
            #define CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC 1
        #else
            #define CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC 0
        #endif
    #endif
#endif

// Disable MSVC warning
#if (CC_COMPILER == CC_COMPILER_MSVC)
    #pragma warning(disable : 4251 4275 4819)
    #ifndef _CRT_SECURE_NO_DEPRECATE
        #define _CRT_SECURE_NO_DEPRECATE
    #endif
    #ifndef _SCL_SECURE_NO_DEPRECATE
        #define _SCL_SECURE_NO_DEPRECATE
    #endif
#endif

#define CC_CACHELINE_SIZE 64

#if (CC_COMPILER == CC_COMPILER_MSVC)
    // MSVC ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS() \
        __pragma(warning(push, 0))

    #define CC_ENABLE_WARNINGS() \
        __pragma(warning(pop))
#elif (CC_COMPILER == CC_COMPILER_GNUC)
    // GCC ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS()                               \
        _Pragma("GCC diagnostic push")                          \
            _Pragma("GCC diagnostic ignored \"-Wall\"")         \
                _Pragma("clang diagnostic ignored \"-Wextra\"") \
                    _Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

    #define CC_ENABLE_WARNINGS() \
        _Pragma("GCC diagnostic pop")
#elif (CC_COMPILER == CC_COMPILER_CLANG)
    // CLANG ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS()                               \
        _Pragma("clang diagnostic push")                        \
            _Pragma("clang diagnostic ignored \"-Wall\"")       \
                _Pragma("clang diagnostic ignored \"-Wextra\"") \
                    _Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

    #define CC_ENABLE_WARNINGS() \
        _Pragma("clang diagnostic pop")
#endif

/** @def CC_DISALLOW_COPY_AND_ASSIGN(TypeName)
 * A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class
 */
#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) || \
    (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
    #define CC_DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&) = delete;       \
        TypeName& operator=(const TypeName&) = delete;
#else
    #define CC_DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&);                \
        TypeName& operator=(const TypeName&);
#endif

/** @def CC_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName)
 * A macro to disallow all the implicit constructors, namely the
 * default constructor, copy constructor and operator= functions.
 *
 * This should be used in the private: declarations for a class
 * that wants to prevent anyone from instantiating it. This is
 * especially useful for classes containing only static methods.
 */
#define CC_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName();                                     \
    CC_DISALLOW_COPY_AND_ASSIGN(TypeName)

#define CC_DISALLOW_ASSIGN(TypeName)                \
    TypeName &operator=(const TypeName &) = delete; \
    TypeName &operator=(TypeName &&) = delete;

#define CC_DISALLOW_COPY_MOVE_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete;       \
    TypeName(TypeName &&) = delete;            \
    CC_DISALLOW_ASSIGN(TypeName)

#if (CC_COMPILER == CC_COMPILER_MSVC)
    #define CC_ALIGN(N)        __declspec(align(N))
    #define CC_CACHE_ALIGN     __declspec(align(CC_CACHELINE_SIZE))
    #define CC_PACKED_ALIGN(N) __declspec(align(N))

    #define CC_ALIGNED_DECL(type, var, alignment) __declspec(align(alignment)) type var

    #define CC_READ_COMPILER_BARRIER()  _ReadBarrier()
    #define CC_WRITE_COMPILER_BARRIER() _WriteBarrier()
    #define CC_COMPILER_BARRIER()       _ReadWriteBarrier()

    #define CC_READ_MEMORY_BARRIER()  MemoryBarrier()
    #define CC_WRITE_MEMORY_BARRIER() MemoryBarrier()
    #define CC_MEMORY_BARRIER()       MemoryBarrier()

    #define CC_CPU_READ_MEMORY_BARRIER() \
        do {                             \
            __asm { lfence}               \
        } while (0)
    #define CC_CPU_WRITE_MEMORY_BARRIER() \
        do {                              \
            __asm { sfence}                \
        } while (0)
    #define CC_CPU_MEMORY_BARRIER() \
        do {                        \
            __asm { mfence}          \
        } while (0)

#elif (CC_COMPILER == CC_COMPILER_GNUC) || (CC_COMPILER == CC_COMPILER_CLANG)
    #define CC_ALIGN(N)        __attribute__((__aligned__((N))))
    #define CC_CACHE_ALIGN     __attribute__((__aligned__((CC_CACHELINE_SIZE))))
    #define CC_PACKED_ALIGN(N) __attribute__((packed, aligned(N)))

    #define CC_ALIGNED_DECL(type, var, alignment) type var __attribute__((__aligned__(alignment)))

    #define CC_READ_COMPILER_BARRIER()        \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_WRITE_COMPILER_BARRIER()       \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_COMPILER_BARRIER()             \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)

    #define CC_READ_MEMORY_BARRIER() \
        do {                         \
            __sync_synchronize();    \
        } while (0)
    #define CC_WRITE_MEMORY_BARRIER() \
        do {                          \
            __sync_synchronize();     \
        } while (0)
    #define CC_MEMORY_BARRIER()   \
        do {                      \
            __sync_synchronize(); \
        } while (0)

    #define CC_CPU_READ_MEMORY_BARRIER()      \
        do {                                  \
            __asm__ __volatile__("lfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_CPU_WRITE_MEMORY_BARRIER()     \
        do {                                  \
            __asm__ __volatile__("sfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_CPU_MEMORY_BARRIER()           \
        do {                                  \
            __asm__ __volatile__("mfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)

#else
    #error "Unsupported compiler!"
#endif

/* Stack-alignment
 If macro __CC_SIMD_ALIGN_STACK defined, means there requests
 special code to ensure stack align to a 16-bytes boundary.

 Note:
 This macro can only guarantee callee stack pointer (esp) align
 to a 16-bytes boundary, but not that for frame pointer (ebp).
 Because most compiler might use frame pointer to access to stack
 variables, so you need to wrap those alignment required functions
 with extra function call.
 */
#if defined(__INTEL_COMPILER)
    // For intel's compiler, simply calling alloca seems to do the right
    // thing. The size of the allocated block seems to be irrelevant.
    #define CC_SIMD_ALIGN_STACK() _alloca(16)
    #define CC_SIMD_ALIGN_ATTRIBUTE

#elif (CC_CPU == CC_CPU_X86) && (CC_COMPILER == CC_COMPILER_GNUC || CC_COMPILER == CC_COMPILER_CLANG) && (CC_CPU_ARCH != CC_CPU_ARCH_64)
    // mark functions with GCC attribute to force stack alignment to 16 bytes
    #define CC_SIMD_ALIGN_ATTRIBUTE __attribute__((force_align_arg_pointer))
#elif (CC_COMPILER == CC_COMPILER_MSVC)
    // Fortunately, MSVC will align the stack automatically
    #define CC_SIMD_ALIGN_ATTRIBUTE
#else
    #define CC_SIMD_ALIGN_ATTRIBUTE
#endif

// mode
#if (defined(_DEBUG) || defined(DEBUG)) && (CC_PLATFORM == CC_PLATFORM_WINDOWS)
    #define CC_MODE CC_MODE_DEBUG
#else
    #define CC_MODE CC_MODE_RELEASE
#endif

#define CC_MEMORY_ALLOCATOR CC_MEMORY_ALLOCATOR_STD

// STL memory allocator
#if (CC_MEMORY_ALLOCATOR == CC_MEMORY_ALLOCATOR_STD)
	#define CC_STL_MEMORY_ALLOCATOR CC_STL_MEMORY_ALLOCATOR_STANDARD
#else
	#define CC_STL_MEMORY_ALLOCATOR CC_STL_MEMORY_ALLOCATOR_CUSTOM
#endif

#define CC_TOSTR(s) #s

#if defined(__GNUC__) && __GNUC__ >= 4
    #define CC_PREDICT_TRUE(x)  __builtin_expect(!!(x), 1)
    #define CC_PREDICT_FALSE(x) __builtin_expect(!!(x), 0)
#else
    #define CC_PREDICT_TRUE(x)  (x)
    #define CC_PREDICT_FALSE(x) (x)
#endif

// compatibility with non-clang compilers...
#ifndef __has_attribute
    #define __has_attribute(x) 0
#endif
#ifndef __has_builtin
    #define __has_builtin(x) 0
#endif

/*
 * helps the compiler's optimizer predicting branches
 */
#if __has_builtin(__builtin_expect)
    #ifdef __cplusplus
        #define UTILS_LIKELY(exp) (__builtin_expect(!!(exp), true))
        #define UTILS_UNLIKELY(exp) (__builtin_expect(!!(exp), false))
    #else
        #define UTILS_LIKELY(exp) (__builtin_expect(!!(exp), 1))
        #define UTILS_UNLIKELY(exp) (__builtin_expect(!!(exp), 0))
    #endif
#else
    #define UTILS_LIKELY(exp) (!!(exp))
    #define UTILS_UNLIKELY(exp) (!!(exp))
#endif

#if defined(_MSC_VER)
    #define CC_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define CC_FORCE_INLINE inline __attribute__((always_inline))
#else
    #if defined(__cplusplus) || defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */
        #define CC_FORCE_INLINE static inline
    #elif
        #define CC_FORCE_INLINE inline
    #endif
#endif

#define CC_HALF_PI (M_PI * 0.5f)

#define CC_DOUBLE_PI (M_PI * 2)

/** @def CCRANDOM_MINUS1_1
 returns a random float between -1 and 1
 */
#define CCRANDOM_MINUS1_1() cc::rand_minus1_1()

/** @def CCRANDOM_0_1
 returns a random float between 0 and 1
 */
#define CCRANDOM_0_1() cc::rand_0_1()

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&)

#define CC_REPEAT_FOREVER (UINT_MAX - 1)
#define kRepeatForever CC_REPEAT_FOREVER

/** @def CC_BLEND_SRC
default gl blend src function. Compatible with premultiplied alpha images.
*/
#define CC_BLEND_SRC cc::backend::BlendFactor::ONE
#define CC_BLEND_DST cc::backend::BlendFactor::ONE_MINUS_SRC_ALPHA

/** @def CC_NODE_DRAW_SETUP [DEPRECATED]
 Helpful macro that setups the GL server state, the correct GL program and sets the Model View Projection matrix
 @since v2.0
 */
#define CC_NODE_DRAW_SETUP()

/** @def CC_DIRECTOR_END
 Stops and removes the director from memory.
 Removes the GLView from its parent

 @since v0.99.4
 */
#define CC_DIRECTOR_END()                                        \
    do                                                           \
    {                                                            \
        Director* __director = cc::Director::getInstance(); \
        __director->end();                                       \
    } while (0)

/** @def CC_CONTENT_SCALE_FACTOR
On Mac it returns 1;
On iPhone it returns 2 if RetinaDisplay is On. Otherwise it returns 1
*/
#define CC_CONTENT_SCALE_FACTOR() cc::Director::getInstance()->getContentScaleFactor()

/****************************/
/** RETINA DISPLAY ENABLED **/
/****************************/

/** @def CC_RECT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_RECT_PIXELS_TO_POINTS(__rect_in_pixels__)                           \
    cc::Rect((__rect_in_pixels__).origin.x / CC_CONTENT_SCALE_FACTOR(),   \
                  (__rect_in_pixels__).origin.y / CC_CONTENT_SCALE_FACTOR(),   \
                  (__rect_in_pixels__).size.width / CC_CONTENT_SCALE_FACTOR(), \
                  (__rect_in_pixels__).size.height / CC_CONTENT_SCALE_FACTOR())

/** @def CC_RECT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_RECT_POINTS_TO_PIXELS(__rect_in_points_points__)                          \
    cc::Rect((__rect_in_points_points__).origin.x* CC_CONTENT_SCALE_FACTOR(),   \
                  (__rect_in_points_points__).origin.y* CC_CONTENT_SCALE_FACTOR(),   \
                  (__rect_in_points_points__).size.width* CC_CONTENT_SCALE_FACTOR(), \
                  (__rect_in_points_points__).size.height* CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_POINT_PIXELS_TO_POINTS(__pixels__) \
    cc::Vec2((__pixels__).x / CC_CONTENT_SCALE_FACTOR(), (__pixels__).y / CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_POINT_POINTS_TO_PIXELS(__points__) \
    cc::Vec2((__points__).x* CC_CONTENT_SCALE_FACTOR(), (__points__).y* CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_PIXELS_TO_POINTS
 Converts a rect in pixels to points
 */
#define CC_SIZE_PIXELS_TO_POINTS(__size_in_pixels__)             \
    Vec2((__size_in_pixels__).width / CC_CONTENT_SCALE_FACTOR(), \
         (__size_in_pixels__).height / CC_CONTENT_SCALE_FACTOR())

/** @def CC_POINT_POINTS_TO_PIXELS
 Converts a rect in points to pixels
 */
#define CC_SIZE_POINTS_TO_PIXELS(__size_in_points__) \
    Vec2((__size_in_points__).width* CC_CONTENT_SCALE_FACTOR(), (__size_in_points__).height* CC_CONTENT_SCALE_FACTOR())

/**********************/
/** Profiling Macros **/
/**********************/
#if CC_ENABLE_PROFILERS

    #define CC_PROFILER_DISPLAY_TIMERS() NS_CC::Profiler::getInstance()->displayTimers()
    #define CC_PROFILER_PURGE_ALL() NS_CC::Profiler::getInstance()->releaseAllTimers()

    #define CC_PROFILER_START(__name__) NS_CC::ProfilingBeginTimingBlock(__name__)
    #define CC_PROFILER_STOP(__name__) NS_CC::ProfilingEndTimingBlock(__name__)
    #define CC_PROFILER_RESET(__name__) NS_CC::ProfilingResetTimingBlock(__name__)

    #define CC_PROFILER_START_CATEGORY(__cat__, __name__)   \
        do                                                  \
        {                                                   \
            if (__cat__)                                    \
                NS_CC::ProfilingBeginTimingBlock(__name__); \
        } while (0)
    #define CC_PROFILER_STOP_CATEGORY(__cat__, __name__)  \
        do                                                \
        {                                                 \
            if (__cat__)                                  \
                NS_CC::ProfilingEndTimingBlock(__name__); \
        } while (0)
    #define CC_PROFILER_RESET_CATEGORY(__cat__, __name__)   \
        do                                                  \
        {                                                   \
            if (__cat__)                                    \
                NS_CC::ProfilingResetTimingBlock(__name__); \
        } while (0)

    #define CC_PROFILER_START_INSTANCE(__id__, __name__)                                       \
        do                                                                                     \
        {                                                                                      \
            NS_CC::ProfilingBeginTimingBlock(                                                  \
                NS_CC::String::createWithFormat("%08X - %s", __id__, __name__)->getCString()); \
        } while (0)
    #define CC_PROFILER_STOP_INSTANCE(__id__, __name__)                                        \
        do                                                                                     \
        {                                                                                      \
            NS_CC::ProfilingEndTimingBlock(                                                    \
                NS_CC::String::createWithFormat("%08X - %s", __id__, __name__)->getCString()); \
        } while (0)
    #define CC_PROFILER_RESET_INSTANCE(__id__, __name__)                                       \
        do                                                                                     \
        {                                                                                      \
            NS_CC::ProfilingResetTimingBlock(                                                  \
                NS_CC::String::createWithFormat("%08X - %s", __id__, __name__)->getCString()); \
        } while (0)

#else

    #define CC_PROFILER_DISPLAY_TIMERS() \
        do                               \
        {                                \
        } while (0)
    #define CC_PROFILER_PURGE_ALL() \
        do                          \
        {                           \
        } while (0)

    #define CC_PROFILER_START(__name__) \
        do                              \
        {                               \
        } while (0)
    #define CC_PROFILER_STOP(__name__) \
        do                             \
        {                              \
        } while (0)
    #define CC_PROFILER_RESET(__name__) \
        do                              \
        {                               \
        } while (0)

    #define CC_PROFILER_START_CATEGORY(__cat__, __name__) \
        do                                                \
        {                                                 \
        } while (0)
    #define CC_PROFILER_STOP_CATEGORY(__cat__, __name__) \
        do                                               \
        {                                                \
        } while (0)
    #define CC_PROFILER_RESET_CATEGORY(__cat__, __name__) \
        do                                                \
        {                                                 \
        } while (0)

    #define CC_PROFILER_START_INSTANCE(__id__, __name__) \
        do                                               \
        {                                                \
        } while (0)
    #define CC_PROFILER_STOP_INSTANCE(__id__, __name__) \
        do                                              \
        {                                               \
        } while (0)
    #define CC_PROFILER_RESET_INSTANCE(__id__, __name__) \
        do                                               \
        {                                                \
        } while (0)

#endif

/*********************************/
/** 64bits Program Sense Macros **/
/*********************************/
#if defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(__x86_64) || \
    defined(__arm64__) || defined(__aarch64__)
    #define CC_64BITS 1
#else
    #define CC_64BITS 0
#endif

/******************************************************************************************/
/** LittleEndian Sense Macro, from google protobuf see:                                  **/
/** https://github.com/google/protobuf/blob/master/src/google/protobuf/io/coded_stream.h **/
/******************************************************************************************/
#ifdef _WIN32
// Assuming windows is always little-endian.
    #if !defined(CC_DISABLE_LITTLE_ENDIAN_OPT_FOR_TEST)
        #define CC_LITTLE_ENDIAN 1
    #endif
    #if defined(_MSC_VER) && _MSC_VER >= 1300 && !defined(__INTEL_COMPILER)
// If MSVC has "/RTCc" set, it will complain about truncating casts at
// runtime.  This file contains some intentional truncating casts.
        #pragma runtime_checks("c", off)
    #endif
#else
    #ifdef __APPLE__
        #include <machine/endian.h>  // __BYTE_ORDER
    #elif defined(__FreeBSD__)
        #include <sys/endian.h>  // __BYTE_ORDER
    #else
        #if !defined(__QNX__)
            #include <endian.h>  // __BYTE_ORDER
        #endif
    #endif
    #if ((defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) ||    \
         (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN)) && \
        !defined(CC_DISABLE_LITTLE_ENDIAN_OPT_FOR_TEST)
        #define CC_LITTLE_ENDIAN 1
    #endif
#endif

/** @def CC_INCREMENT_GL_DRAWS_BY_ONE
 Increments the GL Draws counts by one.
 The number of calls per frame are displayed on the screen when the Director's stats are enabled.
 */
#define CC_INCREMENT_GL_DRAWS(__n__) cc::Director::getInstance()->getRenderer()->addDrawnBatches(__n__)
#define CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(__drawcalls__, __vertices__) \
    do                                                                          \
    {                                                                           \
        auto __renderer__ = cc::Director::getInstance()->getRenderer();    \
        __renderer__->addDrawnBatches(__drawcalls__);                           \
        __renderer__->addDrawnVertices(__vertices__);                           \
    } while (0)

/*******************/
/** Notifications **/
/*******************/
/** @def AnimationFrameDisplayedNotification
 Notification name when a SpriteFrame is displayed
 */
#define AnimationFrameDisplayedNotification "CCAnimationFrameDisplayedNotification"

/*******************/
/** Notifications **/
/*******************/
/** @def Animate3DDisplayedNotification
 Notification name when a frame in Animate3D is played
 */
#define Animate3DDisplayedNotification "CCAnimate3DDisplayedNotification"
