# Uncomment target properties to trace where their values come from.
set(CMAKE_DEBUG_TARGET_PROPERTIES
    # INCLUDE_DIRECTORIES
    # COMPILE_DEFINITIONS
    # COMPILE_OPTIONS
    # AUTOUIC_OPTIONS
    # POSITION_INDEPENDENT_CODE
)

# Keep engine targets in a subdirectory of the project's build tree.
set(ENGINE_BINARY_PATH ${PROJECT_BINARY_DIR}/engine)

if(CMAKE_TOOLCHAIN_FILE)
    message(STATUS "using toolchain file:" ${CMAKE_TOOLCHAIN_FILE})
endif()

find_program(PYTHON_COMMAND NAMES python2 python)

message(STATUS "PROJECT_NAME:" ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
message(STATUS "COCOS2DX_ROOT_PATH:" ${COCOS2DX_ROOT_PATH})
message(STATUS "CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
message(STATUS "PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})
message(STATUS "ENGINE_BINARY_PATH:" ${ENGINE_BINARY_PATH})
message(STATUS "PYTHON_COMMAND: ${PYTHON_COMMAND}")
message(STATUS "HOST_SYSTEM:" ${CMAKE_HOST_SYSTEM_NAME})
option(BUILD_LUA_LIBS "Build lua libraries" OFF)
option(CC_BUILD_SHARED_LIBS "Build the cocos core as a shared library with embedded gfx" OFF)

# AUTO follows cocos' CC_DEBUG > 0 in the binding header. Only explicit
# overrides are supplied to every target instantiating the templates.
set(CC_LUA_BINDING_CHECKS "AUTO" CACHE STRING "Lua binding diagnostics: AUTO, ON or OFF")
set_property(CACHE CC_LUA_BINDING_CHECKS PROPERTY STRINGS AUTO ON OFF)
string(TOUPPER "${CC_LUA_BINDING_CHECKS}" _cc_lua_binding_checks)
if(_cc_lua_binding_checks STREQUAL "ON")
    add_compile_definitions(CC_LUA_BINDING_CHECKS=1)
elseif(_cc_lua_binding_checks STREQUAL "OFF")
    add_compile_definitions(CC_LUA_BINDING_CHECKS=0)
elseif(NOT _cc_lua_binding_checks STREQUAL "AUTO")
    message(FATAL_ERROR "CC_LUA_BINDING_CHECKS must be AUTO, ON or OFF")
endif()
unset(_cc_lua_binding_checks)

# include helper functions
include(CocosBuildHelpers)

# Detect the platform and set common compiler options.
include(CocosConfigDefine)

if(CC_BUILD_SHARED_LIBS)
    string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" _cc_shared_arch)
    if(NOT (WINDOWS AND MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 8 AND _cc_shared_arch STREQUAL "x64"))
        message(FATAL_ERROR
            "CC_BUILD_SHARED_LIBS requires Windows x64 with MSVC; detected system '${CMAKE_SYSTEM_NAME}', compiler '${CMAKE_CXX_COMPILER_ID}', architecture '${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}'")
    endif()
    unset(_cc_shared_arch)
endif()

# Apply Xcode defaults after IOS/MACOSX detection and before creating targets.
# Preserve deployment versions supplied through CMake or Xcode attributes.
if(XCODE AND "${CMAKE_OSX_DEPLOYMENT_TARGET}" STREQUAL "")
    if(IOS AND NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        set(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 17.0)
    elseif(MACOSX AND NOT DEFINED CMAKE_XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET)
        set(CMAKE_XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET 12.0)
    endif()
endif()

if(APPLE)
    enable_language(OBJC OBJCXX)
    # Keep Objective-C and Objective-C++ aligned with the C/C++ settings.
    set(CMAKE_OBJC_STANDARD ${CMAKE_C_STANDARD})
    set(CMAKE_OBJC_STANDARD_REQUIRED ${CMAKE_C_STANDARD_REQUIRED})
    set(CMAKE_OBJCXX_STANDARD ${CMAKE_CXX_STANDARD})
    set(CMAKE_OBJCXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})
    set(CMAKE_OBJCXX_EXTENSIONS ${CMAKE_CXX_EXTENSIONS})
endif()

# Load platform dependency helpers.
include(CocosConfigDepend)
