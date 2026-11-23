set(COCOS_GAMEPAD_HEADER
    input/gamepad/GamepadTypes.h
    input/gamepad/GamepadFrame.h
    input/gamepad/GamepadMapping.h
    input/gamepad/GamepadOutput.h
    input/gamepad/GamepadService.h
)

set(COCOS_GAMEPAD_SRC
    input/gamepad/private/GamepadBackend.h
    input/gamepad/private/PlatformGamepadBackend.h
    input/gamepad/private/core/GamepadFrame.cpp
    input/gamepad/private/core/GamepadService.cpp
    input/gamepad/private/core/DeviceRegistry.cpp
    input/gamepad/private/core/DeviceRegistry.h
    input/gamepad/private/core/FrameBuilder.cpp
    input/gamepad/private/core/FrameBuilder.h
    input/gamepad/private/core/ReportQueue.cpp
    input/gamepad/private/core/ReportQueue.h
    input/gamepad/private/mapping/BindingPlan.cpp
    input/gamepad/private/mapping/BindingPlan.h
    input/gamepad/private/mapping/DeviceGuid.cpp
    input/gamepad/private/mapping/DeviceGuid.h
    input/gamepad/private/mapping/MappingDatabase.cpp
    input/gamepad/private/mapping/MappingDatabase.h
    input/gamepad/private/mapping/SdlMappingParser.cpp
    input/gamepad/private/mapping/SdlMappingParser.h
    input/gamepad/private/output/HapticPlayback.cpp
    input/gamepad/private/output/HapticPlaybackSession.h
    input/gamepad/private/output/OutputRouter.cpp
    input/gamepad/private/output/OutputRouter.h
    input/gamepad/private/output/OutputRouterHaptics.cpp
    input/gamepad/private/drivers/DualShock4Reports.h
    input/gamepad/private/drivers/DualShock4Reports.cpp
    input/gamepad/private/drivers/DualSenseReports.h
    input/gamepad/private/drivers/DualSenseReports.cpp
    input/gamepad/private/drivers/SonyHidReports.h
    input/gamepad/private/drivers/SonyReportBits.h
    input/gamepad/private/drivers/SwitchReports.cpp
    input/gamepad/private/drivers/SwitchReports.h
    input/gamepad/private/drivers/XboxBluetoothReports.cpp
    input/gamepad/private/drivers/XboxBluetoothReports.h
)

if(WIN32)
    list(APPEND COCOS_GAMEPAD_SRC
        input/gamepad/private/win/WinGamepadBackend.cpp
        input/gamepad/private/win/WinDirectInput.cpp
        input/gamepad/private/win/WinHidFile.h
        input/gamepad/private/win/WinLegacyInput.cpp
        input/gamepad/private/win/WinLegacyInput.h
        input/gamepad/private/win/WinRawHid.cpp
        input/gamepad/private/win/WinSwitchGamepad.cpp
        input/gamepad/private/win/WinSwitchGamepad.h
        input/gamepad/private/win/WinWgi.cpp
        input/gamepad/private/win/WinWgi.h
        input/gamepad/private/win/WinXboxBluetooth.cpp
        input/gamepad/private/win/WinXboxBluetooth.h
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
        input/gamepad/private/linux/LinuxHidGamepad.h
        input/gamepad/private/linux/LinuxSonyHid.h
        input/gamepad/private/linux/LinuxSonyHid.cpp
        input/gamepad/private/linux/LinuxSwitchHid.h
        input/gamepad/private/linux/LinuxSwitchHid.cpp
        input/gamepad/private/linux/LinuxXboxBluetooth.h
        input/gamepad/private/linux/LinuxXboxBluetooth.cpp
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
