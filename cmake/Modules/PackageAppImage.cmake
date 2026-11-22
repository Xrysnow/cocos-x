cmake_minimum_required(VERSION 3.28)

if(NOT IS_ABSOLUTE "${APPIMAGE_STAGE}" OR NOT EXISTS "${APPIMAGE_EXECUTABLE}")
    message(FATAL_ERROR "Run the appimage-<target> build target to package the application")
endif()

if(NOT APPIMAGE_LINUXDEPLOY)
    unset(APPIMAGE_LINUXDEPLOY)
    find_program(APPIMAGE_LINUXDEPLOY
        NAMES linuxdeploy "linuxdeploy-${APPIMAGE_ARCHITECTURE}.AppImage" REQUIRED)
endif()
if(NOT APPIMAGE_APPIMAGETOOL)
    unset(APPIMAGE_APPIMAGETOOL)
    find_program(APPIMAGE_APPIMAGETOOL
        NAMES appimagetool "appimagetool-${APPIMAGE_ARCHITECTURE}.AppImage" REQUIRED)
endif()
if(APPIMAGE_RUNTIME_FILE AND NOT EXISTS "${APPIMAGE_RUNTIME_FILE}")
    message(FATAL_ERROR "AppImage runtime does not exist: ${APPIMAGE_RUNTIME_FILE}")
endif()

# Each target/configuration owns its staging directory, including the temporary
# image. Recreate it so removing a resource cannot leave it in a later package.
file(MAKE_DIRECTORY "${APPIMAGE_STAGE}")
file(LOCK "${APPIMAGE_STAGE}.lock" GUARD PROCESS)
file(REMOVE_RECURSE "${APPIMAGE_STAGE}")
set(appdir "${APPIMAGE_STAGE}/AppDir")
set(bin "${appdir}/usr/bin")
file(MAKE_DIRECTORY "${bin}")

if(APPIMAGE_RESOURCE_DIRS)
    file(COPY ${APPIMAGE_RESOURCE_DIRS} DESTINATION "${bin}"
        PATTERN ".git" EXCLUDE
        PATTERN ".gitattributes" EXCLUDE
        PATTERN ".gitignore" EXCLUDE
        PATTERN ".github" EXCLUDE
        PATTERN ".idea" EXCLUDE
        PATTERN ".vscode" EXCLUDE
        PATTERN ".emmyrc.json" EXCLUDE)
endif()
foreach(resource IN LISTS APPIMAGE_RESOURCE_FILES)
    get_filename_component(parent "${resource}" DIRECTORY)
    file(COPY "${APPIMAGE_SOURCE_DIR}/${resource}" DESTINATION "${bin}/${parent}")
endforeach()

# Use the desktop file basename for the icon and give both names to linuxdeploy.
get_filename_component(desktop_name "${APPIMAGE_DESKTOP_FILE}" NAME)
get_filename_component(icon_name "${APPIMAGE_DESKTOP_FILE}" NAME_WLE)
get_filename_component(icon_extension "${APPIMAGE_ICON_FILE}" LAST_EXT)
set(desktop "${APPIMAGE_STAGE}/${desktop_name}")
set(icon "${APPIMAGE_STAGE}/${icon_name}${icon_extension}")
configure_file("${APPIMAGE_DESKTOP_FILE}" "${desktop}" @ONLY NEWLINE_STYLE UNIX)
file(COPY_FILE "${APPIMAGE_ICON_FILE}" "${icon}")

set(apprun_options)
if(APPIMAGE_APP_RUN)
    set(apprun "${APPIMAGE_STAGE}/AppRun")
    configure_file("${APPIMAGE_APP_RUN}" "${apprun}" @ONLY NEWLINE_STYLE UNIX
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    list(APPEND apprun_options --custom-apprun "${apprun}")
endif()

set(tool_environment "APPIMAGE_EXTRACT_AND_RUN=1")
if(APPIMAGE_CONFIG STREQUAL "Debug")
    list(APPEND tool_environment "NO_STRIP=1")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" -E env ${tool_environment}
    "${APPIMAGE_LINUXDEPLOY}" --appdir "${appdir}" --executable "${APPIMAGE_EXECUTABLE}"
    --desktop-file "${desktop}" --icon-file "${icon}" ${apprun_options}
    COMMAND_ERROR_IS_FATAL ANY)

# Check the packaged paths with the Linux loader's normal search environment.
get_filename_component(executable_name "${APPIMAGE_EXECUTABLE}" NAME)
set(staged_executable "${bin}/${executable_name}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E env --unset=LD_LIBRARY_PATH "LC_ALL=C"
    ldd "${staged_executable}"
    OUTPUT_VARIABLE dependencies COMMAND_ERROR_IS_FATAL ANY)
if(dependencies MATCHES "=>[ \t]+not found")
    message(FATAL_ERROR "Unresolved AppImage runtime dependencies:\n${dependencies}")
endif()

find_program(objdump NAMES objdump REQUIRED)
file(GLOB_RECURSE libraries LIST_DIRECTORIES FALSE "${appdir}/usr/lib/*.so*")
foreach(elf IN ITEMS "${staged_executable}" ${libraries})
    if(IS_SYMLINK "${elf}")
        continue()
    endif()
    execute_process(COMMAND "${objdump}" -p "${elf}"
        OUTPUT_VARIABLE dynamic COMMAND_ERROR_IS_FATAL ANY)
    if(dynamic MATCHES "[\r\n][ \t]*NEEDED[ \t]+[^\r\n]*/")
        message(FATAL_ERROR "Non-relocatable DT_NEEDED path in ${elf}")
    endif()
    string(REGEX MATCHALL "[\r\n][ \t]*(RPATH|RUNPATH)[ \t]+[^\r\n]+" search_paths "${dynamic}")
    foreach(line IN LISTS search_paths)
        string(REGEX REPLACE "^[\r\n \t]*(RPATH|RUNPATH)[ \t]+" "" path "${line}")
        string(STRIP "${path}" path)
        string(REPLACE ":" ";" entries "${path}")
        foreach(entry IN LISTS entries)
            if(NOT entry MATCHES "^\\$ORIGIN(/|$)")
                message(FATAL_ERROR "Non-relocatable runtime search path '${entry}' in ${elf}")
            endif()
        endforeach()
    endforeach()
endforeach()

set(runtime_options)
if(APPIMAGE_RUNTIME_FILE)
    list(APPEND runtime_options --runtime-file "${APPIMAGE_RUNTIME_FILE}")
endif()
get_filename_component(output_name "${APPIMAGE_OUTPUT}" NAME)
get_filename_component(output_dir "${APPIMAGE_OUTPUT}" DIRECTORY)
set(temporary_image "${APPIMAGE_STAGE}/${output_name}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E env "APPIMAGE_EXTRACT_AND_RUN=1"
    "${APPIMAGE_APPIMAGETOOL}" ${runtime_options} "${appdir}" "${temporary_image}"
    COMMAND_ERROR_IS_FATAL ANY)
file(MAKE_DIRECTORY "${output_dir}")
file(RENAME "${temporary_image}" "${APPIMAGE_OUTPUT}")
message(STATUS "AppImage packaged at ${APPIMAGE_OUTPUT}")
