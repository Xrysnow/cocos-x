# Set the engine's platform flags and select its platform source folder.
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
    set(PLATFORM_FOLDER win32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(WIN64 TRUE)
    endif ()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(PLATFORM_FOLDER android)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if(ANDROID)
        set(PLATFORM_FOLDER android)
    else()
        set(LINUX TRUE)
        set(PLATFORM_FOLDER linux)
    endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(APPLE TRUE)
    set(MACOSX TRUE)
    set(PLATFORM_FOLDER mac)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "iOS")
    set(APPLE TRUE)
    set(IOS TRUE)
    set(PLATFORM_FOLDER ios)
else()
    message(FATAL_ERROR "Unsupported cocos-x target system: ${CMAKE_SYSTEM_NAME}")
    return()
endif()

# generators that are capable of organizing into a hierarchy of folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# simplify generator condition, please use them everywhere
if(CMAKE_GENERATOR STREQUAL Xcode)
    set(XCODE TRUE)
elseif(CMAKE_GENERATOR MATCHES Visual)
    set(VS TRUE)
endif()
message(STATUS "CMAKE_GENERATOR: ${CMAKE_GENERATOR}")

# custom target property for lua/js link
define_property(TARGET
    PROPERTY CC_JS_DEPEND
    BRIEF_DOCS "cocos2d js depend libs"
    FULL_DOCS "use to save depend libs of cocos2d js project"
) 
define_property(TARGET
    PROPERTY CC_LUA_DEPEND
    BRIEF_DOCS "cocos2d lua depend libs"
    FULL_DOCS "use to save depend libs of cocos2d lua project"
) 

# check c++ standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check the MSVC toolset on Windows.
if(WINDOWS)
    if(MSVC)
        if(MSVC_VERSION LESS 1930)
            message(FATAL_ERROR "cocos-x requires MSVC 1930 or newer. Found ${MSVC_VERSION}.")
        endif()
        message(STATUS "MSVC version: ${MSVC_VERSION}")
    else()
        message(FATAL_ERROR "Building cocos-x on Windows requires MSVC.")
    endif()
endif()

# Set macro definitions for special platforms
function(use_cocos2dx_compile_define target)
    target_compile_definitions(${target} PUBLIC $<$<CONFIG:Debug>:CC_DEBUG=1>)
    if(APPLE)
        target_compile_definitions(${target} PUBLIC __APPLE__)
        target_compile_definitions(${target} PUBLIC USE_FILE32API)
    elseif(LINUX)
        target_compile_definitions(${target} PUBLIC LINUX)
        target_compile_definitions(${target} PUBLIC _GNU_SOURCE)
    elseif(ANDROID)
        target_compile_definitions(${target} PUBLIC ANDROID)
        target_compile_definitions(${target} PUBLIC USE_FILE32API)
    elseif(WINDOWS)
        target_compile_definitions(${target} 
            PUBLIC WIN32
            PUBLIC _WIN32
            PUBLIC _WINDOWS
            PUBLIC UNICODE
            PUBLIC _UNICODE
            PUBLIC _CRT_SECURE_NO_WARNINGS
            PUBLIC _SCL_SECURE_NO_WARNINGS
        )
        if(BUILD_SHARED_LIBS)
            target_compile_definitions(${target} 
                PUBLIC _USRDLL
                PUBLIC _EXPORT_DLL_
                PUBLIC _USEGUIDLL
                PUBLIC _USREXDLL
                PUBLIC _USRSTUDIODLL
                PUBLIC _USE3DDLL
            )
        else()
            target_compile_definitions(${target} PUBLIC CC_STATIC)
        endif()
    endif()
    target_compile_definitions(${target} PUBLIC CC_USE_GFX)
    if(CC_ENABLE_EXT_GUI)
        target_compile_definitions(${target} PUBLIC CC_USE_EXT_GUI)
    endif()
    if(CC_ENABLE_EXT_ASSETMANAGER)
        target_compile_definitions(${target} PUBLIC CC_USE_ASSETMANAGER)
    endif()
    if(CC_ENABLE_EXT_PARTICLE3D)
        target_compile_definitions(${target} PUBLIC CC_USE_PARTICLE3D)
    endif()
    if(CC_ENABLE_EXT_PHYSICS_NODE)
        target_compile_definitions(${target} PUBLIC CC_USE_PHYSICS_NODE)
    endif()
    if(CC_ENABLE_EXT_SPINE)
        target_compile_definitions(${target} PUBLIC CC_USE_SPINE)
    endif()
    if(CC_ENABLE_EXT_DRAGONBONES)
        target_compile_definitions(${target} PUBLIC CC_USE_DRAGONBONES)
    endif()
    if(CC_ENABLE_EXT_COCOSTUDIO)
        target_compile_definitions(${target} PUBLIC CC_USE_COCOSTUDIO)
    endif()
    if(CC_ENABLE_EXT_FAIRYGUI)
        target_compile_definitions(${target} PUBLIC CC_USE_FAIRYGUI)
    endif()
    if(CC_ENABLE_EXT_LIVE2D)
        target_compile_definitions(${target} PUBLIC CC_USE_EXT_LIVE2D)
    endif()
    if(CC_ENABLE_EXT_EFFEKSEER)
        target_compile_definitions(${target} PUBLIC CC_USE_EFFEKSEER)
    endif()
    if(CC_ENABLE_EXT_IMGUI)
        target_compile_definitions(${target} PUBLIC CC_USE_EXT_IMGUI)
    endif()
endfunction()

 # Set compiler options
function(use_cocos2dx_compile_options target)
    if(MSVC)
        target_compile_options(${target}
            PUBLIC /MP
        )
    endif()
endfunction()
