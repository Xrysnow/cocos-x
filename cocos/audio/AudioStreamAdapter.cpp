#include "audio/AudioStreamAdapter.h"
#include <limits>
#include <new>
#include <stdexcept>

NS_CC_BEGIN

AudioStreamAdapter::AudioStreamAdapter(RefConstructionToken token, io::StreamPtr stream)
    : AudioStream(token), _stream(std::move(stream))
{
    if (!_stream || getReferenceThreading() != RefThreading::Atomic)
        throw std::invalid_argument("AudioStreamAdapter requires Atomic ownership and a stream");
}

io::Result<ThreadSafeRefPtr<AudioStreamAdapter>> AudioStreamAdapter::create(io::StreamPtr stream)
{
    using Output = io::Result<ThreadSafeRefPtr<AudioStreamAdapter>>;
    if (!stream || !stream->isOpen())
        return Output::failure({io::ErrorCode::Closed});
    if (!io::hasCapability(stream->capabilities(), io::Capability::Read | io::Capability::Seek))
        return Output::failure({io::ErrorCode::NotSupported});
    const auto length = stream->size();
    if (!length) return Output::failure(length.error);
    if (!length.value) return Output::failure({io::ErrorCode::NotSupported});
    const auto position = stream->tell();
    if (!position) return Output::failure(position.error);
    if (*length.value < 0 || position.value < 0 || position.value > *length.value)
        return Output::failure({io::ErrorCode::OutOfRange});
    try
    {
        return Output::success(makeThreadSafeRef<AudioStreamAdapter>(std::move(stream)));
    }
    catch (const std::bad_alloc&) { return Output::failure({io::ErrorCode::OutOfMemory}); }
}

bool AudioStreamAdapter::fail(io::StreamError error)
{
    _lastResult = io::IoResult::failure(error);
    _failed = true;
    return false;
}

uint64_t AudioStreamAdapter::size()
{
    if (_failed) return 0;
    const auto result = _stream->size();
    if (!result)
        return fail(result.error), 0;
    if (!result.value || *result.value < 0)
        return fail({io::ErrorCode::InvalidBackend}), 0;
    return static_cast<uint64_t>(*result.value);
}

uint64_t AudioStreamAdapter::tell()
{
    if (_failed) return 0;
    const auto result = _stream->tell();
    if (!result)
        return fail(result.error), 0;
    if (result.value < 0)
        return fail({io::ErrorCode::InvalidBackend}), 0;
    return static_cast<uint64_t>(result.value);
}

bool AudioStreamAdapter::seek(SeekOrigin origin, int64_t offset)
{
    if (_failed) return false;
    io::SeekOrigin translated;
    switch (origin)
    {
    case SeekOrigin::BEGINNING: translated = io::SeekOrigin::Begin; break;
    case SeekOrigin::CURRENT: translated = io::SeekOrigin::Current; break;
    case SeekOrigin::END: translated = io::SeekOrigin::End; break;
    default:
        _lastResult = io::IoResult::failure({io::ErrorCode::InvalidArgument});
        return false;
    }
    const auto length = size();
    const auto position = tell();
    if (_failed) return false;
    const auto target = io::detail::seekTarget(translated, offset, static_cast<int64_t>(position),
                                              static_cast<int64_t>(length), false);
    if (!target)
    {
        _lastResult = io::IoResult::failure(target.error);
        return false;
    }
    const auto result = _stream->seek(io::SeekOrigin::Begin, target.value);
    if (!result)
        return fail(result.error);
    const auto actual = _stream->tell();
    if (!actual) return fail(actual.error);
    if (actual.value != target.value) return fail({io::ErrorCode::InvalidBackend});
    _lastResult = io::IoResult::success(0);
    return true;
}

bool AudioStreamAdapter::read(uint8_t* destination, uint64_t length, uint64_t* bytesRead)
{
    if (bytesRead) *bytesRead = 0;
    if (_failed) return false;
    if (length > std::numeric_limits<size_t>::max())
    {
        _lastResult = io::IoResult::failure({io::ErrorCode::Overflow});
        return false;
    }
    _lastResult = _stream->readExact(destination, static_cast<size_t>(length));
    if (bytesRead) *bytesRead = _lastResult.transferred;
    if (_lastResult.status == io::IoStatus::Error &&
        _lastResult.error.code != io::ErrorCode::InvalidArgument)
        _failed = true;
    return _lastResult.status == io::IoStatus::Ok && _lastResult.transferred == length;
}

void AudioStreamAdapter::lock() { _stream->lock(); }
void AudioStreamAdapter::unlock() { _stream->unlock(); }

NS_CC_END
