


# Extensions retain their static API even when their core dependency is a DLL.
set(BUILD_SHARED_LIBS OFF)

function(setup_ax_extension_config target_name)
    set(options DNTLINK opt_DNTLINK)
    cmake_parse_arguments(opt "" "${options}" ""
                          "" ${ARGN} )

  target_compile_features(${target_name} PUBLIC cxx_std_20)

  if(ANDROID)
    # An INTERFACE link does not apply cocos definitions to this target itself.
    target_compile_definitions(${target_name} PUBLIC CC_USE_GFX)
    target_link_libraries(${target_name} INTERFACE ${COCOS_CORE_LIB})
    target_include_directories(${target_name} PRIVATE $<TARGET_PROPERTY:${COCOS_CORE_LIB},INTERFACE_INCLUDE_DIRECTORIES>)
  else()
    target_link_libraries(${target_name} ${COCOS_CORE_LIB})
  endif()

  target_compile_definitions(${target_name} PUBLIC CC_EX_STATIC)

  set_target_properties(${target_name}
      PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      FOLDER "Extensions"
  )

  if(NOT opt_DNTLINK)
      set(CC_EXTENSION_LIBS "${target_name};${CC_EXTENSION_LIBS}" CACHE INTERNAL "extensions for auto link to target application" FORCE)
  endif()
  
  if(XCODE OR VS)
    cocos_mark_code_files("${target_name}")
  endif()

endfunction()

if(CC_ENABLE_EXT_GUI)
  add_subdirectory(GUI)
endif()

if(CC_ENABLE_EXT_ASSETMANAGER)
  add_subdirectory(assets-manager)
  if(CC_BUILD_SHARED_LIBS)
    target_link_libraries(assets-manager unzip dep_zlib)
  endif()
endif()

if(CC_ENABLE_EXT_PARTICLE3D)
  add_subdirectory(Particle3D)
endif()

if(CC_ENABLE_EXT_PHYSICS_NODE)
  add_subdirectory(physics-nodes)
  if(CC_BUILD_SHARED_LIBS)
    foreach(physics_dependency chipmunk box2d)
      if(TARGET ${physics_dependency})
        target_link_libraries(physics-nodes ${physics_dependency})
      endif()
    endforeach()
  endif()
endif()

if(CC_ENABLE_EXT_SPINE)
  add_subdirectory(spine)
endif()

if(CC_ENABLE_EXT_DRAGONBONES)
  add_subdirectory(DragonBones)
endif()

if(CC_ENABLE_EXT_FAIRYGUI)
  add_subdirectory(fairygui)
  if(CC_BUILD_SHARED_LIBS)
    target_link_libraries(fairygui pugixml)
  endif()
  if(TARGET spine)
    target_link_libraries(fairygui spine)
  else()
    target_include_directories(fairygui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/spine/runtime/include)
  endif()
endif()

if(CC_ENABLE_EXT_IMGUI)
  add_subdirectory(ImGui)
endif()

if(CC_ENABLE_EXT_LIVE2D)
  add_subdirectory(Live2D)
endif()

if (CC_ENABLE_EXT_EFFEKSEER)
  add_subdirectory(Effekseer)
endif()

message(STATUS "Enabled ${COCOS_CORE_LIB} extensions:${CC_EXTENSION_LIBS}")
