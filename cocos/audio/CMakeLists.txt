option(AUDIO_USE_LIBVORBIS "Use libvorbis" ON)

set(COCOS_AUDIO_HEADER
    audio/AudioALSupport.h
    audio/AudioCommon.h
    audio/AudioDecoder.h
    audio/AudioDirectPlayback.h
    audio/AudioEffect.h
    audio/AudioEngine.h
    audio/AudioFilter.h
    audio/AudioPool.h
    audio/AudioRecordingDevice.h
    audio/AudioSoundData.h
    audio/AudioSource.h
    audio/AudioStream.h
    audio/AudioStreamAdapter.h
    audio/codecs/AudioDecoderFlac.h
    audio/codecs/AudioDecoderMp3.h
    audio/codecs/AudioDecoderVorbisStb.h
    audio/codecs/AudioDecoderWav.h
    audio/codecs/third_party/NqrCommon.h
    audio/codecs/third_party/NqrDither.h
    audio/codecs/third_party/NqrRiffUtils.h
    audio/codecs/third_party/dr_flac.h
    audio/codecs/third_party/dr_mp3.h
    audio/output/AudioDirectBackend.h
    audio/output/AudioDirectInput.h
    audio/output/AudioDirectRenderer.h
    audio/output/AudioOutputEndpoints.h
    audio/output/AudioOutputIntegration.h
    audio/platform/AudioPlatform.h
)

set(COCOS_AUDIO_SRC
    audio/AudioCommon.cpp
    audio/AudioDecoder.cpp
    audio/AudioEffect.cpp
    audio/AudioEngine.cpp
    audio/AudioFilter.cpp
    audio/AudioRecordingDevice.cpp
    audio/AudioSoundData.cpp
    audio/AudioSource.cpp
    audio/AudioStream.cpp
    audio/AudioStreamAdapter.cpp
    audio/codecs/AudioDecoderFlac.cpp
    audio/codecs/AudioDecoderMp3.cpp
    audio/codecs/AudioDecoderVorbisStb.cpp
    audio/codecs/AudioDecoderWav.cpp
    audio/codecs/third_party/NqrCommon.cpp
    audio/codecs/third_party/NqrRiffUtils.cpp
    audio/codecs/third_party/stb_vorbis.c
    audio/openal/AudioALSupport.cpp
    audio/openal/AudioPool.cpp
    audio/output/AudioDirectPlayback.cpp
    audio/output/AudioDirectRenderer.cpp
    audio/output/AudioOutputEndpoints.cpp
)

if(AUDIO_USE_LIBVORBIS)
    list(APPEND COCOS_AUDIO_HEADER audio/codecs/AudioDecoderVorbis.h)
    list(APPEND COCOS_AUDIO_SRC audio/codecs/AudioDecoderVorbis.cpp)
endif()

if(IOS)
    list(APPEND COCOS_AUDIO_SRC audio/platform/AudioPlatformApple.mm)
    set_source_files_properties(audio/platform/AudioPlatformApple.mm PROPERTIES LANGUAGE OBJCXX)
    set_property(SOURCE audio/platform/AudioPlatformApple.mm APPEND PROPERTY COMPILE_OPTIONS -fno-objc-arc)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(AUDIO_PIPEWIRE QUIET IMPORTED_TARGET libpipewire-0.3>=0.3.50)
    endif()
endif()

if(WINDOWS)
    list(APPEND COCOS_AUDIO_SRC audio/output/AudioDirectBackendWin.cpp)
    set(COCOS_AUDIO_PLATFORM_LIBS ole32 uuid propsys)
elseif(TARGET PkgConfig::AUDIO_PIPEWIRE)
    list(APPEND COCOS_AUDIO_SRC audio/output/AudioDirectBackendPipeWire.cpp)
    set(COCOS_AUDIO_PLATFORM_LIBS PkgConfig::AUDIO_PIPEWIRE)
else()
    list(APPEND COCOS_AUDIO_SRC audio/output/AudioDirectBackendStub.cpp)
endif()
