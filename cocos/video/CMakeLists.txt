# The Windows cocos PCH includes yasio, which redefines EAGAIN as WSATRY_AGAIN.
# FFmpeg uses the C runtime errno value in these two translation units.
if(WIN32)
    set_source_files_properties(video/ffmpeg/FFDemuxer.cpp video/ffmpeg/FFInputStream.cpp
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif()

target_sources(${COCOS_CORE_LIB} PRIVATE
    video/ffmpeg/FFAvio.cpp
    video/ffmpeg/FFAvio.h
    video/ffmpeg/FFCodec.cpp
    video/ffmpeg/FFCodec.h
    video/ffmpeg/FFDemuxer.cpp
    video/ffmpeg/FFDemuxer.h
    video/ffmpeg/FFFrameQueue.cpp
    video/ffmpeg/FFFrameQueue.h
    video/ffmpeg/FFFrameReceiver.h
    video/ffmpeg/FFHardware.cpp
    video/ffmpeg/FFHardware.h
    video/FFInfo.h
    video/ffmpeg/FFInputStream.cpp
    video/ffmpeg/FFInputStream.h
    video/ffmpeg/FFPointer.h
    video/VideoCommon.cpp
    video/VideoCommon.h
    video/VideoAsync.h
    video/VideoDecoder.cpp
    video/VideoDecoder.h
    video/VideoDecodeWorker.cpp
    video/VideoDecodeWorker.h
    video/VideoPlayMode.h
    video/VideoPlayback.cpp
    video/VideoPlayback.h
    video/VideoPlayer.cpp
    video/VideoPlayer.h
)
