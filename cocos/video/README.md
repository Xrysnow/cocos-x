# Video textures

Configure cocos-x with `-DCC_ENABLE_VIDEO_TEXTURE=ON` to build basic video
playback into `cocos2d` using the bundled FFmpeg 9.0 lite libraries.

Include `video/VideoPlayer.h` to play video through a sprite, or
`video/VideoDecoder.h` to access decoded frames directly. Standalone cocos-x
builds leave this option off by default. This option is independent of the
platform-native `cocos2d::ui::VideoPlayer`.

Include `video/VideoDecoder.h` explicitly when calling methods on the
Decoder returned by a Player. Include `video/VideoStream.h` when using
the stream interface. `FFInfo.h` supplies the metadata returned by
`Decoder::getInfo()`. The decoder and metadata headers require FFmpeg's
libavutil types.

Demuxing, codec, hardware, and frame queue implementation files live in
`video/ffmpeg/`. `VideoCommon.h` remains the logging and FFmpeg
compatibility header.
