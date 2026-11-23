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
Normal cocos platform initialization is required. Factories return owning
`cc::IntrusivePtr` handles and do not register their results with an autorelease pool.

A host may install `AudioStream::setFileOpener()` during initialization. It receives
the original path synchronously on the caller's thread and returns an owning
`cc::IntrusivePtr<AudioStream>`; a null result is a failure, with no automatic fallback. For explicit
fallback, call `createFromLocalFile()`, which bypasses the audio callback while
retaining FileUtils path and delegate behavior. Empty paths fail. Configure or
clear the callback only when there are no concurrent stream creation requests.
`AudioEngine::end()` keeps the callback; the host clears it at complete shutdown
with `setFileOpener({})`. Already created streams remain usable after clearing.

`AudioSource::createFromDecoder()` creates a streaming source. Initialize
`AudioEngine` before creating playback sources, check factory results, and keep the returned
handles for their intended playback lifetime: playback does not retain a source.
Release game/UI sources before ending the engine. Repeated `init()`/`end()` calls
are supported, with worker shutdown preceding OpenAL context destruction.
Independent consumers exercise these contracts in the workspace's
`tests/audio/standalone_consumer.cpp` and `tests/audio/standalone/CMakeLists.txt`.

Only file input is supplied by default. Generic memory input and LuaSTG resource
packages belong to host adapters. `AudioSoundData`, recording, PCM/static/queue
playback, filters, and effects remain core features. A decoder cloned through the
bare stream interface shares that stream's input cursor.

## Direct channel playback

`AudioEngine::getOutputEndpoints()` returns each current output connection, its
display name, whether it is the default, and its known channel positions. Retain
the opaque `AudioEndpointId` for that connection and enumerate again after
reconnection. Equal display names can refer to different connections. Windows uses
OpenAL Soft with WASAPI endpoints. Linux uses PipeWire when its development package
is available at configure time. Other builds report `Unsupported` for direct output.

Pass an `AudioSource`, endpoint ID, and channel map to `createDirectPlayback()`.
Each route has a zero-based `input` index and a named `output` position. One input
can feed several positions. Each output position can appear once per playback.
The playback starts in `Ready`. `play()` prebuffers. `pause()`, `resume()`,
`seekTime()`, `setLooping()`, `setGain()`, and `stop()` affect that playback only.
`snapshot()` reports the estimated position of consumed source PCM and the current
state. Keep the move-only handle while it plays. Its destructor and `close()` both
release the stream. `AudioEngine::end()` closes any surviving handles.

Direct output uses an independent stream for each playback. Unmapped positions in
its contribution are silent. The engine applies explicit gain and sample conversion.
The game listener and its effects do not process that stream. System mixing and
hardware processing still apply at the selected endpoint. Device integrations can
reserve particular output positions. Check `managed` in the endpoint descriptor
before offering a position for public routing.

Static playback retains immutable 8- or 16-bit PCM. A streaming `AudioSource`
created from a file decoder uses a fresh decoder and cursor per playback. The
source captures the file identity when opened. A host can supply a custom
`AudioSource::createFromReopenableStream()` factory that returns an independent,
owning stream positioned at byte zero. The factory may be called concurrently on
reader threads. Individual open and read calls must complete. Bare streams and
queue sources are unsupported. Start with mono or stereo WAV, Ogg Vorbis, FLAC,
or MP3 inputs.

## LuaSTG integration

LuaSTG owns `XAudioStream` and its resource FileOpener in `frameworks/Classes`,
and automatic/manual bindings in `frameworks/LuaBindings`. The core Lua
types are `cc.AudioEngine`, `cc.AudioSource`, `cc.AudioDecoder`, `cc.AudioStream`,
`cc.AudioSoundData`, and `cc.AudioRecordingDevice`. `audio.Engine`, `audio.Source`,
`audio.Decoder`, `audio.Stream`, `audio.SoundData`, and `audio.RecordingDevice`
are aliases of those same tables. Lua exposes direct output through both engine
names, using one-based source channel indices, positions such as `rearLeft`, and
opaque string IDs. A `cc.AudioDirectPlayback` userdata owns the C++ handle. The
host's file opener captures LuaSTG resource bytes, so existing playbacks can
continue after package unload, source release, or a same-name replacement.

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
Apple session/background handling is connected through `platform/AudioPlatformApple.mm`.
Platform wiring is not a claim of device validation. The workspace's P4 report in
`_research/audio-migration_2026-10-28` records actual Windows/Android build and
runtime coverage, the failed shared build, and untested platforms/hardware.
Large file-stream offsets do not imply every decoder/container supports them.

Public engine and input headers remain in `audio/`. Format implementations and
bundled decoding code live in `codecs/` and `codecs/third_party/`. The OpenAL
pool and extension support live in `openal/`. Endpoint discovery, playback
transport, and platform direct output live in `output/`.

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
