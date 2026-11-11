# Build-tree imports for independently configured Windows DLL consumers.
# This package refers to the current source headers and prebuilt binary outputs;
# it does not configure, compile or install the engine in the consuming project.
function(cocos_collect_consumer_links consumer_target output)
    set(pending "${consumer_target}")
    set(visited)
    set(links)
    while(pending)
        list(POP_FRONT pending current)
        get_target_property(aliased "${current}" ALIASED_TARGET)
        if(aliased)
            set(current "${aliased}")
        endif()
        if(current IN_LIST visited)
            continue()
        endif()
        list(APPEND visited "${current}")
        get_target_property(current_type "${current}" TYPE)
        if(NOT current STREQUAL consumer_target)
            if(current STREQUAL "cocos2d")
                list(APPEND links CocosX::cocos2d)
            elseif(current_type STREQUAL "STATIC_LIBRARY" OR current_type STREQUAL "SHARED_LIBRARY")
                list(APPEND links "$<TARGET_LINKER_FILE:${current}>")
            endif()
        endif()
        # A DLL resolves its implementation dependencies itself. Only its
        # public interface can add libraries to an independent consumer link.
        if(current_type STREQUAL "SHARED_LIBRARY" OR current_type STREQUAL "MODULE_LIBRARY")
            set(link_properties INTERFACE_LINK_LIBRARIES)
        elseif(current_type STREQUAL "OBJECT_LIBRARY")
            # gfx objects belong exclusively to cocos2d.dll.
            continue()
        else()
            set(link_properties LINK_LIBRARIES INTERFACE_LINK_LIBRARIES)
        endif()
        foreach(link_property IN LISTS link_properties)
            get_target_property(current_links "${current}" "${link_property}")
            foreach(current_link IN LISTS current_links)
                if(current_link MATCHES "^\\$<(LINK_ONLY|BUILD_INTERFACE|TARGET_NAME_IF_EXISTS):([^<>]+)>$")
                    set(current_link "${CMAKE_MATCH_2}")
                endif()
                if(TARGET "${current_link}")
                    list(APPEND pending "${current_link}")
                elseif(current_link AND NOT current_link MATCHES "-NOTFOUND$|^::@|^\\$<")
                    list(APPEND links "${current_link}")
                endif()
            endforeach()
        endforeach()
    endwhile()
    list(REMOVE_DUPLICATES links)
    set(${output} "${links}" PARENT_SCOPE)
endfunction()

function(cocos_generate_shared_package)
    set(package_dir "${CMAKE_BINARY_DIR}/CocosX")
    file(MAKE_DIRECTORY "${package_dir}")
    configure_file("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/CocosSharedPackageConfig.cmake.in"
        "${package_dir}/CocosXConfig.cmake" @ONLY)

    set(package_extensions "${CC_EXTENSION_LIBS}")
    list(REMOVE_ITEM package_extensions "")
    list(REMOVE_DUPLICATES package_extensions)
    set(package_targets cocos2d ${package_extensions})
    if(TARGET luacocos2d)
        list(APPEND package_targets luacocos2d)
    endif()
    list(REMOVE_DUPLICATES package_targets)
    set(package_content "# Generated imports for this engine build and configuration.\n")
    set(runtime_dlls)
    set(runtime_modules)
    foreach(package_target IN LISTS package_targets)
        get_target_property(package_type "${package_target}" TYPE)
        if(package_type STREQUAL "SHARED_LIBRARY")
            set(import_type SHARED)
        elseif(package_type STREQUAL "STATIC_LIBRARY")
            set(import_type STATIC)
        else()
            continue()
        endif()
        string(APPEND package_content
            "add_library(CocosX::${package_target} ${import_type} IMPORTED)\n"
            "set_target_properties(CocosX::${package_target} PROPERTIES\n"
            "    IMPORTED_LOCATION [==[$<TARGET_FILE:${package_target}>]==]\n"
            "    INTERFACE_COMPILE_FEATURES cxx_std_20\n"
            "    INTERFACE_INCLUDE_DIRECTORIES [==[$<TARGET_GENEX_EVAL:${package_target},$<TARGET_PROPERTY:${package_target},INTERFACE_INCLUDE_DIRECTORIES>>]==]\n"
            "    INTERFACE_COMPILE_DEFINITIONS [==[$<TARGET_GENEX_EVAL:${package_target},$<TARGET_PROPERTY:${package_target},INTERFACE_COMPILE_DEFINITIONS>>]==]\n")
        if(import_type STREQUAL "SHARED")
            string(APPEND package_content
                "    IMPORTED_IMPLIB [==[$<TARGET_LINKER_FILE:${package_target}>]==]\n")
        endif()

        # Runtime deployment needs the full graph, including private DLL edges.
        search_depend_libs_recursive("${package_target}" package_depends)
        foreach(package_depend IN LISTS package_depends)
            get_target_property(depend_type "${package_depend}" TYPE)
            if(depend_type STREQUAL "SHARED_LIBRARY" OR depend_type STREQUAL "MODULE_LIBRARY")
                list(APPEND runtime_dlls "$<TARGET_FILE:${package_depend}>")
            endif()
            get_target_property(depend_modules "${package_depend}" CC_RUNTIME_MODULES)
            if(depend_modules)
                list(APPEND runtime_modules ${depend_modules})
            endif()
        endforeach()
        # A static module needs its own dependency closure, never the private
        # implementation archives hidden behind the core DLL boundary.
        cocos_collect_consumer_links("${package_target}" package_links)
        if(package_links)
            string(APPEND package_content
                "    INTERFACE_LINK_LIBRARIES [==[${package_links}]==]\n")
        endif()
        string(APPEND package_content ")\n")
    endforeach()

    set(extension_imports)
    foreach(extension_target IN LISTS package_extensions)
        list(APPEND extension_imports "CocosX::${extension_target}")
    endforeach()
    string(APPEND package_content
        "add_library(CocosX::extensions INTERFACE IMPORTED)\n"
        "set_property(TARGET CocosX::extensions PROPERTY INTERFACE_LINK_LIBRARIES [==[${extension_imports}]==])\n")
    list(REMOVE_DUPLICATES runtime_dlls)
    # Source/destination pairs are deliberately kept together. Repeated provider
    # pairs are harmless and avoid treating their two fields as independent IDs.
    string(APPEND package_content
        "set(CocosX_RUNTIME_DLLS [==[${runtime_dlls}]==])\n"
        "set(CocosX_RUNTIME_MODULES [==[${runtime_modules}]==])\n"
        "set(CocosX_CONFIGURATION [==[$<CONFIG>]==])\n")
    file(GENERATE OUTPUT "${package_dir}/CocosX-$<CONFIG>.cmake"
        CONTENT "${package_content}" TARGET cocos2d)
    message(STATUS "CocosX prebuilt DLL package: ${package_dir}")
endfunction()
