/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2018-2020 HALX99.
 Copyright (c) 2021-2022 Bytedance Inc.

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

#define LOG_TAG "AudioPlayer"

#include "platform/CCPlatformConfig.h"
#include "audio/AudioPlayer.h"
#include "audio/AudioCache.h"
#include "platform/CCFileUtils.h"
#include "audio/AudioDecoder.h"
#include "audio/AudioDecoderManager.h"

#ifdef VERY_VERY_VERBOSE_LOGGING
#    define ALOGVV ALOGV
#else
#    define ALOGVV(...) \
        do              \
        {               \
        } while (false)
#endif

USING_NS_CC;

namespace
{
unsigned int __idIndex = 0;
}

AudioPlayer::AudioPlayer()
    : _audioCache(nullptr)
    , _finishCallbak(nullptr)
    , _isDestroyed(false)
    , _removeByAudioEngine(false)
    , _ready(false)
    , _currTime(0.0f)
    , _streamingSource(false)
    , _rotateBufferThread(nullptr)
    , _timeDirty(false)
    , _isRotateThreadExited(false)
#if defined(__APPLE__)
    , _needWakeupRotateThread(false)
#endif
    , _id(++__idIndex)
{
    memset(_bufferIds, 0, sizeof(_bufferIds));
}

AudioPlayer::~AudioPlayer()
{
    ALOGVV("~AudioPlayer() (%p), id=%u", this, _id);
    destroy();

    if (_streamingSource)
    {
        alDeleteBuffers(QUEUEBUFFER_NUM, _bufferIds);
    }
}

void AudioPlayer::destroy()
{
    std::unique_lock<std::mutex> lck(_play2dMutex);
    if (_isDestroyed)
        return;

    ALOGVV("AudioPlayer::destroy begin, id=%u", _id);

    _isDestroyed = true;

    do
    {
        if (_audioCache != nullptr)
        {
            if (_audioCache->_state == AudioCache::State::INITIAL)
            {
                ALOGV("AudioPlayer::destroy, id=%u, cache isn't ready!", _id);
                break;
            }

            while (!_audioCache->_isLoadingFinished)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        }

        if (_streamingSource)
        {
            if (_rotateBufferThread != nullptr)
            {
                while (!_isRotateThreadExited)
                {
                    _sleepCondition.notify_one();
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }

                if (_rotateBufferThread->joinable())
                {
                    _rotateBufferThread->join();
                }

                delete _rotateBufferThread;
                _rotateBufferThread = nullptr;
                ALOGVV("rotateBufferThread exited!");

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                // some specific OpenAL implement defects existed on iOS platform
                // refer to: https://github.com/cocos2d/cocos2d-x/issues/18597
                ALint sourceState;
                ALint bufferProcessed = 0;
                alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
                if (sourceState == AL_PLAYING)
                {
                    alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
                    while (bufferProcessed < QUEUEBUFFER_NUM)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(2));
                        alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
                    }
                    alSourceUnqueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
                    CHECK_AL_ERROR_DEBUG();
                }
                ALOGVV("UnqueueBuffers Before alSourceStop");
#endif
            }
        }
    } while (false);

    ALOGVV("Before alSourceStop");
    alSourceStop(_alSource);
    CHECK_AL_ERROR_DEBUG();
    ALOGVV("Before alSourcei");
    alSourcei(_alSource, AL_BUFFER, 0);
    CHECK_AL_ERROR_DEBUG();

    _removeByAudioEngine = true;

    _ready = false;
    ALOGVV("AudioPlayer::destroy end, id=%u", _id);
}

void AudioPlayer::setCache(AudioCache* cache)
{
    _audioCache = cache;
}

bool AudioPlayer::play2d()
{
    std::unique_lock<std::mutex> lck(_play2dMutex);
    ALOGV("AudioPlayer::play2d, _alSource: %u, player id=%u", _alSource, _id);

    if (_isDestroyed)
        return false;

    /*********************************************************************/
    /*       Note that it may be in sub thread or in main thread.       **/
    /*********************************************************************/
    bool ret = false;
    do
    {
        if (_audioCache->_state != AudioCache::State::READY)
        {
            ALOGE("alBuffer isn't ready for play!");
            break;
        }

        alSourcei(_alSource, AL_BUFFER, 0);
        CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_PITCH, 1.0f);
        CHECK_AL_ERROR_DEBUG();
        alSourcef(_alSource, AL_GAIN, _volume);
        CHECK_AL_ERROR_DEBUG();
        alSourcei(_alSource, AL_LOOPING, AL_FALSE);
        CHECK_AL_ERROR_DEBUG();

        if (_audioCache->_queBufferFrames == 0)
        {
            if (_loop)
            {
                alSourcei(_alSource, AL_LOOPING, AL_TRUE);
                CHECK_AL_ERROR_DEBUG();
            }
        }
        else
        {
            alGenBuffers(QUEUEBUFFER_NUM, _bufferIds);

            auto alError = alGetError();
            if (alError == AL_NO_ERROR)
            {
                for (int index = 0; index < QUEUEBUFFER_NUM; ++index)
                {
                    alBufferData(_bufferIds[index], _audioCache->_format, _audioCache->_queBuffers[index],
                                 _audioCache->_queBufferSize[index], _audioCache->_sampleRate);
                }
                CHECK_AL_ERROR_DEBUG();
            }
            else
            {
                ALOGE("%s:alGenBuffers error code:%x", __FUNCTION__, alError);
                break;
            }
            _streamingSource = true;
        }

        {
            std::unique_lock<std::mutex> lk(_sleepMutex);
            if (_isDestroyed)
                break;

            if (_streamingSource)
            {
                // To continuously stream audio from a source without interruption, buffer queuing is required.
                alSourceQueueBuffers(_alSource, QUEUEBUFFER_NUM, _bufferIds);
                CHECK_AL_ERROR_DEBUG();
                _rotateBufferThread = new std::thread(&AudioPlayer::rotateBufferThread, this,
                                                      _audioCache->_queBufferFrames * QUEUEBUFFER_NUM + 1);
            }
            else
            {
                alSourcei(_alSource, AL_BUFFER, _audioCache->_alBufferId);
                CHECK_AL_ERROR_DEBUG();
            }

            alSourcePlay(_alSource);
        }

        auto alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            ALOGE("%s:alSourcePlay error code:%x", __FUNCTION__, alError);
            break;
        }

        ALint state;
        alGetSourcei(_alSource, AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING)
            ALOGE("state isn't playing, %d, %s, cache id=%u, player id=%u", state, _audioCache->_fileFullPath.c_str(),
                  _audioCache->_id, _id);

        // OpenAL framework: sometime when switch audio too fast, the result state will error, but there is no any
        // alError, so just skip for workaround.
        assert(state == AL_PLAYING);
        _ready = true;
        ret    = true;
    } while (false);

    if (!ret)
    {
        _removeByAudioEngine = true;
    }

    return ret;
}

// rotateBufferThread is used to rotate alBufferData for _alSource when playing big audio file
void AudioPlayer::rotateBufferThread(int offsetFrame)
{
#if defined(__APPLE__)
    pthread_setname_np("ALStreaming");
#endif

    char* tmpBuffer           = nullptr;
    auto& fullPath            = _audioCache->_fileFullPath;
    AudioDecoder* decoder     = AudioDecoderManager::createDecoder(fullPath);
    long long rotateSleepTime = static_cast<long long>(QUEUEBUFFER_TIME_STEP * 1000) / 2;
    do
    {
        BREAK_IF(decoder == nullptr || !decoder->open(fullPath));

        uint32_t framesRead         = 0;
        const uint32_t framesToRead = _audioCache->_queBufferFrames;
        const uint32_t bufferSize   = decoder->framesToBytes(framesToRead);
#if CC_USE_ALSOFT
        const auto sourceFormat = decoder->getSourceFormat();
#endif
        tmpBuffer = (char*)malloc(bufferSize);
        memset(tmpBuffer, 0, bufferSize);

        if (offsetFrame != 0)
        {
            decoder->seek(offsetFrame);
        }

        ALint sourceState;
        ALint bufferProcessed = 0;
        bool needToExitThread = false;

        while (!_isDestroyed)
        {
            alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
            if (sourceState == AL_PLAYING)
            {
                alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &bufferProcessed);
                while (bufferProcessed > 0)
                {
                    bufferProcessed--;
                    if (_timeDirty)
                    {
                        _timeDirty  = false;
                        offsetFrame = _currTime * decoder->getSampleRate();
                        decoder->seek(offsetFrame);
                    }
                    else
                    {
                        _currTime += QUEUEBUFFER_TIME_STEP;
                        if (_currTime > _audioCache->_duration)
                        {
                            if (_loop)
                            {
                                _currTime = 0.0f;
                            }
                            else
                            {
                                _currTime = _audioCache->_duration;
                            }
                        }
                    }

                    framesRead = decoder->readFixedFrames(framesToRead, tmpBuffer);

                    if (framesRead == 0)
                    {
                        if (_loop)
                        {
                            decoder->seek(0);
                            framesRead = decoder->readFixedFrames(framesToRead, tmpBuffer);
                        }
                        else
                        {
                            needToExitThread = true;
                            break;
                        }
                    }
                    /*
                     While the source is playing, alSourceUnqueueBuffers can be called to remove buffers which have
                     already played. Those buffers can then be filled with new data or discarded. New or refilled
                     buffers can then be attached to the playing source using alSourceQueueBuffers. As long as there is
                     always a new buffer to play in the queue, the source will continue to play.
                     */
                    ALuint bid;
                    alSourceUnqueueBuffers(_alSource, 1, &bid);
#if CC_USE_ALSOFT
                    if (sourceFormat == AUDIO_SOURCE_FORMAT::ADPCM || sourceFormat == AUDIO_SOURCE_FORMAT::IMA_ADPCM)
                        alBufferi(bid, AL_UNPACK_BLOCK_ALIGNMENT_SOFT, decoder->getSamplesPerBlock());
#endif
                    alBufferData(bid, _audioCache->_format, tmpBuffer, decoder->framesToBytes(framesRead),
                                 decoder->getSampleRate());
                    alSourceQueueBuffers(_alSource, 1, &bid);
                }
            }
            /* Make sure the source hasn't underrun */
            else if (sourceState != AL_PAUSED)
            {
                ALint queued;

                /* If no buffers are queued, playback is finished */
                alGetSourcei(_alSource, AL_BUFFERS_QUEUED, &queued);
                if (queued == 0)
                {
                    needToExitThread = true;
                }
                else
                {
                    alSourcePlay(_alSource);
                    if (alGetError() != AL_NO_ERROR)
                    {
                        ALOGE("Error restarting playback!");
                        needToExitThread = true;
                    }
                }
            }

            std::unique_lock<std::mutex> lk(_sleepMutex);
            if (_isDestroyed || needToExitThread)
            {
                break;
            }
#if defined(__APPLE__)
            if (!_needWakeupRotateThread)
            {
                _sleepCondition.wait_for(lk, std::chrono::milliseconds(rotateSleepTime));
            }

            _needWakeupRotateThread = false;
#else
            _sleepCondition.wait_for(lk, std::chrono::milliseconds(rotateSleepTime));
#endif
        }

    } while (false);

    ALOGVV("Exit rotate buffer thread ...");
    AudioDecoderManager::destroyDecoder(decoder);
    free(tmpBuffer);
    _isRotateThreadExited = true;
}

#if defined(__APPLE__)
void AudioPlayer::wakeupRotateThread()
{
    _needWakeupRotateThread = true;
    _sleepCondition.notify_all();
}
#endif

bool AudioPlayer::isFinished() const
{
    if (_streamingSource)
        return _isRotateThreadExited;
    else
    {
        ALint sourceState;
        alGetSourcei(_alSource, AL_SOURCE_STATE, &sourceState);
        return sourceState == AL_STOPPED;
    }
}

bool AudioPlayer::setLoop(bool loop)
{
    if (!_isDestroyed)
    {
        _loop = loop;
        return true;
    }

    return false;
}

bool AudioPlayer::setTime(float time)
{
    if (!_isDestroyed && time >= 0.0f && time < _audioCache->_duration)
    {

        _currTime  = time;
        _timeDirty = true;

        return true;
    }
    return false;
}
