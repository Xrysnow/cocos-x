include(io/core/CMakeLists.txt)
include(io/zip/CMakeLists.txt)

set(COCOS_IO_HEADER ${COCOS_IO_CORE_HEADER} ${COCOS_IO_ZIP_HEADER})
set(COCOS_IO_SRC ${COCOS_IO_CORE_SRC} ${COCOS_IO_ZIP_SRC})
