/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2022 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ui/UIVideoPlayer/UIVideoPlayer.h"

#if CC_ENABLE_VIDEO_PLATFORM && (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/CCFileUtils.h"
#include "base/CCRefPtr.h"
#include "ui/UIHelper.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <unordered_map>

USING_NS_CC;
using namespace cocos2d::ui;

namespace
{
constexpr auto videoHelperClassName = "org.cocos.lib.VideoHelper";
constexpr auto visibilityKey = "ui.video.visibility";
constexpr int quitFullscreen = 1000;

// Accessed only on the CocosEngine thread, including Java event delivery.
struct VideoEntry
{
    VideoPlayer* player;
    jlong generation = 0;
    jlong fullScreenRevision = 0;
    bool visible = false;
    bool inLifecycle = false;
    bool hasRect = false;
    std::array<int, 4> rect{};
};
std::unordered_map<int, VideoEntry> players;
int64_t nextPlayerId = 0;

jlong nextGeneration(int id)
{
    const auto it = players.find(id);
    return it == players.end() ? 0 : ++it->second.generation;
}

void setLifecycle(int id, bool active)
{
    const auto it = players.find(id);
    if (it != players.end()) it->second.inLifecycle = active;
}

void syncVisible(VideoPlayer* player, int id, bool entered)
{
    const auto it = players.find(id);
    if (it == players.end()) return;
    bool visible = entered;
    for (auto node = static_cast<Node*>(player); visible && node; node = node->getParent())
        visible = node->isVisible();
    if (it->second.visible != visible)
    {
        it->second.visible = visible;
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoVisible", id, visible);
    }
}

void syncRect(VideoPlayer* player, int id)
{
    const auto it = players.find(id);
    if (it == players.end() || !player->isRunning()) return;
    const auto bounds = Helper::convertBoundingBoxToScreen(player);
    const std::array<float, 4> values = {bounds.origin.x, bounds.origin.y, bounds.size.width, bounds.size.height};
    std::array<int, 4> rect;
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (!std::isfinite(values[i]) || values[i] <= static_cast<double>(std::numeric_limits<int>::min()) ||
            values[i] >= static_cast<double>(std::numeric_limits<int>::max())) return;
        rect[i] = static_cast<int>(std::round(values[i]));
    }
    rect[2] = std::max(0, rect[2]);
    rect[3] = std::max(0, rect[3]);
    if (!it->second.hasRect || it->second.rect != rect)
    {
        it->second.hasRect = true;
        it->second.rect = rect;
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoRect", id, rect[0], rect[1], rect[2], rect[3]);
    }
}
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_VideoHelper_nativeExecuteVideoCallback(
    JNIEnv*, jclass, jint id, jlong generation, jint event)
{
    const auto it = players.find(id);
    if (it == players.end() || it->second.generation != generation) return;
    if (event == static_cast<int>(VideoPlayer::EventType::PLAYING) &&
        (!it->second.visible || !it->second.player->isRunning())) return;
    RefPtr<VideoPlayer> keepAlive(it->second.player);
    keepAlive->onPlayEvent(event);
}

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_VideoHelper_nativeExitFullScreen(
    JNIEnv*, jclass, jint id, jlong revision)
{
    const auto it = players.find(id);
    if (it == players.end() || it->second.fullScreenRevision != revision) return;
    RefPtr<VideoPlayer> keepAlive(it->second.player);
    keepAlive->onPlayEvent(quitFullscreen);
}

VideoPlayer::VideoPlayer()
{
    if (nextPlayerId > std::numeric_limits<int>::max())
    {
        CCLOGERROR("Android video player handle space exhausted");
        return;
    }
    _videoPlayerIndex = static_cast<int>(nextPlayerId++);
    _videoSource = Source::FILENAME;
    players.emplace(_videoPlayerIndex, VideoEntry{this});
    JniHelper::callStaticVoidMethod(videoHelperClassName, "createVideoWidget", _videoPlayerIndex);
#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
}

VideoPlayer::~VideoPlayer()
{
    // Revoke native delivery before posting asynchronous UI destruction.
    players.erase(_videoPlayerIndex);
    JniHelper::callStaticVoidMethod(videoHelperClassName, "removeVideoWidget", _videoPlayerIndex);
}

void VideoPlayer::setFileName(std::string_view fileName)
{
    _videoSource = Source::FILENAME;
    _videoURL = FileUtils::getInstance()->fullPathForFilename(fileName);
    _isPlaying = false;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoFile", _videoPlayerIndex, _videoURL,
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::setURL(std::string_view videoUrl)
{
    _videoSource = Source::URL;
    _videoURL = videoUrl;
    _isPlaying = false;
    CCLOGERROR("Android platform video supports ordinary local files only");
    // Keep the public interface, but reject URL/asset input without opening it.
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoFile", _videoPlayerIndex, std::string{},
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::setLooping(bool looping)
{
    _isLooping = looping;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setLooping", _videoPlayerIndex, looping);
}

void VideoPlayer::setUserInputEnabled(bool enableInput)
{
    _isUserInputEnabled = enableInput;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setUserInputEnabled", _videoPlayerIndex, enableInput);
}

void VideoPlayer::setStyle(StyleType style) { _styleType = style; }

void VideoPlayer::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    Widget::draw(renderer, transform, flags);
    syncRect(this, _videoPlayerIndex);
#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode->clear();
    const auto size = getContentSize();
    const Point vertices[] = {Point::ZERO, Point(size.width, 0), Point(size.width, size.height), Point(0, size.height)};
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1, 1, 1, 1));
#endif
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    if (_fullScreenEnabled == enabled) return;
    _fullScreenEnabled = enabled;
    const auto it = players.find(_videoPlayerIndex);
    if (it != players.end())
        JniHelper::callStaticVoidMethod(videoHelperClassName, "setFullScreenEnabled", _videoPlayerIndex, enabled,
                                        ++it->second.fullScreenRevision);
}

bool VideoPlayer::isFullScreenEnabled() const { return _fullScreenEnabled; }

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    _keepAspectRatioEnabled = enable;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "setVideoKeepRatioEnabled", _videoPlayerIndex, enable);
}

void VideoPlayer::setPlayRate(float rate)
{
    if (rate != 1.0f) CCLOGERROR("Android platform video supports 1x playback only");
}

void VideoPlayer::play()
{
    JniHelper::callStaticVoidMethod(videoHelperClassName, "startVideo", _videoPlayerIndex,
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::pause()
{
    const auto it = players.find(_videoPlayerIndex);
    if (it != players.end() && it->second.inLifecycle)
    {
        Widget::pause();
        return;
    }
    _isPlaying = false;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "pauseVideo", _videoPlayerIndex,
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::resume()
{
    const auto it = players.find(_videoPlayerIndex);
    if (it != players.end() && it->second.inLifecycle)
    {
        Widget::resume();
        return;
    }
    JniHelper::callStaticVoidMethod(videoHelperClassName, "resumeVideo", _videoPlayerIndex,
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::stop()
{
    _isPlaying = false;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "stopVideo", _videoPlayerIndex,
                                    nextGeneration(_videoPlayerIndex));
}

void VideoPlayer::seekTo(float seconds)
{
    if (!std::isfinite(seconds) || seconds < 0 ||
        static_cast<double>(seconds) * 1000.0 >= static_cast<double>(std::numeric_limits<jlong>::max())) return;
    JniHelper::callStaticVoidMethod(videoHelperClassName, "seekVideoTo", _videoPlayerIndex,
                                    nextGeneration(_videoPlayerIndex), static_cast<jlong>(seconds * 1000.0));
}

bool VideoPlayer::isPlaying() const { return _isPlaying; }
bool VideoPlayer::isLooping() const { return _isLooping; }
bool VideoPlayer::isUserInputEnabled() const { return _isUserInputEnabled; }

void VideoPlayer::setVisible(bool visible)
{
    Widget::setVisible(visible);
    syncVisible(this, _videoPlayerIndex, isRunning());
}

void VideoPlayer::onEnter()
{
    RefPtr<VideoPlayer> keepAlive(this);
    setLifecycle(_videoPlayerIndex, true);
    Widget::onEnter();
    setLifecycle(_videoPlayerIndex, false);
    syncVisible(this, _videoPlayerIndex, true);
    syncRect(this, _videoPlayerIndex);
    // Visibility of an ancestor can change without this node being drawn.
    schedule([this](float) {
        syncVisible(this, _videoPlayerIndex, isRunning());
        syncRect(this, _videoPlayerIndex);
    }, visibilityKey);
}

void VideoPlayer::onExit()
{
    RefPtr<VideoPlayer> keepAlive(this);
    syncVisible(this, _videoPlayerIndex, false);
    unschedule(visibilityKey);
    _isPlaying = false;
    setLifecycle(_videoPlayerIndex, true);
    Widget::onExit();
    setLifecycle(_videoPlayerIndex, false);
}

void VideoPlayer::addEventListener(const ccVideoPlayerCallback& callback) { _eventCallback = callback; }

void VideoPlayer::onPlayEvent(int event)
{
    if (event == quitFullscreen)
    {
        _fullScreenEnabled = false;
        return;
    }
    if (event < static_cast<int>(EventType::PLAYING) || event > static_cast<int>(EventType::ERROR)) return;
    RefPtr<VideoPlayer> keepAlive(this);
    _isPlaying = event == static_cast<int>(EventType::PLAYING);
    const auto callback = _eventCallback;
    if (callback) callback(this, static_cast<EventType>(event));
}

Widget* VideoPlayer::createCloneInstance() { return VideoPlayer::create(); }

void VideoPlayer::copySpecialProperties(Widget* widget)
{
    const auto model = dynamic_cast<VideoPlayer*>(widget);
    if (!model) return;
    setLooping(model->_isLooping);
    setUserInputEnabled(model->_isUserInputEnabled);
    setStyle(model->_styleType);
    setKeepAspectRatioEnabled(model->_keepAspectRatioEnabled);
    setFullScreenEnabled(model->_fullScreenEnabled);
    if (!model->_videoURL.empty())
    {
        if (model->_videoSource == Source::FILENAME) setFileName(model->_videoURL);
        else setURL(model->_videoURL);
    }
    // A clone has its own handle and starts stopped, with no inherited listener.
}
#endif
