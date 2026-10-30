# cocos-x audio

The audio implementation is part of the `cocos2d` library. Include public headers
as `audio/AudioEngine.h`, `audio/AudioDecoder.h`, and `audio/AudioSource.h`, and use
the `cocos2d::Audio...` types. Consumers link `cocos2d` and its normal dependencies;
no separate `cc_audio` library or LuaSTG implementation objects are required.

## Files, custom input, and ownership

`AudioStream::createFromFile(path)` resolves and opens a file through cocos
`FileUtils` by default, using an independent file handle and cursor per stream.
`AudioDecoder::createFromFile(path, bufferSize, type)` uses this stream without
requiring an audio device. Explicit custom streams use `createFromStream()`.
Normal cocos platform initialization and an autorelease pool are required.

A host may install `AudioStream::setFileOpener()` during initialization. It receives
the original path synchronously on the caller's thread and returns an autoreleased
stream; a null result is a failure, with no automatic fallback. For explicit
fallback, call `createFromLocalFile()`, which bypasses the audio callback while
retaining FileUtils path and delegate behavior. Empty paths fail. Configure or
clear the callback only when there are no concurrent stream creation requests.
`AudioEngine::end()` keeps the callback; the host clears it at complete shutdown
with `setFileOpener({})`. Already created streams remain usable after clearing.

`AudioSource::createFromDecoder()` creates a streaming source. Initialize
`AudioEngine` before creating playback sources, check factory results, and retain
sources for their intended playback lifetime: playback does not retain a source.
Release game/UI sources before ending the engine. Repeated `init()`/`end()` calls
are supported, with worker shutdown preceding OpenAL context destruction.
Independent consumers exercise these contracts in the workspace's
`tests/audio/standalone_consumer.cpp` and `tests/audio/standalone/CMakeLists.txt`.

Only file input is supplied by default; generic memory input and LuaSTG resource
packages belong to host adapters. `AudioSoundData`, recording, PCM/static/queue
playback, filters, and effects remain core features. A raw PCM input wrapper is
not an encoded WAV/OGG file. Cloned decoders still share an input cursor and are
not independent concurrent readers.

## LuaSTG integration

LuaSTG owns `XAudioStream` and its resource FileOpener in `frameworks/Classes`,
and automatic/manual bindings in `frameworks/LuaBindings`. The six canonical Lua
types are `cc.AudioEngine`, `cc.AudioSource`, `cc.AudioDecoder`, `cc.AudioStream`,
`cc.AudioSoundData`, and `cc.AudioRecordingDevice`. `audio.Engine`, `audio.Source`,
`audio.Decoder`, `audio.Stream`, `audio.SoundData`, and `audio.RecordingDevice`
are aliases of those same tables. String/SoundData input factories are added by
the host's manual bindings. The core contains no Lua bindings or resource manager.

The old cocos playback-ID API, `play2d`, and `AudioProfile` are retired. Reusing
the `AudioEngine` name does not provide source or ABI compatibility with that API;
consumers must be rebuilt. Lua generator instructions live in the workspace's
`_misc/LuaBindingsGenerator` directory.

## Platforms and dependencies

* [OpenAL](http://www.openal.org/) or [OpenAL Soft](https://github.com/kcat/openal-soft).
* [libogg](https://www.xiph.org/ogg/) and [libvorbis](https://www.xiph.org/vorbis/)
  when `AUDIO_USE_LIBVORBIS=ON`; the bundled stb decoder is the OFF path.
* WAV, Ogg/Vorbis, FLAC, and MP3 decoding; A-B looping; audio effects and filters.

Android assets require the normal cocos AssetManager setup; OpenAL runtime
deployment and the recording-permission callback remain host/platform duties.
Apple session/background handling is connected through `AudioPlatformApple.mm`.
Platform wiring is not a claim of device validation. The workspace's P4 report in
`_research/audio-migration_2026-10-28` records actual Windows/Android build and
runtime coverage, the failed shared build, and untested platforms/hardware.
Large file-stream offsets do not imply every decoder/container supports them.

## Origin and licenses

This module came from the local `frameworks/Audio` working tree at commit
`54ec63e1b96d3dc48e69c32e663fafb4c6bd8b6b`, then received the namespace, input,
lifecycle, and decoder-wrapper changes recorded in the workspace's migration
reports. The retired standalone repository was removed from this workspace
after migration. The original MIT license remains in
[LICENSE](LICENSE); third-party source notices remain in their original files.
The migration did not download replacement decoder versions.

The original audio module is based on the audio engine of [LÖVE](https://love2d.org)
and uses code from [Libnyquist](https://github.com/ddiakopoulos/libnyquist),
[dr_libs](https://github.com/mackron/dr_libs), and the bundled stb Vorbis decoder.
