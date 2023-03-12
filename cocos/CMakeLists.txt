#/****************************************************************************
# Copyright (c) 2013 cocos2d-x.org
# Copyright (c) 2014 martell malone
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

# this CMakeLists is to generate Cocos2d-x Engine Library
# build libcocos2d
# build luacocos2d if BUILD_LUA_LIBS=ON

# The version number
set(COCOS2D_X_VERSION 4.0)

set(COCOS_CORE_LIB cocos2d)
project(cocos2d_libs)

if (NOT DEFINED CC_ENABLE_MSEDGE_WEBVIEW2)
    set(CC_ENABLE_MSEDGE_WEBVIEW2 OFF CACHE INTERNAL "Enabling windows webview2" )
endif()

if (NOT DEFINED CC_ENABLE_MFMEDIA)
    set(CC_ENABLE_MFMEDIA OFF CACHE INTERNAL "Enabling microsoft media foundation for windows video player" )
endif()

# extensions to build
# extensions dependicies: COCOSTUDIO may depend on spine & dragonBones if they are present in buildset
option(CC_ENABLE_EXT_GUI "Build extension GUI" ON)
option(CC_ENABLE_EXT_ASSETMANAGER "Build extension asset-manager" ON)
option(CC_ENABLE_EXT_PARTICLE3D "Build extension Particle3D" ON)
option(CC_ENABLE_EXT_PHYSICS_NODE "Build extension physics-nodes" ON)
option(CC_ENABLE_EXT_SPINE "Build extension spine" ON)
option(CC_ENABLE_EXT_DRAGONBONES "Build extension DragonBones" ON)
option(CC_ENABLE_EXT_COCOSTUDIO "Build extension cocostudio" ON)
option(CC_ENABLE_EXT_FAIRYGUI "Build extension FairyGUI" ON)
option(CC_ENABLE_EXT_LIVE2D "Build extension Live2D" OFF)
option(CC_ENABLE_EXT_EFFEKSEER "Build extension Effekseer" OFF)
option(CC_ENABLE_EXT_IMGUI "Build extension ImGui" OFF)

if(BUILD_LUA_LIBS)
    set(CC_ENABLE_EXT_LUA ON)
endif()

if (CC_ENABLE_EXT_EFFEKSEER AND ANDROID) # effekseer-axmol require use glad
   set(CC_USE_GLAD TRUE CACHE INTERNAL "Forcing use glad for platforms which use GL backend" )
   add_definitions(-DCC_USE_GLAD=1)
endif()

if(XCODE)
    # set(CMAKE_BUILD_WITH_INSTALL_RPATH YES)
    # set(CMAKE_INSTALL_RPATH "@executable_path/Frameworks")
    set(CMAKE_XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/Frameworks" CACHE INTERNAL "")
endif()

if (WIN32)
    option(WIN32_PATH_USE_ACP "" OFF)
    if(NOT WIN32_PATH_USE_ACP)
        add_definitions(-DNTCVT_CP_DEFAULT=CP_UTF8)
    else()
        add_definitions(-DNTCVT_CP_DEFAULT=CP_ACP)
    endif()
endif()

include(2d/CMakeLists.txt)
include(3d/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(physics/CMakeLists.txt)
include(physics3d/CMakeLists.txt)
include(math/CMakeLists.txt)
include(navmesh/CMakeLists.txt)
include(renderer/CMakeLists.txt)
include(base/CMakeLists.txt)
include(ui/CMakeLists.txt)
include(network/CMakeLists.txt)
include(audio/CMakeLists.txt)

set(COCOS_HEADER cocos2d.h
    ${COCOS_2D_HEADER}
    ${COCOS_3D_HEADER}
    ${COCOS_PLATFORM_HEADER}
    ${COCOS_PHYSICS_HEADER}
    ${COCOS_PHYSICS3D_HEADER}
    ${COCOS_MATH_HEADER}
    ${COCOS_NAVMESH_HEADER}
    ${COCOS_RENDERER_HEADER}
    ${COCOS_BASE_HEADER}
    ${COCOS_AUDIO_HEADER}
    ${COCOS_UI_HEADER}
    ${COCOS_NETWORK_HEADER}
    )

set(COCOS_SRC cocos2d.cpp
    ${COCOS_2D_SRC}
    ${COCOS_3D_SRC}
    ${COCOS_PLATFORM_SRC}
    ${COCOS_PHYSICS_SRC}
    ${COCOS_PHYSICS3D_SRC}
    ${COCOS_MATH_SRC}
    ${COCOS_NAVMESH_SRC}
    ${COCOS_RENDERER_SRC}
    ${COCOS_BASE_SRC}
    ${COCOS_AUDIO_SRC}
    ${COCOS_UI_SRC}
    ${COCOS_NETWORK_SRC}
    )

list(APPEND COCOS_SRC ${COCOS_HEADER})

add_library(${COCOS_CORE_LIB} ${COCOS_SRC})

# use external libs
add_subdirectory(${COCOS2DX_ROOT_PATH}/external ${ENGINE_BINARY_PATH}/external)
target_link_libraries(${COCOS_CORE_LIB} external)

# add base macro define and compile options
use_cocos2dx_compile_define(${COCOS_CORE_LIB})
use_cocos2dx_compile_options(${COCOS_CORE_LIB})

# use all platform related system libs
use_cocos2dx_libs_depend(${COCOS_CORE_LIB})

target_include_directories(${COCOS_CORE_LIB}
    PUBLIC ${COCOS2DX_ROOT_PATH}
    PUBLIC ${COCOS2DX_ROOT_PATH}/external
    PUBLIC ${COCOS2DX_ROOT_PATH}/extensions
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform

    INTERFACE ${COCOS2DX_ROOT_PATH}/external
    INTERFACE ${COCOS2DX_ROOT_PATH}/extensions
    INTERFACE ${COCOS2DX_ROOT_PATH}/cocos/base
    INTERFACE ${COCOS2DX_ROOT_PATH}/cocos/audio
    INTERFACE ${COCOS2DX_ROOT_PATH}/cocos/platform/${PLATFORM_FOLDER}
)

set_target_properties(${COCOS_CORE_LIB}
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
                      VERSION "${COCOS2D_X_VERSION}"
                      FOLDER "Internal"
                      )

if(XCODE OR VS)
    cocos_mark_code_files(${COCOS_CORE_LIB})
endif()

message("CMake 3.16 target_precompile_headers")
target_precompile_headers(cocos2d PRIVATE 
    "$<$<COMPILE_LANGUAGE:CXX>:cocos2d.h>")

if(WINDOWS)
    if(CC_ENABLE_MSEDGE_WEBVIEW2)
        find_program(NUGET_EXE NAMES nuget 
            PATHS ${_CC_ROOT_PATH}/tools/external/nuget)
            
        if(NOT NUGET_EXE)
            message("NUGET.EXE not found.")
            message(FATAL_ERROR "Please run setup.py again to download NUGET.EXE, and run CMake again.")
        endif()
     
        exec_program(${NUGET_EXE}
            ARGS install "Microsoft.Web.WebView2" -Version 1.0.992.28 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)

        if(CMAKE_GENERATOR STREQUAL "Ninja")
            target_link_libraries(${COCOS_CORE_LIB} ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/${ARCH_ALIAS}/WebView2Loader.dll.lib)
            target_include_directories(${COCOS_CORE_LIB} PUBLIC ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/include)
        else()
            target_link_libraries(${COCOS_CORE_LIB} ${CMAKE_BINARY_DIR}/packages/Microsoft.Web.WebView2/build/native/Microsoft.Web.WebView2.targets)
        endif()
        target_compile_definitions(${COCOS_CORE_LIB} PUBLIC CC_HAVE_WEBVIEW2)
        target_compile_definitions(${COCOS_CORE_LIB} PUBLIC AX_HAVE_WEBVIEW2)
    endif()
endif()

# engine extensions
add_subdirectory(${COCOS2DX_ROOT_PATH}/extensions ${ENGINE_BINARY_PATH}/extensions)

#if(XCODE)
#    # Later versions of Xcode clang want to compile C++17 with aligned allocation turned on and this is only supported on iOS 11.0+
#    # TODO: Only turn this off if ${CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET} < 11.0
#    target_compile_options(${COCOS_CORE_LIB} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-fno-aligned-allocation>)
#endif()

if(CC_USE_GFX)
	target_compile_definitions(${COCOS_CORE_LIB} PUBLIC CC_USE_GFX)
endif()
