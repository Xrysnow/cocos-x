# The Windows cocos PCH includes yasio, which redefines EAGAIN as WSATRY_AGAIN.
# FFmpeg uses the C runtime errno value in these two translation units.
if(WIN32)
    set_source_files_properties(video/FFDemuxer.cpp video/FFInputStream.cpp
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif()

target_sources(${COCOS_CORE_LIB} PRIVATE
    video/FFCodec.cpp
    video/FFCodec.h
    video/FFDemuxer.cpp
    video/FFDemuxer.h
    video/FFFrameQueue.cpp
    video/FFFrameQueue.h
    video/FFFrameReceiver.h
    video/FFHardware.cpp
    video/FFHardware.h
    video/FFInfo.h
    video/FFInputStream.cpp
    video/FFInputStream.h
    video/FFPointer.h
    video/VideoCommon.cpp
    video/VideoCommon.h
    video/VideoDecoder.cpp
    video/VideoDecoder.h
    video/VideoPlayer.cpp
    video/VideoPlayer.h
    video/VideoStream.h
)
