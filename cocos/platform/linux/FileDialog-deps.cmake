set(CC_FILE_DIALOG_LINUX_BACKEND "PORTAL" CACHE STRING "Linux file dialog backend")
set_property(CACHE CC_FILE_DIALOG_LINUX_BACKEND PROPERTY STRINGS PORTAL)
if(NOT CC_FILE_DIALOG_LINUX_BACKEND STREQUAL "PORTAL")
    message(FATAL_ERROR "CC_FILE_DIALOG_LINUX_BACKEND must be PORTAL")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED IMPORTED_TARGET dbus-1>=1.10)
target_link_libraries(${COCOS_CORE_LIB} PRIVATE PkgConfig::DBUS)

if(GLFW_BUILD_X11)
    target_compile_definitions(${COCOS_CORE_LIB} PRIVATE CC_DIALOG_X11=1)
endif()
if(GLFW_BUILD_WAYLAND)
    pkg_check_modules(CC_DIALOG_WAYLAND REQUIRED IMPORTED_TARGET wayland-client)
    pkg_check_modules(CC_DIALOG_WAYLAND_PROTOCOLS REQUIRED wayland-protocols)
    pkg_get_variable(_cc_dialog_wayland_data wayland-protocols pkgdatadir)
    find_program(CC_FILE_DIALOG_WAYLAND_SCANNER NAMES wayland-scanner REQUIRED)
    # xdg-foreign unstable v2 wire protocol, zxdg_exporter_v2 version 1.
    set(_cc_dialog_protocol "${_cc_dialog_wayland_data}/unstable/xdg-foreign/xdg-foreign-unstable-v2.xml")
    if(NOT EXISTS "${_cc_dialog_protocol}")
        message(FATAL_ERROR "wayland-protocols does not provide xdg-foreign-unstable-v2.xml")
    endif()
    set(_cc_dialog_generated "${CMAKE_CURRENT_BINARY_DIR}/file-dialog-protocol")
    set(_cc_dialog_protocol_code "${_cc_dialog_generated}/xdg-foreign-v2-protocol.c")
    set(_cc_dialog_protocol_header "${_cc_dialog_generated}/xdg-foreign-v2-client.h")
    add_custom_command(
        OUTPUT "${_cc_dialog_protocol_code}" "${_cc_dialog_protocol_header}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${_cc_dialog_generated}"
        COMMAND "${CC_FILE_DIALOG_WAYLAND_SCANNER}" private-code "${_cc_dialog_protocol}" "${_cc_dialog_protocol_code}"
        COMMAND "${CC_FILE_DIALOG_WAYLAND_SCANNER}" client-header "${_cc_dialog_protocol}" "${_cc_dialog_protocol_header}"
        DEPENDS "${_cc_dialog_protocol}"
        VERBATIM)
    target_sources(${COCOS_CORE_LIB} PRIVATE "${_cc_dialog_protocol_code}" "${_cc_dialog_protocol_header}")
    set_source_files_properties("${_cc_dialog_protocol_code}" PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
    target_include_directories(${COCOS_CORE_LIB} PRIVATE "${_cc_dialog_generated}")
    target_compile_definitions(${COCOS_CORE_LIB} PRIVATE CC_DIALOG_WAYLAND=1)
    target_link_libraries(${COCOS_CORE_LIB} PRIVATE PkgConfig::CC_DIALOG_WAYLAND)
endif()
