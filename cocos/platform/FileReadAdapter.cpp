#include "platform/FileReadAdapter.h"
#include <algorithm>
#include <climits>
#include <cerrno>
#include <cstdio>
#include <limits>

namespace cc
{
namespace {
class StreamBackend final : public FileStream {
public:
    explicit StreamBackend(io::StreamPtr stream) : _stream(std::move(stream)) {}
    ~StreamBackend() override { close(); }
    bool open(std::string_view, Mode) override { errno = ENOSYS; return false; }
    int close() override {
        if (!_stream) return 0;
        auto status = _stream->close();
        _stream = nullptr;
        if (status) return 0;
        errno = EIO;
        return -1;
    }
    bool isOpen() const override { return _stream && _stream->isOpen(); }
    int read(void* data, unsigned size) override {
        if (!_stream) { errno = EBADF; return -1; }
        auto r = _stream->read(data, std::min(size, unsigned(INT_MAX)));
        if (r || r.status == io::IoStatus::EndOfStream) return static_cast<int>(r.transferred);
        errno = EIO;
        return -1;
    }
    int write(const void*, unsigned) override { errno = EACCES; return -1; }
    int64_t tell() override {
        if (_stream) { auto result = _stream->tell(); if (result) return result.value; }
        errno = EIO;
        return -1;
    }
    int64_t size() override {
        if (_stream) { auto result = _stream->size(); if (result && result.value) return *result.value; }
        errno = EIO;
        return -1;
    }
    int seek(int64_t offset, int whence) override {
        if (!_stream || (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END)) {
            errno = EINVAL;
            return -1;
        }
        auto origin = whence == SEEK_SET ? io::SeekOrigin::Begin :
                      whence == SEEK_CUR ? io::SeekOrigin::Current : io::SeekOrigin::End;
        if (_stream->seek(origin, offset)) return 0;
        errno = EINVAL;
        return -1;
    }
private:
    io::StreamPtr _stream;
};
}
io::Result<ReadFile> readFileFromStream(io::StreamPtr stream)
{
    if (!stream || !io::hasCapability(stream->capabilities(), io::Capability::Read | io::Capability::Seek))
        return io::Result<ReadFile>::failure({io::ErrorCode::NotSupported});
    return io::Result<ReadFile>::success(std::make_unique<StreamBackend>(std::move(stream)));
}
}
