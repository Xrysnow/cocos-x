#/****************************************************************************
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

if(ANDROID)
    # refer to target: cocos/platform/android/CMakeLists.txt
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/android/Application-android.cpp
        platform/android/SystemInfo-android.cpp
        platform/android/SystemNetwork-android.cpp
        platform/android/Common-android.cpp
        platform/android/GLViewImpl-android.cpp
        platform/android/TextInput-android.cpp
        platform/android/AndroidPackageReadAdapter.cpp
        platform/android/FileUtils-android.cpp
    )
elseif(WINDOWS)
    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/win32/compat/stdint.h
        platform/win32/Application-win32.h
        platform/win32/inet_pton_mingw.h
        platform/win32/FileUtils-win32.h
        platform/win32/StdC-win32.h
        platform/win32/PlatformDefine-win32.h
        platform/desktop/GLViewImpl-desktop.h
        platform/desktop/TextInputGLFW.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/win32/StdC-win32.cpp
        platform/win32/SystemInfo-win32.cpp
        platform/win32/SystemNetwork-win32.cpp
        platform/win32/FileUtils-win32.cpp
        platform/win32/Common-win32.cpp
        platform/win32/Application-win32.cpp
        platform/win32/Device-win32.cpp
        platform/win32/inet_pton_mingw.cpp
        platform/desktop/GLViewImpl-desktop.cpp
        platform/desktop/TextInputGLFW.cpp
        platform/win32/TextInput-win32.cpp
        )

elseif(APPLE)
    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/apple/FileUtils-apple.h
        platform/apple/Device-apple.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/apple/FileUtils-apple.mm
        platform/apple/SystemInfo-apple.mm
        platform/apple/SystemNetwork-apple.mm
        platform/apple/AppDirectories-apple.mm
        platform/apple/Device-apple.mm
        )
    if(MACOSX)
        set(COCOS_PLATFORM_SPECIFIC_HEADER
            ${COCOS_PLATFORM_SPECIFIC_HEADER}
            platform/mac/StdC-mac.h
            platform/desktop/GLViewImpl-desktop.h
            platform/desktop/TextInputGLFW.h
            platform/mac/GLViewImpl-desktop-mac.h
            platform/mac/PlatformDefine-mac.h
            platform/mac/Application-mac.h
            )
        set(COCOS_PLATFORM_SPECIFIC_SRC
            ${COCOS_PLATFORM_SPECIFIC_SRC}
            platform/mac/Application-mac.mm
            platform/desktop/GLViewImpl-desktop.cpp
            platform/desktop/TextInputGLFW.cpp
            platform/mac/GLViewImpl-desktop-mac.mm
            platform/mac/TextInput-mac.mm
            platform/mac/Common-mac.mm
            platform/mac/Device-mac.mm
            )
        # Keep the shared implementation pure C++; native ownership stays in MRC.
        set_source_files_properties(platform/desktop/GLViewImpl-desktop.cpp
            PROPERTIES LANGUAGE CXX)
        set_source_files_properties(platform/mac/GLViewImpl-desktop-mac.mm platform/mac/TextInput-mac.mm
            PROPERTIES LANGUAGE OBJCXX)
        set_property(SOURCE platform/mac/GLViewImpl-desktop-mac.mm platform/mac/TextInput-mac.mm
            APPEND PROPERTY COMPILE_OPTIONS -fno-objc-arc)
    elseif(IOS)
        set(COCOS_PLATFORM_SPECIFIC_HEADER
            ${COCOS_PLATFORM_SPECIFIC_HEADER}
            platform/ios/Application-ios.h
            platform/ios/DirectorCaller-ios.h
            platform/ios/EAGLView-ios.h
            platform/ios/GLViewImpl-ios.h
            platform/ios/PlatformDefine-ios.h
            platform/ios/StdC-ios.h
            platform/ios/TextInput-ios.h
            )
        set(COCOS_PLATFORM_SPECIFIC_SRC
            ${COCOS_PLATFORM_SPECIFIC_SRC}
            platform/ios/Application-ios.mm
            platform/ios/Common-ios.mm
            platform/ios/Device-ios.mm
            platform/ios/DirectorCaller-ios.mm
            platform/ios/EAGLView-ios.mm
            platform/ios/GLViewImpl-ios.mm
            platform/ios/Image-ios.mm
            platform/ios/TextInput-ios.mm
            )
        set_property(SOURCE platform/ios/TextInput-ios.mm APPEND PROPERTY COMPILE_OPTIONS -fobjc-arc)
    endif()

elseif(LINUX)

    if(NOT CMAKE_CROSSCOMPILING)
        include_directories(
                /usr/include
                /usr/include/GLFW
                /usr/local/include/GLFW
        )
    endif(NOT CMAKE_CROSSCOMPILING)

    set(COCOS_PLATFORM_SPECIFIC_HEADER
        platform/linux/Application-linux.h
        platform/linux/GL-linux.h
        platform/linux/StdC-linux.h
        platform/linux/FileUtils-linux.h
        platform/linux/PlatformDefine-linux.h
        platform/desktop/GLViewImpl-desktop.h
        platform/desktop/TextInputGLFW.h
        )
    set(COCOS_PLATFORM_SPECIFIC_SRC
        platform/linux/FileUtils-linux.cpp
        platform/linux/SystemInfo-linux.cpp
        platform/linux/SystemNetwork-linux.cpp
        platform/linux/Common-linux.cpp
        platform/linux/Application-linux.cpp
        platform/linux/Device-linux.cpp
        platform/desktop/GLViewImpl-desktop.cpp
        platform/desktop/TextInputGLFW.cpp
        )
endif()

set(COCOS_PLATFORM_HEADER
    platform/SystemInfo.h
    platform/SystemInfoInternal.h
    platform/FileDialog.h
    ${COCOS_PLATFORM_SPECIFIC_HEADER}
    platform/Application.h
    platform/ApplicationProtocol.h
    platform/Common.h
    platform/Device.h
    platform/FileReadAdapter.h
    platform/PhysicalReadAdapter.h
    platform/FileUtils.h
    platform/AppDirectories.h
    platform/FileStream.h
    platform/GL.h
    platform/GLView.h
    platform/Image.h
    platform/PlatformConfig.h
    platform/PlatformDefine.h
    platform/Namespace.h
    platform/PlatformMacros.h
    platform/PosixFileStream.h
    platform/SAXParser.h
    platform/StdC.h
    platform/TextInputBackend.h
    platform/TextInputIndex.h
    platform/TextInputService.h
    platform/TextInputTypes.h
    )

set(COCOS_PLATFORM_SRC
    platform/SystemInfo.cpp
    platform/SystemInterfaces.cpp
    platform/SystemNetwork.cpp
    platform/SystemNetworkSignal.h
    platform/FileDialog.cpp
    ${COCOS_PLATFORM_SPECIFIC_SRC}
    platform/FileReadAdapter.cpp
    platform/FileReadRegistry.cpp
    platform/PhysicalReadAdapter.cpp
    platform/FileUtils.cpp
    platform/AppDirectories.cpp
    platform/FileStream.cpp
    platform/GLView.cpp
    platform/Image.cpp
    platform/PosixFileStream.cpp
    platform/SAXParser.cpp
    platform/TextInputIndex.cpp
    platform/TextInputService.cpp
    )

if(APPLE)
    set_property(SOURCE platform/apple/SystemInfo-apple.mm platform/apple/SystemNetwork-apple.mm
        APPEND PROPERTY COMPILE_OPTIONS -fobjc-arc)
endif()

if(CC_ENABLE_FILE_DIALOG)
    if(WINDOWS)
        list(APPEND COCOS_PLATFORM_SRC platform/win32/FileDialog-win32.cpp)
    elseif(ANDROID)
        list(APPEND COCOS_PLATFORM_SRC platform/android/jni/FileDialog-android.cpp)
    elseif(LINUX)
        list(APPEND COCOS_PLATFORM_SRC platform/linux/FileDialog-linux.cpp)
    elseif(APPLE)
        if(IOS)
            if((CMAKE_OSX_DEPLOYMENT_TARGET AND CMAKE_OSX_DEPLOYMENT_TARGET VERSION_LESS 14)
                OR (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET AND
                    CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET VERSION_LESS 14))
                message(FATAL_ERROR "CC_ENABLE_FILE_DIALOG requires iOS 14 or later")
            endif()
            set(_cc_picker platform/ios/FileDialog-ios.mm)
        else()
            set(_cc_picker platform/mac/FileDialog-mac.mm)
        endif()
        list(APPEND COCOS_PLATFORM_SRC ${_cc_picker} io/core/Document-apple.mm)
        set_property(SOURCE ${_cc_picker} io/core/Document-apple.mm APPEND PROPERTY COMPILE_OPTIONS -fobjc-arc)
    endif()
endif()
