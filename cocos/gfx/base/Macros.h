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

// define supported target platform macro which CC uses.
#define CC_PLATFORM_UNKNOWN            0
#define CC_PLATFORM_IOS                1
#define CC_PLATFORM_ANDROID            2
#define CC_PLATFORM_WIN32              3
// #define CC_PLATFORM_MARMALADE          4
#define CC_PLATFORM_LINUX              5
// #define CC_PLATFORM_BADA               6
// #define CC_PLATFORM_BLACKBERRY         7
#define CC_PLATFORM_MAC                8
// #define CC_PLATFORM_NACL               9
#define CC_PLATFORM_EMSCRIPTEN        10
// #define CC_PLATFORM_TIZEN             11
// #define CC_PLATFORM_QT5               12
// #define CC_PLATFORM_WINRT             13
#define CC_PLATFORM_MAC_IOS           CC_PLATFORM_IOS
#define CC_PLATFORM_MAC_OSX           CC_PLATFORM_MAC
#define CC_PLATFORM_MACOS             CC_PLATFORM_MAC
#define CC_PLATFORM_OHOS              14
#define CC_PLATFORM_QNX               15
#define CC_PLATFORM_NX                16

// Determine target platform by compile environment macro.
#ifndef CC_TARGET_PLATFORM
    #define CC_TARGET_PLATFORM             CC_PLATFORM_UNKNOWN
#endif

// Apple: Mac and iOS
#if defined(__APPLE__) && !defined(ANDROID) // exclude android for binding generator.
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE // TARGET_OS_IPHONE includes TARGET_OS_IOS TARGET_OS_TV and TARGET_OS_WATCH. see TargetConditionals.h
        #undef  CC_TARGET_PLATFORM
        #define CC_TARGET_PLATFORM         CC_PLATFORM_IOS
    #elif TARGET_OS_MAC
        #undef  CC_TARGET_PLATFORM
        #define CC_TARGET_PLATFORM         CC_PLATFORM_MAC
    #endif
#endif

// android
#if defined(ANDROID)
    #undef  CC_TARGET_PLATFORM
    #define CC_TARGET_PLATFORM         CC_PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) && defined(_WINDOWS)
    #undef  CC_TARGET_PLATFORM
    #define CC_TARGET_PLATFORM         CC_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX) && !defined(__APPLE__)
    #undef  CC_TARGET_PLATFORM
    #define CC_TARGET_PLATFORM         CC_PLATFORM_LINUX
#endif


//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! CC_TARGET_PLATFORM
    #error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning (disable:4127)
#endif
#endif  // CC_PLATFORM_WIN32

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS))
    #define CC_PLATFORM_MOBILE
#else
    #define CC_PLATFORM_PC
#endif



#define CC_PLATFORM CC_TARGET_PLATFORM
#define CC_PLATFORM_WINDOWS CC_PLATFORM_WIN32

#ifndef CC_DEBUG
#define CC_DEBUG 0
#endif


//////////////////////////////////////////////////////////////////////////

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

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
    #if defined(CC_STATIC)
        #define CC_DLL
    #else
        #if defined(_USRDLL)
            #define CC_DLL __declspec(dllexport)
        #else /* use a DLL library */
            #define CC_DLL __declspec(dllimport)
        #endif
    #endif
#else
    #define CC_DLL
#endif

#ifndef CCASSERT
    #if CC_DEBUG > 0
        #define CCASSERT(cond, msg) CC_ASSERT(cond)
    // #endif
    #else
        #define CCASSERT(cond, msg)
    #endif

    #define GP_ASSERT(cond) CCASSERT(cond, "")
#endif // CCASSERT

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

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

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
