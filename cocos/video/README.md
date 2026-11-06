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
