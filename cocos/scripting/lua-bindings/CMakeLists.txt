set(cocos_root ${COCOS2DX_ROOT_PATH})

set(lua_bindings_manual_headers
    manual/CCComponentLua.h
    manual/3d/cclua_3d_manual.h
    manual/3d/cclua_geometry_compat.hpp
    manual/CCLuaStack.h
    manual/CCLuaEngine.h
    manual/lua_module_register.h
    manual/CCLuaBridge.h
    manual/extension/cclua_extension_manual.h
    manual/extension/cclua_extension_conversions.h
    manual/LuaBasicConversions.h
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
    manual/lua_conversion/detail/cocos/value_types.hpp
    manual/lua_conversion/detail/cocos/geometry.hpp
    manual/lua_conversion/detail/cocos/physics.hpp
    manual/lua_conversion/detail/cocos/app_directories.hpp
    manual/platform/ios/CCLuaObjcBridge.h
    manual/network/cclua_network_manual.h
    manual/network/lua_xml_http_request.h
    manual/network/lua_downloader.h
    manual/Lua-BindingsExport.h
    manual/tolua_fix.h
    manual/navmesh/cclua_navmesh_manual.h
    manual/navmesh/cclua_navmesh_conversions.h
    manual/navmesh/cclua_navmesh_compat.hpp
    manual/base/LuaScriptHandlerMgr.h
    manual/base/cclua_base_manual.hpp
    manual/CcluaLoader.h
    manual/CCLuaValue.h
    manual/physics3d/cclua_physics3d_manual.h
    manual/physics3d/cclua_physics3d_compat.hpp
    manual/ui/cclua_ui_manual.hpp
    manual/ui/cclua_ui_retained.hpp
    manual/ui/cclua_ui_events_compat.hpp
    manual/controller/cclua_controller_manual.hpp
    )

set(lua_bindings_manual_files
    manual/CCLuaBridge.cpp
    manual/CCLuaEngine.cpp
    manual/CCLuaStack.cpp
    manual/CCLuaValue.cpp
    manual/CcluaLoader.cpp
    manual/LuaBasicConversions.cpp
    manual/lua_module_register.cpp
    manual/tolua_fix.cpp
    manual/CCComponentLua.cpp
    manual/base/LuaScriptHandlerMgr.cpp
    manual/base/cclua_base_manual.cpp
    manual/physics/cclua_physics_manual.cpp
    manual/3d/cclua_3d_manual.cpp
    manual/controller/cclua_controller_manual.cpp
    manual/extension/cclua_extension_manual.cpp
    manual/network/cclua_network_manual.cpp
    manual/network/lua_xml_http_request.cpp
    manual/network/lua_downloader.cpp
    manual/ui/cclua_ui_manual.cpp
    manual/physics3d/cclua_physics3d_manual.cpp
    manual/physics3d/cclua_physics3d_retained.cpp
    manual/navmesh/cclua_navmesh_conversions.cpp
    manual/navmesh/cclua_navmesh_manual.cpp
    )

set(lua_bindings_auto_headers
    auto/cclua_3d_auto.hpp
    auto/cclua_geometry_auto.hpp
    auto/cclua_controller_auto.hpp
    auto/cclua_base_auto.hpp
    auto/cclua_navmesh_auto.hpp
    auto/cclua_physics3d_auto.hpp
    auto/cclua_ui_auto.hpp
    auto/cclua_ui_compat.hpp
    auto/cclua_ui_events_auto.hpp
    auto/cclua_physics_auto.hpp
    auto/cclua_extension_auto.hpp
    auto/cclua_backend_auto.hpp
    )

set(lua_bindings_auto_files
    auto/cclua_3d_auto.cpp
    auto/cclua_geometry_auto.cpp
    auto/cclua_base_auto.cpp
    auto/cclua_base_auto01.cpp
    auto/cclua_base_auto02.cpp
    auto/cclua_base_auto03.cpp
    auto/cclua_base_auto04.cpp
    auto/cclua_base_auto05.cpp
    auto/cclua_base_auto06.cpp
    auto/cclua_base_auto07.cpp
    auto/cclua_base_auto08.cpp
    auto/cclua_base_retained.cpp
    auto/cclua_controller_auto.cpp
    auto/cclua_extension_auto.cpp
    auto/cclua_physics_auto.cpp
    auto/cclua_ui_auto.cpp
    auto/cclua_ui_auto01.cpp
    auto/cclua_ui_auto02.cpp
    auto/cclua_ui_auto03.cpp
    auto/cclua_ui_auto04.cpp
    auto/cclua_ui_auto05.cpp
    auto/cclua_ui_auto06.cpp
    auto/cclua_ui_events_auto.cpp
    auto/cclua_physics3d_auto.cpp
    auto/cclua_physics3d_auto01.cpp
    auto/cclua_physics3d_auto02.cpp
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
if(CC_ENABLE_EXT_COCOSTUDIO)
    list(APPEND lua_bindings_manual_headers
        manual/cocostudio/lua-cocostudio-conversions.h
        manual/cocostudio/CustomGUIReader.h
        manual/cocostudio/cclua_csloader_manual.hpp
    )
    list(APPEND lua_bindings_manual_files
        manual/cocostudio/CustomGUIReader.cpp
        manual/cocostudio/cclua_cocostudio_manual.cpp
        manual/cocostudio/lua-cocostudio-conversions.cpp
        manual/cocostudio/cclua_csloader_manual.cpp
    )
    list(APPEND lua_bindings_auto_headers
        auto/cclua_studio_auto.hpp
        auto/cclua_studio_compat.hpp
        auto/cclua_csloader_auto.hpp
    )
    list(APPEND lua_bindings_auto_files
        auto/cclua_studio_auto.cpp
        auto/cclua_studio_auto01.cpp
        auto/cclua_studio_auto02.cpp
        auto/cclua_studio_auto03.cpp
        auto/cclua_studio_auto04.cpp
        auto/cclua_studio_auto05.cpp
        auto/cclua_studio_auto06.cpp
        auto/cclua_studio_auto07.cpp
        auto/cclua_studio_retained.cpp
        auto/cclua_csloader_auto.cpp
    )
endif()

if(APPLE)
    # CCLuaObjcBridge.mm needed by ios and mac
    set(lua_bindings_manual_headers
        ${lua_bindings_manual_headers}
        manual/platform/ios/CCLuaObjcBridge.h
        )
    set(lua_bindings_manual_files
        ${lua_bindings_manual_files}
        manual/platform/ios/CCLuaObjcBridge.mm
        )
    if(IOS)
        set(lua_bindings_manual_headers
            ${lua_bindings_manual_headers}
            manual/ui/cclua_webview_manual.hpp
            auto/cclua_webview_auto.hpp
            )
        set(lua_bindings_manual_files
            ${lua_bindings_manual_files}
            manual/ui/cclua_webview_manual.cpp
            auto/cclua_webview_auto.cpp
            )
    endif()
elseif(ANDROID)
    set(lua_bindings_manual_headers
        ${lua_bindings_manual_headers}
        manual/ui/cclua_webview_manual.hpp
        auto/cclua_webview_auto.hpp
        )
    set(lua_bindings_manual_files
        ${lua_bindings_manual_files}
        manual/ui/cclua_webview_manual.cpp
        auto/cclua_webview_auto.cpp
        )
elseif(WINDOWS)
    if(CC_ENABLE_MSEDGE_WEBVIEW2)
        set(lua_bindings_manual_headers
            ${lua_bindings_manual_headers}
            manual/ui/cclua_webview_manual.hpp
            auto/cclua_webview_auto.hpp
            )
        set(lua_bindings_manual_files
            ${lua_bindings_manual_files}
            manual/ui/cclua_webview_manual.cpp
            auto/cclua_webview_auto.cpp
            )
    endif()
endif()

if(CC_ENABLE_VIDEO_PLATFORM)
    list(APPEND lua_bindings_manual_headers
        auto/cclua_video_platform_auto.hpp
        manual/ui/cclua_video_platform_manual.hpp)
    list(APPEND lua_bindings_manual_files
        auto/cclua_video_platform_auto.cpp
        manual/ui/cclua_video_platform_manual.cpp)
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
add_dependencies(${COCOS_LUA_LIB} ${COCOS_CORE_LIB})

if(MSVC)
    target_compile_options(${COCOS_LUA_LIB} PRIVATE /bigobj)
endif()

get_target_property(lua_ext_depend external CC_LUA_DEPEND)
target_link_libraries(${COCOS_LUA_LIB} ${lua_ext_depend})

target_include_directories(${COCOS_LUA_LIB}
    PUBLIC ${cocos_root}/cocos
    PUBLIC ${cocos_root}/external
    PUBLIC ${cocos_root}/external/jni.hpp/include
    PUBLIC ${cocos_root}/external/lua
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/manual
    PRIVATE manual/platform/android
    PRIVATE manual/platform/android/jni
    PRIVATE ${cocos_root}/extensions/spine/runtime/include
    PRIVATE ${cocos_root}/extensions/cocostudio
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

if(CC_ENABLE_MSEDGE_WEBVIEW2)
    target_compile_definitions(${COCOS_LUA_LIB}
        PUBLIC CC_ENABLE_MSEDGE_WEBVIEW2=1
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
