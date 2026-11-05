# Video textures

Configure cocos-x with `-DCC_ENABLE_VIDEO_TEXTURE=ON` to build basic video
playback into `cocos2d` using the bundled FFmpeg 9.0 lite libraries.

Include `video/VideoPlayer.h` to play video through a sprite, or
`video/VideoDecoder.h` to access decoded frames directly. Standalone cocos-x
builds leave this option off by default. This option is independent of the
platform-native `cocos2d::ui::VideoPlayer`.
