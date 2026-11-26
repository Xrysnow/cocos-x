set(cocos_root ${COCOS2DX_ROOT_PATH})

set(lua_bindings_manual_headers
    manual/ComponentLua.h
    manual/3d/cclua_3d_manual.h
    manual/LuaStack.h
    manual/LuaEngine.h
    manual/lua_module_register.h
    manual/LuaBridge.h
    manual/LuaBasicConversions.h
    manual/gamepad/cclua_gamepad.hpp
    manual/gamepad/cclua_gamepad_conversions.hpp
    manual/cclua_system_info_conversions.hpp
    manual/lua_conversion/lua_conversion.hpp
    manual/lua_conversion/lua_conversion_tolua.hpp
    manual/lua_conversion/detail/base.hpp
    manual/lua_conversion/detail/scalar.hpp
    manual/lua_conversion/detail/containers.hpp
    manual/lua_conversion/detail/conversion.hpp
    manual/lua_conversion/detail/callback_state.hpp
    manual/lua_conversion/detail/callback_from_lua.hpp
    manual/lua_conversion/detail/invoke.hpp
    manual/lua_conversion/detail/value_userdata.hpp
    manual/lua_conversion/detail/callback_to_lua.hpp
    manual/lua_conversion/detail/binding_macros.hpp
    manual/lua_conversion/detail/binding_macros_base.hpp
    manual/lua_conversion/detail/cocos/object.hpp
    manual/lua_conversion/detail/cocos/containers.hpp
    manual/lua_conversion/detail/record.hpp
    manual/lua_conversion/detail/cocos/navmesh.hpp
    manual/lua_conversion/detail/cocos/value_types.hpp
    manual/lua_conversion/detail/cocos/render_types.hpp
    manual/lua_conversion/detail/cocos/particle_types.hpp
    manual/lua_conversion/detail/cocos/geometry.hpp
    manual/lua_conversion/detail/cocos/physics.hpp
    manual/lua_conversion/detail/cocos/assets_manager.hpp
    manual/lua_conversion/detail/cocos/app_directories.hpp
    manual/platform/ios/LuaObjcBridge.h
    manual/network/cclua_network_manual.h
    manual/network/lua_xml_http_request.h
    manual/network/lua_downloader.h
    manual/Lua-BindingsExport.h
    manual/tolua_fix.h
    manual/base/LuaScriptHandlerMgr.h
    manual/base/cclua_base_manual.hpp
    manual/base/cclua_file_read.hpp
    manual/CcluaLoader.h
    manual/LuaValue.h
    manual/physics3d/cclua_physics3d_manual.h
    manual/ui/cclua_ui_manual.hpp
    manual/ui/cclua_ui_values.hpp
    )

set(lua_bindings_manual_files
    manual/LuaBridge.cpp
    manual/LuaEngine.cpp
    manual/LuaStack.cpp
    manual/LuaValue.cpp
    manual/CcluaLoader.cpp
    manual/LuaBasicConversions.cpp
    manual/gamepad/cclua_gamepad.cpp
    manual/lua_module_register.cpp
    manual/cclua_file_dialog.cpp
    manual/tolua_fix.cpp
    manual/ComponentLua.cpp
    manual/base/LuaScriptHandlerMgr.cpp
    manual/base/cclua_base_manual.cpp
    manual/base/cclua_font_manual.cpp
    manual/base/cclua_file_read.cpp
    manual/base/cclua_zip.cpp
    manual/physics/cclua_physics_manual.cpp
    manual/3d/cclua_3d_manual.cpp
    manual/network/cclua_network_manual.cpp
    manual/network/lua_xml_http_request.cpp
    manual/network/lua_downloader.cpp
    manual/ui/cclua_ui_manual.cpp
    manual/physics3d/cclua_physics3d_manual.cpp
    manual/physics3d/cclua_physics3d_retained.cpp
    )

set(lua_bindings_auto_headers
    auto/cclua_gamepad_auto.hpp
    auto/cclua_system_info_auto.hpp
    auto/cclua_3d_auto.hpp
    auto/cclua_geometry_auto.hpp
    auto/cclua_base_auto.hpp
    auto/cclua_navmesh_auto.hpp
    auto/cclua_physics3d_auto.hpp
    auto/cclua_ui_auto.hpp
    auto/cclua_physics_auto.hpp
    auto/cclua_extension_auto.hpp
    auto/cclua_backend_auto.hpp
    )

set(lua_bindings_auto_files
    auto/cclua_gamepad_auto.cpp
    auto/cclua_system_info_auto.cpp
    auto/cclua_3d_auto.cpp
    auto/cclua_geometry_auto.cpp
    auto/cclua_base_auto.cpp
    auto/cclua_base_auto01.cpp
    auto/cclua_base_auto02.cpp
    auto/cclua_base_auto03.cpp
    auto/cclua_base_auto04.cpp
    auto/cclua_base_auto05.cpp
    auto/cclua_base_auto06.cpp
    auto/cclua_base_retained.cpp
    auto/cclua_extension_auto.cpp
    auto/cclua_physics_auto.cpp
    auto/cclua_ui_auto.cpp
    auto/cclua_ui_auto01.cpp
    auto/cclua_ui_auto02.cpp
    auto/cclua_physics3d_auto.cpp
    auto/cclua_navmesh_auto.cpp
    auto/cclua_backend_auto.cpp
    manual/backend/cclua_backend_manual.cpp
    )

if(CC_ENABLE_EXT_SPINE)
    list(APPEND lua_bindings_manual_headers
        manual/spine/cclua_spine_manual.hpp
    )
    list(APPEND lua_bindings_manual_files
        manual/spine/cclua_spine_manual.cpp
    )
    list(APPEND lua_bindings_auto_headers
        auto/cclua_spine_auto.hpp
    )
    list(APPEND lua_bindings_auto_files
        auto/cclua_spine_auto.cpp
    )
endif()

if(APPLE)
    # LuaObjcBridge.mm needed by ios and mac
    set(lua_bindings_manual_headers
        ${lua_bindings_manual_headers}
        manual/platform/ios/LuaObjcBridge.h
        )
    set(lua_bindings_manual_files
        ${lua_bindings_manual_files}
        manual/platform/ios/LuaObjcBridge.mm
        )
endif()

# WebView has no macOS/tvOS backend. UI installs this single generated class
# only when its native implementation is also selected.
if(ANDROID OR (IOS AND NOT TVOS) OR (WINDOWS AND CC_ENABLE_MSEDGE_WEBVIEW2))
    list(APPEND lua_bindings_auto_headers auto/cclua_webview_auto.hpp)
    list(APPEND lua_bindings_auto_files auto/cclua_webview_auto.cpp)
endif()

if(CC_ENABLE_VIDEO_PLATFORM)
    list(APPEND lua_bindings_auto_headers auto/cclua_video_platform_auto.hpp)
    list(APPEND lua_bindings_auto_files auto/cclua_video_platform_auto.cpp)
endif()

if(CC_ENABLE_VIDEO_TEXTURE)
    list(APPEND lua_bindings_auto_headers auto/cclua_video_texture_auto.hpp)
    list(APPEND lua_bindings_auto_files auto/cclua_video_texture_auto.cpp)
    list(APPEND lua_bindings_manual_headers manual/cclua_video_texture_types.hpp)
endif()

set(lua_bindings_files
    ${lua_bindings_manual_files}
    ${lua_bindings_auto_files}
    ${_CC_DEPRECATED_SRC}
    )
set(lua_bindings_headers
    ${lua_bindings_manual_headers}
    ${lua_bindings_auto_headers}
    ${_CC_DEPRECATED_HEADER}
    )

set(lua_bindings_files
    ${lua_bindings_files}
    "${cocos_root}/external/yasio/bindings/lyasio.cpp"
    "manual/yasio_cclua.cpp")

list(APPEND lua_bindings_files ${lua_bindings_headers})

set(COCOS_LUA_LIB luacocos2d CACHE INTERNAL "The lua bindings lib name" )
set(COCOS_CORE_LIB cocos2d)

add_library(${COCOS_LUA_LIB} STATIC ${lua_bindings_files})
target_link_libraries(${COCOS_LUA_LIB} ${COCOS_CORE_LIB})
if(CC_EXTENSION_LIBS)
    # The archive's dependency contract must also work outside a host app.
    target_link_libraries(${COCOS_LUA_LIB} ${CC_EXTENSION_LIBS})
endif()
add_dependencies(${COCOS_LUA_LIB} ${COCOS_CORE_LIB})

if(MSVC)
    target_compile_options(${COCOS_LUA_LIB} PRIVATE /bigobj)
endif()

get_target_property(lua_ext_depend external CC_LUA_DEPEND)
target_link_libraries(${COCOS_LUA_LIB} ${lua_ext_depend})
if(CC_BUILD_SHARED_LIBS)
    # These bindings own native yasio calls; the core's private implementation
    # libraries are intentionally not part of its public link interface.
    target_link_libraries(${COCOS_LUA_LIB} yasio)
endif()

target_include_directories(${COCOS_LUA_LIB}
    PUBLIC ${cocos_root}/cocos
    PUBLIC ${cocos_root}/external
    PUBLIC ${cocos_root}/external/jni.hpp/include
    PUBLIC ${cocos_root}/external/lua
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/manual
    PRIVATE manual/platform/android
    PRIVATE manual/platform/android/jni
    PRIVATE ${cocos_root}/extensions/spine/runtime/include
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/manual
)

if(WINDOWS)
    target_compile_definitions(${COCOS_LUA_LIB} PUBLIC _USRLUASTATIC)
endif()

if(WINDOWS AND CC_ENABLE_VIDEO_PLATFORM)
    target_compile_definitions(${COCOS_LUA_LIB}
        PUBLIC CC_ENABLE_MFMEDIA=1
    )
endif()

set_target_properties(${COCOS_LUA_LIB}
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      FOLDER "Internal"
                      )

if(XCODE OR VS)
    cocos_mark_code_files("${COCOS_LUA_LIB}")
endif()

if(ANDROID)
    # Keep JNI entry points in a separate archive for whole-archive linking.
    add_library(lua_android_spec STATIC
        manual/platform/android/LuaJavaBridge.cpp
        manual/platform/android/jni/LuaBridge.cpp
    )

    get_target_property(lua_header ${COCOS_LUA_LIB} INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(tolua_header tolua INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(lua_android_spec
        PRIVATE ../..
        PRIVATE manual
        PRIVATE manual/platform/android
        PRIVATE ${lua_header}
        PRIVATE ${tolua_header}
        PRIVATE ../../../core
        PRIVATE ../../../thirdparty
        PRIVATE ../../../thirdparty/robin-map/include
        PRIVATE ../../../thirdparty/jni.hpp/include
    )
    target_link_libraries(lua_android_spec ${COCOS_LUA_LIB})
endif()
