set(COCOS_BASE_HEADER
    base/astc.h
    base/pvr.h
    base/format.h
    base/Value.h
    base/EventListenerMouse.h
    base/atitc.h
    base/EventTouch.h
    base/Data.h
    base/ccMacros.h
    base/EventAcceleration.h
    base/EventListenerKeyboard.h
    base/Touch.h
    base/base64.h
    base/s3tc.h
    base/etc1.h
    base/etc2.h
    base/Console.h
    base/ccConstants.h
    base/Event.h
    base/ccTypes.h
    base/ccEnums.h
    base/AsyncTaskPool.h
    base/ccRandom.h
    base/Ref.h
    base/Profiling.h
    base/ObjectFactory.h
    base/Properties.h
    base/Vector.h
    base/EventCustom.h
    base/EventKeyboard.h
    base/NinePatchImageParser.h
    base/EventListenerCustom.h
    base/EventDispatcher.h
    base/ccUtils.h
    base/RefPtr.h
    base/Director.h
    base/EventListenerFocus.h
    base/UserDefault.h
    base/ccConfig.h
    base/ccFPSImages.h
    base/ZipUtils.h
    base/Map.h
    base/ccUTF8.h
    base/ScriptSupport.h
    base/EventFocus.h
    base/Configuration.h
    base/Protocols.h
    base/TGAlib.h
    base/EventMouse.h
    base/NS.h
    base/AutoreleasePool.h
    base/StencilStateManager.h
    base/EventListenerTouch.h
    base/EventListenerAcceleration.h
    base/firePngData.h
    base/EventListener.h
    base/Scheduler.h
    base/EventType.h
    base/SimpleTimer.h
    )

set(COCOS_BASE_SRC
    base/AsyncTaskPool.cpp
    base/AutoreleasePool.cpp
    base/Configuration.cpp
    base/Console.cpp
    base/Data.cpp
    base/NinePatchImageParser.cpp
    base/Director.cpp
    base/Event.cpp
    base/EventAcceleration.cpp
    base/EventCustom.cpp
    base/EventDispatcher.cpp
    base/EventFocus.cpp
    base/EventKeyboard.cpp
    base/EventListener.cpp
    base/EventListenerAcceleration.cpp
    base/EventListenerCustom.cpp
    base/EventListenerFocus.cpp
    base/EventListenerKeyboard.cpp
    base/EventListenerMouse.cpp
    base/EventListenerTouch.cpp
    base/EventMouse.cpp
    base/EventTouch.cpp
    base/NS.cpp
    base/Profiling.cpp
    base/Properties.cpp
    base/Ref.cpp
    base/Scheduler.cpp
    base/ScriptSupport.cpp
    base/Touch.cpp
    base/UserDefault.cpp
    base/Value.cpp
    base/ObjectFactory.cpp
    base/StencilStateManager.cpp
    base/TGAlib.cpp
    base/ZipUtils.cpp
    base/atitc.cpp
    base/base64.cpp
    base/ccFPSImages.cpp
    base/ccTypes.cpp
    base/ccUTF8.cpp
    base/ccUtils.cpp
    base/SimpleTimer.cpp
    base/etc1.cpp
    base/etc2.cpp
    base/pvr.cpp
    base/s3tc.cpp
    base/astc.cpp

    )

# Standalone foundations share the core target, but keep their original macro/PCH boundary.
set(COCOS_BASE_STANDALONE_HEADER
    base/Agent.h
    base/Assertf.h
    base/BinaryArchive.h
    base/CachedArray.h
    base/CoreStd.h
    base/IndexHandle.h
    base/Log.h
    base/Macros.h
    base/Object.h
    base/Ptr.h
    base/Random.h
    base/RefCounted.h
    base/RefCountedExport.h
    base/StringHash.h
    base/RefMap.h
    base/RefVector.h
    base/StringHandle.h
    base/StringPool.h
    base/StringUtil.h
    base/Timer.h
    base/TypeDef.h
    base/Utils.h
    base/job-system/JobSystem.h
    base/memory/CallStack.h
    base/memory/Memory.h
    base/memory/MemoryHook.h
    base/std/any.h
    base/std/container/array.h
    base/std/container/deque.h
    base/std/container/list.h
    base/std/container/map.h
    base/std/container/queue.h
    base/std/container/set.h
    base/std/container/string.h
    base/std/container/unordered_map.h
    base/std/container/unordered_set.h
    base/std/container/vector.h
    base/std/hash/hash.h
    base/std/optional.h
    base/std/variant.h
    base/threading/ConditionVariable.h
    base/threading/MessageQueue.h
    base/threading/ReadWriteLock.h
    base/threading/Semaphore.h
    base/threading/SyncEvent.h
    base/threading/ThreadPool.h
    base/threading/ThreadSafeCounter.h
    base/threading/ThreadSafeLinearAllocator.h
    )
set(COCOS_BASE_STANDALONE_SRC
    base/BinaryArchive.cpp
    base/Log.cpp
    base/Random.cpp
    base/RefCounted.cpp
    base/StringHandle.cpp
    base/StringUtil.cpp
    base/Timer.cpp
    base/Utils.cpp
    base/memory/CallStack.cpp
    base/memory/MemoryHook.cpp
    base/threading/ConditionVariable.cpp
    base/threading/MessageQueue.cpp
    base/threading/Semaphore.cpp
    base/threading/ThreadPool.cpp
    base/threading/ThreadSafeLinearAllocator.cpp
    )
list(APPEND COCOS_BASE_HEADER ${COCOS_BASE_STANDALONE_HEADER})
list(APPEND COCOS_BASE_SRC ${COCOS_BASE_STANDALONE_SRC})

# Called after the target and external dependencies have been configured.
function(cocos_configure_base target)
    set(base_src_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}")
    set(base_use_taskflow 0)
    set(base_use_tbb 0)
    if(USE_JOB_SYSTEM_TASKFLOW)
        set(base_job_backend job-system-taskflow)
        set(base_use_taskflow 1)
        target_include_directories(${target} PUBLIC
            ${COCOS2DX_ROOT_PATH}/external/taskflow)
    elseif(USE_JOB_SYSTEM_TBB)
        set(base_job_backend job-system-tbb)
        set(base_use_tbb 1)
        target_include_directories(${target} PUBLIC
            ${COCOS2DX_ROOT_PATH}/external/tbb/include)
    else()
        set(base_job_backend job-system-dummy)
    endif()
    file(GLOB base_job_src
        "${base_src_dir}/job-system/${base_job_backend}/*.cpp"
        "${base_src_dir}/job-system/${base_job_backend}/*.h"
    )
    target_sources(${target} PRIVATE ${base_job_src})
    target_compile_definitions(${target} PUBLIC
        CC_USE_JOB_SYSTEM_TASKFLOW=${base_use_taskflow}
        CC_USE_JOB_SYSTEM_TBB=${base_use_tbb}
    )
    # These files must not import cocos2d.h's host/platform macros through the PCH.
    set_source_files_properties(${COCOS_BASE_STANDALONE_SRC} ${base_job_src}
        TARGET_DIRECTORY ${target} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endfunction()
