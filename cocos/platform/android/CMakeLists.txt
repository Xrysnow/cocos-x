# need to whole-archive this lib
set(target_name cpp_android_spec)

project(${target_name})

set(${target_name}_src
  CCDevice-android.cpp
  javaactivity-android.cpp
  jni/Java_org_cocos_lib_BitmapHelper.cpp
  jni/Java_org_cocos_lib_BitmapHelper.h
  jni/Java_org_cocos_lib_CocosAccelerometer.cpp
  jni/Java_org_cocos_lib_CocosEngine.cpp
  jni/Java_org_cocos_lib_CocosEngine.h
  jni/Java_org_cocos_lib_CocosRenderer.cpp
  jni/JniHelper.cpp
  jni/JniHelper.h
  jni/TouchesJni.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

if(NOT BUILD_SHARED_LIBS)
  target_link_libraries(${target_name} ${COCOS_CORE_LIB})
endif()

target_include_directories(${target_name}
  PRIVATE ..
  PRIVATE ../..
  PRIVATE ../../../external
  PRIVATE ../../../external/yasio
  PRIVATE ../../../external/glad/include
  PRIVATE ../../../external/robin-map/include
  PRIVATE ../../../external/jni.hpp/include
  PRIVATE ../../../external/fmt/include
)
