option(AUDIO_USE_LIBVORBIS "Use libvorbis" ON)

set(COCOS_AUDIO_HEADER
    audio/AudioALSupport.h
    audio/AudioCommon.h
    audio/AudioDecoder.h
    audio/AudioDecoderFlac.h
    audio/AudioDecoderMp3.h
    audio/AudioDecoderVorbisStb.h
    audio/AudioDecoderWav.h
    audio/AudioEffect.h
    audio/AudioEngine.h
    audio/AudioFilter.h
    audio/AudioPool.h
    audio/AudioPlatform.h
    audio/AudioRecordingDevice.h
    audio/AudioSoundData.h
    audio/AudioSource.h
    audio/AudioStream.h
    audio/dr_flac.h
    audio/dr_mp3.h
    audio/NqrCommon.h
    audio/NqrDither.h
    audio/NqrRiffUtils.h
)

set(COCOS_AUDIO_SRC
    audio/AudioALSupport.cpp
    audio/AudioCommon.cpp
    audio/AudioDecoder.cpp
    audio/AudioDecoderFlac.cpp
    audio/AudioDecoderMp3.cpp
    audio/AudioDecoderVorbisStb.cpp
    audio/AudioDecoderWav.cpp
    audio/AudioEffect.cpp
    audio/AudioEngine.cpp
    audio/AudioFilter.cpp
    audio/AudioPool.cpp
    audio/AudioRecordingDevice.cpp
    audio/AudioSoundData.cpp
    audio/AudioSource.cpp
    audio/AudioStream.cpp
    audio/NqrCommon.cpp
    audio/NqrRiffUtils.cpp
    audio/stb_vorbis.c
)

if(AUDIO_USE_LIBVORBIS)
    list(APPEND COCOS_AUDIO_HEADER audio/AudioDecoderVorbis.h)
    list(APPEND COCOS_AUDIO_SRC audio/AudioDecoderVorbis.cpp)
endif()

if(IOS)
    list(APPEND COCOS_AUDIO_SRC audio/AudioPlatformApple.mm)
    set_source_files_properties(audio/AudioPlatformApple.mm PROPERTIES LANGUAGE OBJCXX)
    set_property(SOURCE audio/AudioPlatformApple.mm APPEND PROPERTY COMPILE_OPTIONS -fno-objc-arc)
endif()
