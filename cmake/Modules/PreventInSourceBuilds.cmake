# Adapted from ITKv4/CMake/PreventInSourceBuilds.cmake
#
# This function will prevent in-source builds
function(AssureOutOfSourceBuilds)
  # Resolve symlinks before comparing the source and build directories.
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}")
    message(FATAL_ERROR
      "Configure cocos-x in a separate build directory.\n"
      "  cmake -S \"${CMAKE_SOURCE_DIR}\" -B \"${CMAKE_SOURCE_DIR}/build\"")
  endif()
endfunction()

AssureOutOfSourceBuilds()

