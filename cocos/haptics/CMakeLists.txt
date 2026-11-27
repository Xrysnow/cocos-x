set(COCOS_HAPTICS_HEADER
    haptics/HapticClip.h
    haptics/HapticService.h
    haptics/MobileEffects.h
)
set(COCOS_HAPTICS_SRC
    haptics/private/ClipData.h
    haptics/private/Import.h
    haptics/private/HapticClip.cpp
    haptics/private/HapticClipFile.cpp
    haptics/private/MetaHapticParser.cpp
    haptics/private/AhapParser.cpp
    haptics/private/HapticMixer.h
    haptics/private/HapticMixer.cpp
    haptics/private/HapticControl.h
    haptics/private/HapticControl.cpp
    haptics/private/HapticService.cpp
    haptics/private/MobileHaptics.h
    haptics/private/MobileHaptics.cpp
)
if(ANDROID)
    list(APPEND COCOS_HAPTICS_SRC haptics/private/MobileHaptics-android.cpp)
elseif(APPLE)
    list(APPEND COCOS_HAPTICS_SRC haptics/private/MobileHaptics-ios.mm)
    set_source_files_properties(haptics/private/MobileHaptics-ios.mm PROPERTIES COMPILE_OPTIONS "-fobjc-arc;-std=c++20")
endif()
