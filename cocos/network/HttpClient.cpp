/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "network/HttpClient.h"
#include <errno.h>
#include "base/ccUtils.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "yasio/yasio.hpp"
#include "yasio/obstream.hpp"

using namespace yasio;

NS_CC_BEGIN

namespace network
{

static HttpClient* _httpClient = nullptr;  // pointer to singleton

template <typename _Cont, typename _Fty>
static void __clearQueueUnsafe(_Cont& queue, _Fty pred)
{
    for (auto it = queue.unsafe_begin(); it != queue.unsafe_end();)
    {
        if (!pred || pred((*it)))
        {
            (*it)->release();
            it = queue.unsafe_erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (_httpClient == nullptr)
    {
        _httpClient = new HttpClient();
    }

    return _httpClient;
}

void HttpClient::destroyInstance()
{
    if (nullptr == _httpClient)
    {
        CCLOG("HttpClient singleton is nullptr");
        return;
    }

    CCLOG("HttpClient::destroyInstance begin");
    delete _httpClient;
    _httpClient = nullptr;

    CCLOG("HttpClient::destroyInstance() finished!");
}

void HttpClient::enableCookies(const char* cookieFile)
{
    std::lock_guard<std::recursive_mutex> lock(_cookieFileMutex);
    if (cookieFile)
    {
        _cookieFilename = cookieFile;
    }
    else
    {
        _cookieFilename = (FileUtils::getInstance()->getNativeWritableAbsolutePath() + "cookieFile.txt");
    }

    if (!_cookie)
        _cookie = new HttpCookie();
    _cookie->setCookieFileName(_cookieFilename);
    _cookie->readFile();
}

void HttpClient::setSSLVerification(std::string_view caFile)
{
    std::lock_guard<std::recursive_mutex> lock(_sslCaFileMutex);
    _sslCaFilename = caFile;
    _service->set_option(yasio::YOPT_S_SSL_CACERT, _sslCaFilename.c_str());
}

HttpClient::HttpClient()
    : _isInited(false)
    , _dispatchOnWorkThread(false)
    , _timeoutForConnect(30)
    , _timeoutForRead(60)
    , _cookie(nullptr)
    , _clearResponsePredicate(nullptr)
{
    CCLOG("In the constructor of HttpClient!");
    _scheduler = Director::getInstance()->getScheduler();

    _service = new yasio::io_service(HttpClient::MAX_CHANNELS);
    _service->set_option(yasio::YOPT_S_FORWARD_EVENT, 1);
    _service->set_option(yasio::YOPT_S_DNS_QUERIES_TIMEOUT, 3);
    _service->set_option(yasio::YOPT_S_DNS_QUERIES_TRIES, 1);
    _service->start([=](yasio::event_ptr&& e) { handleNetworkEvent(e.get()); });

    for (int i = 0; i < HttpClient::MAX_CHANNELS; ++i)
    {
        _availChannelQueue.unsafe_emplace_back(i);
    }

    _scheduler->schedule([=](float) { dispatchResponseCallbacks(); }, this, 0, false, "#");

    _isInited = true;
}

HttpClient::~HttpClient()
{
    _scheduler->unscheduleAllForTarget(this);
    delete _service;

    clearPendingResponseQueue();
    clearFinishedResponseQueue();
    if (_cookie)
    {
        _cookie->writeFile();
        delete _cookie;
    }

    CCLOG("HttpClient destructor");
}

void HttpClient::setDispatchOnWorkThread(bool bVal)
{
    _scheduler->unscheduleAllForTarget(this);
    _dispatchOnWorkThread = bVal;
    if (!bVal)
        _scheduler->schedule([=](float) { dispatchResponseCallbacks(); }, this, 0, false, "#");
}

void HttpClient::handleNetworkStatusChanged()
{
    _service->set_option(YOPT_S_DNS_DIRTY, 1);
}

void HttpClient::setNameServers(std::string_view servers)
{
    _service->set_option(YOPT_S_DNS_LIST, servers.data());
}

yasio::io_service* HttpClient::getInternalService()
{
    return _service;
}

bool HttpClient::send(HttpRequest* request)
{
    if (!request)
        return false;

    auto response = new HttpResponse(request);
    processResponse(response, request->getUrl());
    response->release();
    return true;
}

HttpResponse* HttpClient::sendSync(HttpRequest* request)
{
    request->setSync(true);
    if (this->send(request))
        return request->wait();
    return nullptr;
}

int HttpClient::tryTakeAvailChannel()
{
    auto lck = _availChannelQueue.get_lock();
    if (!_availChannelQueue.empty())
    {
        int channel = _availChannelQueue.front();
        _availChannelQueue.pop_front();
        return channel;
    }
    return -1;
}

void HttpClient::processResponse(HttpResponse* response, std::string_view url)
{
    auto channelIndex = tryTakeAvailChannel();
    response->retain();

    if (channelIndex != -1)
    {
        if (response->prepareForProcess(url))
        {
            response->_responseHeaders.clear();  // redirect needs clear old response headers
            auto& requestUri       = response->getRequestUri();
            auto channelHandle     = _service->channel_at(channelIndex);
            channelHandle->ud_.ptr = response;
            _service->set_option(YOPT_C_REMOTE_ENDPOINT, channelIndex, requestUri.getHost().data(),
                                 (int)requestUri.getPort());
            if (requestUri.isSecure())
                _service->open(channelIndex, YCK_SSL_CLIENT);
            else
                _service->open(channelIndex, YCK_TCP_CLIENT);
        }
        else
        {
            finishResponse(response);
        }
    }
    else
    {
        _pendingResponseQueue.emplace_back(response);
    }
}

void HttpClient::handleNetworkEvent(yasio::io_event* event)
{
    int channelIndex       = event->cindex();
    auto channel           = _service->channel_at(event->cindex());
    HttpResponse* response = (HttpResponse*)channel->ud_.ptr;
    if (!response)
        return;

    bool responseFinished = response->isFinished();
    switch (event->kind())
    {
    case YEK_ON_PACKET:
        if (!responseFinished)
        {
            auto&& pkt = event->packet_view();
            response->handleInput(pkt.data(), pkt.size());
        }
        if (response->isFinished())
        {
            response->updateInternalCode(yasio::errc::eof);
            _service->close(event->cindex());
        }
        break;
    case YEK_ON_OPEN:
        if (event->status() == 0)
        {
            obstream obs;
            bool usePostData = false;
            auto request     = response->getHttpRequest();
            switch (request->getRequestType())
            {
            case HttpRequest::Type::GET:
                obs.write_bytes("GET");
                break;
            case HttpRequest::Type::POST:
                obs.write_bytes("POST");
                usePostData = true;
                break;
            case HttpRequest::Type::DELETE:
                obs.write_bytes("DELETE");
                break;
            case HttpRequest::Type::PUT:
                obs.write_bytes("PUT");
                usePostData = true;
                break;
            default:
                obs.write_bytes("GET");
                break;
            }
            obs.write_bytes(" ");

            auto& uri = response->getRequestUri();
            obs.write_bytes(uri.getPathEtc());

            obs.write_bytes(" HTTP/1.1\r\n");

            obs.write_bytes("Host: ");
            obs.write_bytes(uri.getHost());
            obs.write_bytes("\r\n");

            // process custom headers
            struct HeaderFlag
            {
                enum
                {
                    UESR_AGENT   = 1,
                    CONTENT_TYPE = 1 << 1,
                    ACCEPT       = 1 << 2,
                };
            };
            int headerFlags = 0;
            auto& headers   = request->getHeaders();
            if (!headers.empty())
            {
                using namespace cxx17;  // for string_view literal
                for (auto&& header : headers)
                {
                    obs.write_bytes(header);
                    obs.write_bytes("\r\n");

                    if (cxx20::ic::starts_with(cxx17::string_view{header}, "User-Agent:"_sv))
                        headerFlags |= HeaderFlag::UESR_AGENT;
                    else if (cxx20::ic::starts_with(cxx17::string_view{header}, "Content-Type:"_sv))
                        headerFlags |= HeaderFlag::CONTENT_TYPE;
                    else if (cxx20::ic::starts_with(cxx17::string_view{header}, "Accept:"_sv))
                        headerFlags |= HeaderFlag::ACCEPT;
                }
            }

            if (_cookie)
            {
                auto cookies = _cookie->checkAndGetFormatedMatchCookies(uri);
                if (!cookies.empty())
                {
                    obs.write_bytes("Cookie: ");
                    obs.write_bytes(cookies);
                }
            }

            if (!(headerFlags & HeaderFlag::UESR_AGENT))
                obs.write_bytes("User-Agent: yasio-http\r\n");

            if (!(headerFlags & HeaderFlag::ACCEPT))
                obs.write_bytes("Accept: */*;q=0.8\r\n");

            if (usePostData)
            {
                if (!(headerFlags & HeaderFlag::CONTENT_TYPE))
                    obs.write_bytes("Content-Type: application/x-www-form-urlencoded;charset=UTF-8\r\n");

                char strContentLength[128] = {0};
                auto requestData           = request->getRequestData();
                auto requestDataSize       = request->getRequestDataSize();
                snprintf(strContentLength, sizeof(strContentLength), "Content-Length: %d\r\n\r\n", static_cast<int>(requestDataSize));
                obs.write_bytes(strContentLength);

                if (requestData && requestDataSize > 0)
                    obs.write_bytes(cxx17::string_view{requestData, static_cast<size_t>(requestDataSize)});
            }
            else
            {
                obs.write_bytes("\r\n");
            }

            _service->write(event->transport(), std::move(obs.buffer()));

            auto& timerForRead = channel->get_user_timer();
            timerForRead.cancel(*_service);
            timerForRead.expires_from_now(std::chrono::seconds(this->_timeoutForRead));
            timerForRead.async_wait(*_service, [=](io_service& s) {
                response->updateInternalCode(yasio::errc::read_timeout);
                s.close(channelIndex);  // timeout
                return true;
            });
        }
        else
        {
            handleNetworkEOF(response, channel, event->status());
        }
        break;
    case YEK_ON_CLOSE:
        handleNetworkEOF(response, channel, event->status());
        break;
    }
}

void HttpClient::handleNetworkEOF(HttpResponse* response, yasio::io_channel* channel, int internalErrorCode)
{
    channel->get_user_timer().cancel(*_service);
    response->updateInternalCode(internalErrorCode);
    auto responseCode = response->getResponseCode();
    switch (responseCode)
    {
    case 301:
    case 302:
    case 307:
        if (response->increaseRedirectCount() < HttpClient::MAX_REDIRECT_COUNT)
        {
            auto iter = response->_responseHeaders.find("location");
            if (iter != response->_responseHeaders.end())
            {
                if (responseCode == 302)
                    response->getHttpRequest()->setRequestType(HttpRequest::Type::GET);
                CCLOG("Process url redirect (%d): %s", responseCode, iter->second.c_str());
                _availChannelQueue.push_front(channel->index());
                processResponse(response, iter->second);
                response->release();
                return;
            }
        }
    }

    finishResponse(response);

    // recycle channel
    channel->ud_.ptr = nullptr;
    _availChannelQueue.push_front(channel->index());

    // try process pending response
    auto lck = _pendingResponseQueue.get_lock();
    if (!_pendingResponseQueue.unsafe_empty())
    {
        auto pendingResponse = _pendingResponseQueue.unsafe_front();
        _pendingResponseQueue.unsafe_pop_front();
        lck.unlock();

        processResponse(pendingResponse, pendingResponse->getHttpRequest()->getUrl());
        pendingResponse->release();
    }
}

// Poll and notify main thread if responses exists in queue
void HttpClient::dispatchResponseCallbacks()
{
    if (_finishedResponseQueue.unsafe_empty())
        return;

    auto CC_UNUSED lck = _finishedResponseQueue.get_lock();
    if (!_finishedResponseQueue.unsafe_empty())
    {
        HttpResponse* response = _finishedResponseQueue.front();
        _finishedResponseQueue.pop_front();
        invokeResposneCallbackAndRelease(response);
    }
}

void HttpClient::finishResponse(HttpResponse* response)
{
    auto request   = response->getHttpRequest();
    auto syncState = request->getSyncState();

    if (_cookie)
    {
        auto cookieRange = response->getResponseHeaders().equal_range("set-cookie");
        for (auto cookieIt = cookieRange.first; cookieIt != cookieRange.second; ++cookieIt)
            _cookie->updateOrAddCookie(cookieIt->second, response->_requestUri);
    }

    if (!syncState)
    {
        if (_dispatchOnWorkThread || std::this_thread::get_id() == Director::getInstance()->getCocos2dThreadId())
            invokeResposneCallbackAndRelease(response);
        else
            _finishedResponseQueue.emplace_back(response);
    }
    else
    {
        syncState->set_value(response);
    }
}

void HttpClient::invokeResposneCallbackAndRelease(HttpResponse* response)
{
    HttpRequest* request                  = response->getHttpRequest();
    const ccHttpRequestCallback& callback = request->getCallback();

    if (callback != nullptr)
        callback(this, response);

    response->release();
}

void HttpClient::clearResponseQueue()
{
    clearPendingResponseQueue();
    clearFinishedResponseQueue();
}

void HttpClient::clearPendingResponseQueue()
{
    auto CC_UNUSED lck = _pendingResponseQueue.get_lock();
    __clearQueueUnsafe(_pendingResponseQueue, ClearResponsePredicate{});
}

void HttpClient::clearFinishedResponseQueue()
{
    auto CC_UNUSED lck = _finishedResponseQueue.get_lock();
    __clearQueueUnsafe(_finishedResponseQueue, ClearResponsePredicate{});
}

void HttpClient::setTimeoutForConnect(int value)
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForConnectMutex);
    _timeoutForConnect = value;
    _service->set_option(YOPT_S_CONNECT_TIMEOUT, value);
}

int HttpClient::getTimeoutForConnect()
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForConnectMutex);
    return _timeoutForConnect;
}

void HttpClient::setTimeoutForRead(int value)
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForReadMutex);
    _timeoutForRead = value;
}

int HttpClient::getTimeoutForRead()
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForReadMutex);
    return _timeoutForRead;
}

std::string_view HttpClient::getCookieFilename()
{
    std::lock_guard<std::recursive_mutex> lock(_cookieFileMutex);
    return _cookieFilename;
}

std::string_view HttpClient::getSSLVerification()
{
    std::lock_guard<std::recursive_mutex> lock(_sslCaFileMutex);
    return _sslCaFilename;
}

}  // namespace network

NS_CC_END
