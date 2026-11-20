if(GLFW_BUILD_X11)
    # This adapter needs the same private platform definitions as GLFW itself.
    target_sources(glfw PRIVATE "${CMAKE_CURRENT_LIST_DIR}/TextInputX11-glfw.c")
    target_sources(${COCOS_CORE_LIB} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/TextInput-x11.cpp")
    target_compile_definitions(${COCOS_CORE_LIB} PRIVATE CC_GLFW_X11=1)
endif()

if(GLFW_BUILD_WAYLAND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CC_TEXT_INPUT_WAYLAND REQUIRED IMPORTED_TARGET wayland-client)
    pkg_get_variable(protocols wayland-protocols pkgdatadir)
    find_program(CC_TEXT_INPUT_SCANNER NAMES wayland-scanner REQUIRED)
    set(xml "${protocols}/unstable/text-input/text-input-unstable-v3.xml")
    set(generated "${CMAKE_CURRENT_BINARY_DIR}/text-input-protocol")
    set(header "${generated}/text-input-unstable-v3-client-protocol.h")
    set(code "${generated}/text-input-unstable-v3-protocol.c")
    add_custom_command(OUTPUT "${header}" "${code}"
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${generated}"
        COMMAND "${CC_TEXT_INPUT_SCANNER}" client-header "${xml}" "${header}"
        COMMAND "${CC_TEXT_INPUT_SCANNER}" private-code "${xml}" "${code}"
        DEPENDS "${xml}" VERBATIM)
    target_sources(${COCOS_CORE_LIB} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/TextInput-wayland.cpp" "${header}" "${code}")
    target_include_directories(${COCOS_CORE_LIB} PRIVATE "${generated}")
    target_link_libraries(${COCOS_CORE_LIB} PRIVATE PkgConfig::CC_TEXT_INPUT_WAYLAND)
    target_compile_definitions(${COCOS_CORE_LIB} PRIVATE CC_GLFW_WAYLAND=1)
endif()
