# Platform video

`CC_ENABLE_VIDEO_PLATFORM` builds `cocos2d::ui::VideoPlayer` and its
`ccui.VideoPlayer` Lua bindings. It is independent of
`CC_ENABLE_VIDEO_TEXTURE`, which builds the FFmpeg sprite player.

Android and iOS (excluding tvOS) enable platform video by default. On Windows,
the initial default follows the legacy `CC_ENABLE_MFMEDIA` setting; an explicit
`CC_ENABLE_VIDEO_PLATFORM` value takes precedence. Other platforms reject ON.
The option controls native source selection, public declarations, and Lua
registration. Java host lifecycle wiring can remain present with the option
OFF; it has no native player instances to call.

## Android local files

Android uses `MediaPlayer` with a `SurfaceView` overlay. Call `setFileName()`
with an ordinary local file accessible to the application, then `play()`.
FileUtils resolves the path; Java verifies that the opened descriptor is a
regular file. URLs, APK assets, resource packages and arbitrary cocos streams
are outside this entry point. Unsupported inputs report `EventType::ERROR`
without a network request or automatic backend fallback.

The overlay supports a rectangular region, aspect-ratio preservation,
full-screen display, looping, and optional tap-to-pause/resume. Android's Back
button exits full screen before leaving the activity. Cocos clipping, opacity,
rotation, shaders and texture capture do not apply to this native surface;
use the FFmpeg sprite player when those features are needed. Playback rate is
1x. The system player owns its audio output and synchronization. Hosts remain
responsible for coordinating audio focus and game music; the helper does not
alter cocos audio's master volume.

`play()` starts from the beginning; `resume()` continues a paused position and
restarts completed playback. `stop()` pauses and rewinds, without emitting a
completion event. `seekTo()` accepts finite nonnegative seconds. A paused seek
keeps playback paused, and consecutive requests finish at the latest target.
Preparation and seeking are asynchronous. `isPlaying()` reflects delivered
player state, rather than merely accepting a play request.

All player and view operations execute on Android's UI thread. Events return
through the CocosEngine dispatcher before touching C++ or Lua. Independent
handles, command generations, media-player identities and host epochs reject
callbacks from replaced sources, destroyed nodes and previous activities.
Clones allocate independent handles and begin stopped without inherited
listeners.

Scene exit, visibility changes (including hidden ancestors), activity pause
and surface loss suspend output without replacing the user's play/pause
intent. Re-entry or a new surface resumes only a player that still intends to
play. Activity recreation releases old views and players, then restores the
source and position in the new host. Final activity destruction releases the
retained descriptors. Hiding this platform widget pauses it; this differs from
the FFmpeg sprite player's hidden-node behavior.

The helper keeps the UI and engine dispatch asynchronous in both directions;
it never waits for the UI from an engine callback. Release a node normally to
revoke its native handle before asynchronous Java cleanup.
