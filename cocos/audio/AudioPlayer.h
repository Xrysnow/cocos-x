/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2018 HALX99.
 Copyright (c) 2021 Bytedance Inc.

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

#pragma once

#include "platform/CCPlatformConfig.h"

#include <string>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "audio/AudioMacros.h"
#include "platform/CCPlatformMacros.h"
#include "audio/alconfig.h"

NS_CC_BEGIN

class AudioCache;
class AudioEngineImpl;

class CC_DLL AudioPlayer
{
    friend class AudioEngineImpl;

public:
    AudioPlayer();
    ~AudioPlayer();

    void destroy();

    // queue buffer related stuff
    bool setTime(float time);
    float getTime() { return _currTime; }
    bool setLoop(bool loop);

    bool isFinished() const;

protected:
    void setCache(AudioCache* cache);
    void rotateBufferThread(int offsetFrame);
    bool play2d();
#if defined(__APPLE__)
    void wakeupRotateThread();
#endif

    AudioCache* _audioCache;

    float _volume;
    bool _loop;
    std::function<void(AUDIO_ID, std::string_view)> _finishCallbak;

    bool _isDestroyed;
    bool _removeByAudioEngine;
    bool _ready;
    ALuint _alSource;

    // play by circular buffer
    float _currTime;
    bool _streamingSource;
    ALuint _bufferIds[QUEUEBUFFER_NUM];
    std::thread* _rotateBufferThread;
    std::condition_variable _sleepCondition;
    std::mutex _sleepMutex;
    bool _timeDirty;
    bool _isRotateThreadExited;
#if defined(__APPLE__)
    std::atomic_bool _needWakeupRotateThread;
#endif

    std::mutex _play2dMutex;

    unsigned int _id;
    friend class AudioEngineImpl;
};

NS_CC_END
