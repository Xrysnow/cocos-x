# Configure gfx as part of the existing cocos core, with no separate library.
function(cocos_add_gfx_sources target)
    if(WINDOWS)
        set(CC_USE_VULKAN ON)
        set(CC_USE_GLES3 ON)
        set(CC_USE_GLES2 ON)
        set(CC_USE_METAL OFF)
    elseif(ANDROID)
        set(CC_USE_VULKAN ON)
        set(CC_USE_GLES3 ON)
        set(CC_USE_GLES2 ON)
        set(CC_USE_METAL OFF)
    elseif(IOS)
        set(CC_USE_VULKAN ON)
        set(CC_USE_GLES3 OFF)
        set(CC_USE_GLES2 OFF)
        set(CC_USE_METAL ON)
    elseif(MACOSX)
        set(CC_USE_VULKAN OFF)
        set(CC_USE_GLES3 OFF)
        set(CC_USE_GLES2 OFF)
        set(CC_USE_METAL ON)
    else()
        set(CC_USE_VULKAN ON)
        set(CC_USE_GLES3 ON)
        set(CC_USE_GLES2 ON)
        set(CC_USE_METAL OFF)
    endif()

    set(gfx_src_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}")

    set(gfx_src
      base/Agent.h
      base/Assertf.h
      base/BinaryArchive.cpp
      base/BinaryArchive.h
      base/CachedArray.h
      base/CoreStd.h
      base/IndexHandle.h
      base/Log.cpp
      base/Log.h
      base/Macros.h
      base/Object.h
      base/Ptr.h
      base/Random.cpp
      base/Random.h
      base/RefCounted.cpp
      base/RefCounted.h
      base/RefMap.h
      base/RefVector.h
      base/StringHandle.cpp
      base/StringHandle.h
      base/StringPool.h
      base/StringUtil.cpp
      base/StringUtil.h
      base/ThreadPool.cpp
      base/ThreadPool.h
      base/Timer.cpp
      base/Timer.h
      base/TypeDef.h
      base/Utils.cpp
      base/Utils.h

      base/memory/CallStack.cpp
      base/memory/CallStack.h
      base/memory/Memory.h
      base/memory/MemoryHook.cpp
      base/memory/MemoryHook.h

      base/threading/ConditionVariable.h
      base/threading/ConditionVariable.cpp
      base/threading/SyncEvent.h
      base/threading/MessageQueue.h
      base/threading/MessageQueue.cpp
      base/threading/Semaphore.h
      base/threading/Semaphore.cpp
      base/threading/ThreadPool.h
      base/threading/ThreadPool.cpp
      base/threading/ThreadSafeCounter.h
      base/threading/ThreadSafeLinearAllocator.h
      base/threading/ThreadSafeLinearAllocator.cpp

      base/job-system/JobSystem.h

      math/Math.h

      backend/GFXDeviceManager.h
      backend/gfx-gles-common/GLESCommandPool.h
    )

    list(TRANSFORM gfx_src PREPEND "${gfx_src_dir}/")

    set(gfx_source_dirs
        backend/gfx-base
        backend/gfx-agent
        backend/gfx-validator
        backend/gfx-empty
        backend/frame-graph
    )
    if(CC_USE_VULKAN)
        list(APPEND gfx_source_dirs backend/gfx-vulkan)
    endif()
    if(CC_USE_METAL)
        list(APPEND gfx_source_dirs backend/gfx-metal)
        file(GLOB metal_src "${gfx_src_dir}/backend/gfx-metal/*.mm")
        list(APPEND gfx_src ${metal_src})
        if(MACOSX)
            # The Metal backend uses explicit retain/release; do not inherit ARC.
            set_property(SOURCE ${metal_src} TARGET_DIRECTORY ${target}
                APPEND PROPERTY COMPILE_OPTIONS -fno-objc-arc)
        endif()
    endif()
    if(CC_USE_GLES3)
        list(APPEND gfx_source_dirs backend/gfx-gles3)
    endif()
    if(CC_USE_GLES2)
        list(APPEND gfx_source_dirs backend/gfx-gles2)
    endif()
    if(USE_JOB_SYSTEM_TASKFLOW)
        list(APPEND gfx_source_dirs base/job-system/job-system-taskflow)
    elseif(USE_JOB_SYSTEM_TBB)
        list(APPEND gfx_source_dirs base/job-system/job-system-tbb)
    else()
        list(APPEND gfx_source_dirs base/job-system/job-system-dummy)
    endif()
    foreach(gfx_source_dir IN LISTS gfx_source_dirs)
        file(GLOB_RECURSE gfx_backend_src
            "${gfx_src_dir}/${gfx_source_dir}/*.cpp"
            "${gfx_src_dir}/${gfx_source_dir}/*.c"
            "${gfx_src_dir}/${gfx_source_dir}/*.hpp"
            "${gfx_src_dir}/${gfx_source_dir}/*.h"
        )
        list(APPEND gfx_src ${gfx_backend_src})
    endforeach()

    target_sources(${target} PRIVATE ${gfx_src})
    # Keep gfx independent of the cocos2d.h PCH and its host/platform macros.
    set_source_files_properties(${gfx_src} TARGET_DIRECTORY ${target}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

    if(CC_USE_VULKAN)
        target_compile_definitions(${target} PUBLIC VK_NO_PROTOTYPES)
        target_compile_definitions(${target} PUBLIC CC_USE_VULKAN)

        if(WINDOWS)
            target_compile_definitions(${target} PUBLIC VK_USE_PLATFORM_WIN32_KHR)
        elseif(ANDROID)
            target_compile_definitions(${target} PUBLIC VK_USE_PLATFORM_ANDROID_KHR)
        elseif(IOS)
            target_compile_definitions(${target} PUBLIC VK_USE_PLATFORM_IOS_MVK)
        elseif(MACOSX)
            target_compile_definitions(${target} PUBLIC VK_USE_PLATFORM_MACOS_MVK)
        else()
            target_compile_definitions(${target} PUBLIC VK_USE_PLATFORM_XCB_KHR)
        endif()
    endif()

    if(CC_USE_METAL)
        target_compile_definitions(${target} PUBLIC CC_USE_METAL)
    endif()

    if(CC_USE_GLES3)
        target_compile_definitions(${target} PUBLIC CC_USE_GLES3)
    endif()

    if(CC_USE_GLES2)
        target_compile_definitions(${target} PUBLIC CC_USE_GLES2)
    endif()

    if(USE_JOB_SYSTEM_TASKFLOW)
        target_include_directories(${target} PUBLIC
            ${COCOS2DX_ROOT_PATH}/external/taskflow
        )
    elseif(USE_JOB_SYSTEM_TBB)
        target_include_directories(${target} PUBLIC
            ${COCOS2DX_ROOT_PATH}/external/tbb/include
        )
    endif()

    target_compile_definitions(${target} PUBLIC
        NOMINMAX
        CC_USE_PROFILER=0
        USE_MEMORY_LEAK_DETECTOR=0
        $<IF:$<BOOL:${USE_JOB_SYSTEM_TBB}>,CC_USE_JOB_SYSTEM_TBB=1,CC_USE_JOB_SYSTEM_TBB=0>
        $<IF:$<BOOL:${USE_JOB_SYSTEM_TASKFLOW}>,CC_USE_JOB_SYSTEM_TASKFLOW=1,CC_USE_JOB_SYSTEM_TASKFLOW=0>
    )

    # Preserve the existing public include roots and their relative order.
    target_include_directories(${target} PUBLIC
        ${gfx_src_dir}
        ${gfx_src_dir}/backend
        ${gfx_src_dir}/external
        ${gfx_src_dir}/external/khronos
        ${COCOS2DX_ROOT_PATH}/cocos
        ${COCOS2DX_ROOT_PATH}/external
        ${COCOS2DX_ROOT_PATH}/external/glslang
    )

    # Shader compiler and optional TBB libraries are already supplied by external.
    # Common platform libraries and export definitions are configured on the core.
    if(CC_USE_METAL)
        target_link_libraries(${target} PRIVATE "-framework MetalPerformanceShaders")
        if(IOS)
            target_link_libraries(${target} PRIVATE "-framework CoreVideo")
        endif()
    endif()

    if(ANDROID AND CC_USE_VULKAN)
        set_source_files_properties(
            "${gfx_src_dir}/backend/gfx-vulkan/VKDevice.cpp"
            TARGET_DIRECTORY ${target}
            PROPERTIES COMPILE_FLAGS -Wno-nullability-completeness
        )
    endif()
endfunction()

cocos_add_gfx_sources(${COCOS_CORE_LIB})
