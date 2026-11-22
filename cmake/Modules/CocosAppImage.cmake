include_guard(GLOBAL)

set(CC_APPIMAGE_LINUXDEPLOY "" CACHE FILEPATH "linuxdeploy executable used for AppImage staging")
set(CC_APPIMAGE_APPIMAGETOOL "" CACHE FILEPATH "appimagetool executable used to create AppImages")
set(CC_APPIMAGE_RUNTIME_FILE "" CACHE FILEPATH "Optional pinned AppImage type-2 runtime")

# RESOURCE_DIRS are copied beside the executable. RESOURCE_FILES are relative
# to the caller's source directory and keep their parent directories.
function(cocos_add_appimage target)
    cmake_parse_arguments(PARSE_ARGV 1 image "" "DESKTOP_FILE;ICON_FILE;APP_RUN"
        "RESOURCE_DIRS;RESOURCE_FILES")

    set(config "$<IF:$<BOOL:$<CONFIG>>,$<CONFIG>,NoConfig>")
    set(stage "${CMAKE_CURRENT_BINARY_DIR}/appimage-stage/${target}/${config}")
    set(output "${CMAKE_BINARY_DIR}/packages/${config}/${target}-${CMAKE_SYSTEM_PROCESSOR}.AppImage")
    set(script "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/appimage-${target}-${config}.cmake")
    file(GENERATE OUTPUT "${script}" CONTENT
"set(APPIMAGE_EXECUTABLE [==[$<TARGET_FILE:${target}>]==])
set(APPIMAGE_CONFIG [==[$<CONFIG>]==])
set(APPIMAGE_ARCHITECTURE [==[${CMAKE_SYSTEM_PROCESSOR}]==])
set(APPIMAGE_STAGE [==[${stage}]==])
set(APPIMAGE_OUTPUT [==[${output}]==])
set(APPIMAGE_SOURCE_DIR [==[${CMAKE_CURRENT_SOURCE_DIR}]==])
set(APPIMAGE_RESOURCE_DIRS [==[${image_RESOURCE_DIRS}]==])
set(APPIMAGE_RESOURCE_FILES [==[${image_RESOURCE_FILES}]==])
set(APPIMAGE_DESKTOP_FILE [==[${image_DESKTOP_FILE}]==])
set(APPIMAGE_ICON_FILE [==[${image_ICON_FILE}]==])
set(APPIMAGE_APP_RUN [==[${image_APP_RUN}]==])
set(APPIMAGE_LINUXDEPLOY [==[${CC_APPIMAGE_LINUXDEPLOY}]==])
set(APPIMAGE_APPIMAGETOOL [==[${CC_APPIMAGE_APPIMAGETOOL}]==])
set(APPIMAGE_RUNTIME_FILE [==[${CC_APPIMAGE_RUNTIME_FILE}]==])
include([==[${CMAKE_CURRENT_FUNCTION_LIST_DIR}/PackageAppImage.cmake]==])
")

    add_custom_target(appimage-${target}
        COMMAND "${CMAKE_COMMAND}" -P "${script}"
        BYPRODUCTS "${output}"
        COMMENT "Packaging ${target} as an AppImage"
        VERBATIM)
    add_dependencies(appimage-${target} ${target})
endfunction()
