# One Lua application with native entry points for every supported platform.
set(demo_sources Classes/AppDelegate.cpp Classes/AppDelegate.h)
set(demo_resources Resources/main.lua Resources/icon.png)

if(WINDOWS)
    enable_language(RC)
    add_executable(cocos_demo WIN32 ${demo_sources} proj.win32/main.cpp proj.win32/game.rc)
    target_include_directories(cocos_demo PRIVATE proj.win32)
elseif(LINUX)
    add_executable(cocos_demo ${demo_sources} proj.linux/main.cpp)
elseif(MACOSX)
    add_executable(cocos_demo MACOSX_BUNDLE ${demo_sources} proj.ios_mac/mac/main.mm)
elseif(IOS)
    add_executable(cocos_demo MACOSX_BUNDLE ${demo_sources} proj.ios_mac/ios/main.mm)
elseif(ANDROID)
    add_library(cocos_demo SHARED ${demo_sources} proj.android/app/jni/main.cpp)
    if(NOT TARGET cpp_android_spec)
        add_subdirectory("${COCOS2DX_ROOT_PATH}/cocos/platform/android"
            "${ENGINE_BINARY_PATH}/cocos/platform")
        target_link_libraries(cpp_android_spec cocos2d)
    endif()
    target_link_libraries(cocos_demo PRIVATE
        "$<LINK_LIBRARY:WHOLE_ARCHIVE,cpp_android_spec,lua_android_spec>")
else()
    message(FATAL_ERROR "The cocos demo does not support ${CMAKE_SYSTEM_NAME}")
endif()

target_compile_features(cocos_demo PRIVATE cxx_std_20)
target_include_directories(cocos_demo PRIVATE Classes)
target_link_libraries(cocos_demo PRIVATE luacocos2d)
set_target_properties(cocos_demo PROPERTIES
    FOLDER Examples
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/cocos_demo"
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:cocos_demo>")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${demo_sources} ${demo_resources})

if(WINDOWS OR LINUX)
    # A separate target also refreshes edited scripts without relinking C++.
    add_custom_target(cocos_demo_resources
        COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_FILE_DIR:cocos_demo>/Resources"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            ${demo_resources} "$<TARGET_FILE_DIR:cocos_demo>/Resources"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM)
    set_target_properties(cocos_demo_resources PROPERTIES FOLDER Utils)
    add_dependencies(cocos_demo cocos_demo_resources)
    set_source_files_properties(${demo_resources} PROPERTIES HEADER_FILE_ONLY TRUE)
    target_sources(cocos_demo PRIVATE ${demo_resources})
    cocos_copy_target_dll(cocos_demo)
    if(WINDOWS)
        set_property(DIRECTORY "${COCOS2DX_ROOT_PATH}" PROPERTY VS_STARTUP_PROJECT cocos_demo)
    else()
        set_target_properties(cocos_demo PROPERTIES
            BUILD_RPATH "$ORIGIN" BUILD_RPATH_USE_ORIGIN TRUE)
    endif()
elseif(APPLE)
    set_source_files_properties(${demo_resources} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    target_sources(cocos_demo PRIVATE ${demo_resources})
    target_compile_options(cocos_demo PRIVATE "$<$<COMPILE_LANGUAGE:OBJC,OBJCXX>:-fobjc-arc>")
    set_target_properties(cocos_demo PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "cocos-x Demo"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.cocos.demo"
        MACOSX_BUNDLE_BUNDLE_VERSION "1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "org.cocos.demo"
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)
    if(MACOSX)
        target_sources(cocos_demo PRIVATE proj.ios_mac/mac/Icon.icns)
        set_source_files_properties(proj.ios_mac/mac/Icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set_target_properties(cocos_demo PROPERTIES
            MACOSX_BUNDLE_ICON_FILE Icon.icns
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
        if(CMAKE_OSX_ARCHITECTURES STREQUAL "x86_64"
                OR (NOT CMAKE_OSX_ARCHITECTURES AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"))
            target_link_options(cocos_demo PRIVATE -pagezero_size 10000 -image_base 100000000)
        endif()
    else()
        set(ios_resources proj.ios_mac/ios/Images.xcassets proj.ios_mac/ios/LaunchScreen.storyboard)
        target_sources(cocos_demo PRIVATE ${ios_resources})
        set_source_files_properties(${ios_resources} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set_target_properties(cocos_demo PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist"
            XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
    endif()
    cocos_config_app_xcode_property(cocos_demo)
    if(CC_ENABLE_VIDEO_TEXTURE)
        if(XCODE)
            set_property(TARGET cocos_demo APPEND PROPERTY XCODE_EMBED_FRAMEWORKS "${FFMPEG_LIBRARY}")
            set_target_properties(cocos_demo PROPERTIES
                XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY ON
                XCODE_EMBED_FRAMEWORKS_REMOVE_HEADERS_ON_COPY ON)
        else()
            get_target_property(demo_ffmpeg_framework ext_ffmpeg LOCATION)
            add_custom_command(TARGET cocos_demo POST_BUILD
                COMMAND /usr/bin/ditto "${demo_ffmpeg_framework}"
                    "$<TARGET_BUNDLE_CONTENT_DIR:cocos_demo>/Frameworks/FFmpeg.framework"
                VERBATIM)
        endif()
        if(MACOSX)
            target_link_options(cocos_demo PRIVATE -Wl,-rpath,@loader_path/../Frameworks)
        else()
            target_link_options(cocos_demo PRIVATE -Wl,-rpath,@executable_path/Frameworks)
        endif()
    endif()
endif()
