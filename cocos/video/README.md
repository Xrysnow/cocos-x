# Video textures

Configure cocos-x with `-DCC_ENABLE_VIDEO_TEXTURE=ON` to build basic video
playback into `cocos2d` using the bundled FFmpeg 9.0 lite libraries.

Include `video/VideoPlayer.h` to play video through a sprite, or
`video/VideoDecoder.h` to access decoded frames directly. Standalone cocos-x
builds leave this option off by default. This option is independent of the
platform-native `cocos2d::ui::VideoPlayer`.

Include `video/VideoDecoder.h` explicitly when calling methods on the
Decoder returned by a Player. `FFInfo.h` supplies the metadata returned by
`Decoder::getInfo()`. The decoder and metadata headers require FFmpeg's
libavutil types.

Path factories use `cocos2d::io::FileStream::open()` with the FileUtils search
paths. `Decoder::openStream`, `Decoder::createFromStream` and
`Player::createFromStream` accept an existing `cocos2d::io::StreamPtr` at
offset zero. Use a fresh stream for each session and keep other users off its
cursor until the decoder closes. The decoder retains the source for the
session. Hosts can pass a memory stream over an owned resource snapshot.

The decoder can read synchronous sequential sources when the container
supports sequential demuxing. Player stream inputs need the Seek capability
for stop and replay. Custom AVIO accepts a single input, and a container's
demuxer still determines whether a media timestamp can be sought.

Demuxing, codec, hardware, and frame queue implementation files live in
`video/ffmpeg/`. `VideoCommon.h` remains the logging and FFmpeg
compatibility header.

`VideoPlayback` owns the decoder, playback state, and media time. It
accepts caller-provided ticks and reports frames, end of stream, and
errors. `VideoPlayer` connects this session to the scene scheduler and
uploads frames to its sprite texture.

Player controls are `startPlayback`, `pausePlayback`, `resumePlayback`,
`stopPlayback`, and `seekFrame`. Set `video::PlayMode::MANUAL` in C++
or `video.PlayMode.MANUAL` in Lua to use `advance(seconds)` and
`advanceFrame()`. These methods drive the video explicitly.

`Player::createAsync(stream, cancel)` is a C++ entry point for prefetching
video on a worker. Pass a readable, seekable stream at offset zero with a
dedicated cursor. Ordinary file and memory streams use cooperative shutdown,
which waits for the current stream operation to return. An optional thread-safe
cancel hook can unblock pending operations and must return promptly. The hook
may run during a read, probe or seek. The worker retains the stream and owns the
decoder. Lua and rendering stay on the Player's thread.

Attach the returned Player to a running scene to publish frames. Opening and
seek return before the first or landing frame appears. Poll `getAsyncSnapshot()`
for state, errors, metadata and the last presented frame. `getDecoder()` returns
null for this entry point. A MANUAL advance can wait for a frame, and the session
accepts one pending MANUAL advance at a time. `closeAsync()` requests terminal
shutdown. The snapshot changes from `Closing` to `Closed` after worker exit.
If an input operation remains blocked, the session remains `Closing` and process
shutdown waits for the worker. File opening is performed by the caller before
passing its stream to `createAsync()`.
Node cleanup also closes the session. Detaching without cleanup pauses delivery
and audio output, and reattaching preserves the user's play/pause intent.

The RGBA pool shares a limit of three slots and 64 MiB across ready,
converting and last presented frames. The last frame supports screenshots,
so opening fails asynchronously if the image size leaves fewer than two slots.
The pool limit covers CPU output storage. Codec and graphics allocations have
their own lifetimes. The default worker skips audio decoding during playback
and exposes the container's audio track count in the snapshot.

## Opt-in audio (C++)

Initialize `cocos2d::AudioEngine` before starting an audio session, then use the
three-argument overload:

```cpp
auto player = video::Player::createAsync(std::move(stream), {},
    {video::PlayMode::REALTIME, true});
if (player) {
    scene->addChild(player);
    player->startPlayback();
}
```

The two-argument overload and all existing Lua factories stay silent. Audio
requires REALTIME when creating the session. Changing to STEP, FRAME or MANUAL
stops audio and rebases the decoder; returning to REALTIME seeks to the current
media position and prebuffers again. `setAudioVolume` accepts finite values,
clamps to [0, 1], and multiplies with the engine's master gain. `setAudioMuted`
only changes gain. It does not stop consumption or change the clock.

An opted-in REALTIME session follows the audio device's consumed samples at
normal speed. Scheduler `timeScale`, including zero, does not scale this clock.
With no audio track, or after the audio ends before video, it continues on a
1x monotonic clock. Pause/resume, scene exit/entry and audio-engine background
suspension gate progression; hiding the sprite does not. A standalone
`VideoPlayback` caller must supply its own scene gate with `setSceneActive`.

`AL_SOFT_source_latency` is optional. When its procedure is available and the
query succeeds, `AudioCalibrated` uses the measured latency. Otherwise playback
continues with core OpenAL sample offsets as `AudioUncalibrated`, with unknown
output latency. This reports device-consumption time, not a physical speaker
or screen synchronization guarantee. The `seconds` snapshot field remains the
last presented video PTS; `mediaSeconds` is the active media clock. Snapshots
also report clock validity, selected audio stream, suspension, buffer occupancy,
underruns, seek target/landing, and structured decoder/output failures.

The worker owns joint FFmpeg demuxing/decoding and a private OpenAL QUEUE source.
PCM is converted to 48 kHz stereo S16, in blocks of at most 20 ms. Start and
underrun recovery prebuffer 100 ms, with a 200 ms combined PCM limit and ten AL
buffers. Compressed packets have a separate 16 MiB/512-packet limit. Oversized
frames, pathological interleaving and unsupported timestamps/formats fail
explicitly instead of creating unbounded queues or silently disabling audio.
No-track input is valid; a selected track that cannot decode or output is an
error. Codec and resampler tails drain before audio completion is reported.

`seekTime(seconds)` accepts finite nonnegative media times within a known
duration, including its exact endpoint. The bool reports request acceptance;
asynchronous landing or failure appears in the snapshot. Seek invalidates old
audio and video generations immediately. Paused seeks publish a preview without
starting sound. `seekFrame` remains an estimated convenience for constant-rate
content. Device-context rebuilds invalidate the private source and trigger an
internal seek from the last valid media position; failure is observable.

Close video sessions and release their workers before `AudioEngine::end()`.
The cancellation hook is needed if a custom stream can remain blocked during
shutdown. Engine end/init is not a session restart interface. This host ordering
is required; device-generation checks protect late source destruction but do
not replace closing video sessions. A custom read that blocks across an entire
background/foreground cycle can hide suspension history from the worker; hosts
using such streams must explicitly freeze the session before suspending it.
