set(COCOS_GAMEPAD_HEADER
    input/gamepad/GamepadTypes.h
    input/gamepad/GamepadFrame.h
    input/gamepad/GamepadMapping.h
    input/gamepad/GamepadOutput.h
    input/gamepad/GamepadService.h
)

set(COCOS_GAMEPAD_SRC
    input/gamepad/GamepadFrame.cpp
    input/gamepad/GamepadService.cpp
    input/gamepad/private/BindingPlan.cpp
    input/gamepad/private/BindingPlan.h
    input/gamepad/private/DeviceGuid.cpp
    input/gamepad/private/DeviceGuid.h
    input/gamepad/private/DeviceRegistry.cpp
    input/gamepad/private/DeviceRegistry.h
    input/gamepad/private/FrameBuilder.cpp
    input/gamepad/private/FrameBuilder.h
    input/gamepad/private/GamepadBackend.h
    input/gamepad/private/PlatformGamepadBackend.h
    input/gamepad/private/drivers/DualShock4Reports.h
    input/gamepad/private/drivers/DualShock4Reports.cpp
    input/gamepad/private/drivers/DualSenseReports.h
    input/gamepad/private/drivers/DualSenseReports.cpp
    input/gamepad/private/drivers/SonyHidReports.h
    input/gamepad/private/drivers/SonyReportBits.h
    input/gamepad/private/MappingDatabase.cpp
    input/gamepad/private/MappingDatabase.h
    input/gamepad/private/OutputRouter.cpp
    input/gamepad/private/OutputRouter.h
    input/gamepad/private/ReportQueue.cpp
    input/gamepad/private/ReportQueue.h
    input/gamepad/private/SdlMappingParser.cpp
    input/gamepad/private/SdlMappingParser.h
)

if(WIN32)
    list(APPEND COCOS_GAMEPAD_SRC
        input/gamepad/private/win/WinGamepadBackend.cpp
        input/gamepad/private/win/WinDirectInput.cpp
        input/gamepad/private/win/WinLegacyInput.cpp
        input/gamepad/private/win/WinLegacyInput.h
        input/gamepad/private/win/WinRawHid.cpp
        input/gamepad/private/win/WinXInput.cpp
        input/gamepad/private/win/WinXInput.h
    )
    set(COCOS_GAMEPAD_PLATFORM_LIBS cfgmgr32 hid dinput8 dxguid)
elseif(ANDROID)
    list(APPEND COCOS_GAMEPAD_SRC input/gamepad/private/android/AndroidGamepadBackend.cpp)
elseif(APPLE)
    enable_language(OBJCXX)
    find_library(COCOS_GAMEPAD_GC GameController REQUIRED)
    find_library(COCOS_GAMEPAD_HAPTICS CoreHaptics REQUIRED)
    list(APPEND COCOS_GAMEPAD_SRC input/gamepad/private/apple/AppleGamepadBackend.mm)
    set(COCOS_GAMEPAD_PLATFORM_LIBS "${COCOS_GAMEPAD_GC}" "${COCOS_GAMEPAD_HAPTICS}")
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND NOT IOS)
        find_library(COCOS_GAMEPAD_IOKIT IOKit REQUIRED)
        list(APPEND COCOS_GAMEPAD_PLATFORM_LIBS "${COCOS_GAMEPAD_IOKIT}")
    endif()
    set(COCOS_GAMEPAD_APPLE TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND COCOS_GAMEPAD_SRC
        input/gamepad/private/linux/EvdevGamepadBackend.cpp
        input/gamepad/private/linux/EvdevGamepadLayout.cpp
        input/gamepad/private/linux/EvdevGamepadLayout.h
        input/gamepad/private/linux/LinuxSonyHid.h
        input/gamepad/private/linux/LinuxSonyHid.cpp
    )
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GAMEPAD_UDEV QUIET IMPORTED_TARGET libudev)
        if(TARGET PkgConfig::GAMEPAD_UDEV)
            set(COCOS_GAMEPAD_PLATFORM_LIBS PkgConfig::GAMEPAD_UDEV)
            set(COCOS_GAMEPAD_PLATFORM_DEFINITIONS CC_GAMEPAD_HAVE_UDEV)
        endif()
    endif()
endif()
