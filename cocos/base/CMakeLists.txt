
if(APPLE)
    set(COCOS_BASE_SPECIFIC_SRC
        base/CCController-apple.mm
        )

elseif(ANDROID)
    set(COCOS_BASE_SPECIFIC_SRC
        base/CCController-android.cpp
        )
elseif(LINUX OR WINDOWS)
    set(COCOS_BASE_SPECIFIC_SRC
        base/CCController-linux-win32.cpp
        )
endif()

set(COCOS_BASE_HEADER
    base/astc.h
    base/pvr.h
    base/format.h
    base/CCValue.h
    base/CCEventListenerMouse.h
    base/atitc.h
    base/CCEventTouch.h
    base/CCData.h
    base/ccMacros.h
    base/CCEventAcceleration.h
    base/CCEventListenerKeyboard.h
    base/CCController.h
    base/CCTouch.h
    base/base64.h
    base/CCEventListenerController.h
    base/s3tc.h
    base/etc1.h
    base/etc2.h
    base/CCGameController.h
    base/CCConsole.h
    base/ccConstants.h
    base/CCEvent.h
    base/ccTypes.h
    base/ccEnums.h
    base/CCAsyncTaskPool.h
    base/ccRandom.h
    base/CCRef.h
    base/CCProfiling.h
    base/ObjectFactory.h
    base/CCProperties.h
    base/CCVector.h
    base/CCEventCustom.h
    base/CCEventKeyboard.h
    base/CCNinePatchImageParser.h
    base/CCEventListenerCustom.h
    base/CCEventDispatcher.h
    base/ccUtils.h
    base/CCEventController.h
    base/CCRefPtr.h
    base/CCDirector.h
    base/CCEventListenerFocus.h
    base/CCUserDefault.h
    base/ccConfig.h
    base/ccFPSImages.h
    base/ZipUtils.h
    base/CCMap.h
    base/ccUTF8.h
    base/CCScriptSupport.h
    base/CCEventFocus.h
    base/CCConfiguration.h
    base/CCProtocols.h
    base/TGAlib.h
    base/CCEventMouse.h
    base/CCIMEDelegate.h
    base/CCNS.h
    base/CCAutoreleasePool.h
    base/CCStencilStateManager.h
    base/CCEventListenerTouch.h
    base/CCEventListenerAcceleration.h
    base/firePngData.h
    base/ccCArray.h
    base/CCEventListener.h
    base/CCScheduler.h
    base/CCEventType.h
    base/CCIMEDispatcher.h
    base/SimpleTimer.h
    )

set(COCOS_BASE_SRC
    base/CCAsyncTaskPool.cpp
    base/CCAutoreleasePool.cpp
    base/CCConfiguration.cpp
    base/CCConsole.cpp
    base/CCController.cpp
    base/CCData.cpp
    base/CCNinePatchImageParser.cpp
    base/CCDirector.cpp
    base/CCEvent.cpp
    base/CCEventAcceleration.cpp
    base/CCEventController.cpp
    base/CCEventCustom.cpp
    base/CCEventDispatcher.cpp
    base/CCEventFocus.cpp
    base/CCEventKeyboard.cpp
    base/CCEventListener.cpp
    base/CCEventListenerAcceleration.cpp
    base/CCEventListenerController.cpp
    base/CCEventListenerCustom.cpp
    base/CCEventListenerFocus.cpp
    base/CCEventListenerKeyboard.cpp
    base/CCEventListenerMouse.cpp
    base/CCEventListenerTouch.cpp
    base/CCEventMouse.cpp
    base/CCEventTouch.cpp
    base/CCIMEDispatcher.cpp
    base/CCNS.cpp
    base/CCProfiling.cpp
    base/CCProperties.cpp
    base/CCRef.cpp
    base/CCScheduler.cpp
    base/CCScriptSupport.cpp
    base/CCTouch.cpp
    base/CCUserDefault.cpp
    base/CCValue.cpp
    base/ObjectFactory.cpp
    base/CCStencilStateManager.cpp
    base/TGAlib.cpp
    base/ZipUtils.cpp
    base/atitc.cpp
    base/base64.cpp
    base/ccCArray.cpp
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
    ${COCOS_BASE_SPECIFIC_SRC}

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
    base/RefMap.h
    base/RefVector.h
    base/StringHandle.h
    base/StringPool.h
    base/StringUtil.h
    base/ThreadPool.h
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
    base/ThreadPool.cpp
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
