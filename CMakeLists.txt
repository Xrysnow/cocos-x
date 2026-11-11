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

# Build the engine and Lua bindings.

cmake_minimum_required(VERSION 3.28)

project(cocos-x)

if(XCODE)
  set(CMAKE_XCODE_GENERATE_TOP_LEVEL_PROJECT_ONLY TRUE)
endif()

# Locate the engine and its CMake modules.
set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

# prevent in-source-build
include(PreventInSourceBuilds)

# Load shared settings before creating engine targets.
option(BUILD_LUA_LIBS "Build lua libraries" ON)
option(CC_BUILD_DEMO "Build the cross-platform Lua demo" OFF)
if(CC_BUILD_DEMO AND NOT BUILD_LUA_LIBS)
  message(FATAL_ERROR "CC_BUILD_DEMO requires BUILD_LUA_LIBS=ON")
endif()
include(CocosBuildSet)

# Reconfigure from the selected extensions rather than a previous cache list.
set(CC_EXTENSION_LIBS "" CACHE INTERNAL "extensions for auto link to target application" FORCE)

add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
list(REMOVE_ITEM CC_EXTENSION_LIBS "")
list(REMOVE_DUPLICATES CC_EXTENSION_LIBS)
set(CC_EXTENSION_LIBS "${CC_EXTENSION_LIBS}" CACHE INTERNAL "extensions for auto link to target application" FORCE)

if(CC_BUILD_SHARED_LIBS)
  include(CocosSharedPackage)
  cocos_generate_shared_package()
endif()

if(CC_BUILD_DEMO)
  add_subdirectory(templates)
endif()
