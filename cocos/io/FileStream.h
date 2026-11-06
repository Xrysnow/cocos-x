#pragma once
#include "io/Stream.h"
#include "platform/CCFileStream.h"
#include <memory>
#include <string_view>

namespace cocos2d::io
{
using FileAccess = cocos2d::FileStream::Access;
using FileCreation = cocos2d::FileStream::Creation;
using FileOpenOptions = cocos2d::FileStream::OpenOptions;

// Raw file I/O; compose with BufferedStream for configurable user-space caching.
// All factories retain FileUtils::openFileStream's virtual backend hook.
class CC_DLL FileStream final : public Stream
{
public:
    FileStream(RefConstructionToken token, std::unique_ptr<cocos2d::FileStream> backend,
               FileOpenOptions options);
    ~FileStream() override;

    static Result<ThreadSafeRefPtr<FileStream>> open(std::string_view path, FileOpenOptions options = {});
    // Takes exclusive ownership, including on validation failure.
    static Result<ThreadSafeRefPtr<FileStream>> fromBackend(std::unique_ptr<cocos2d::FileStream> backend,
                                                          FileOpenOptions options = {});

    Capability capabilities() const noexcept override;
    bool isOpen() const noexcept override;
    IoResult read(void* destination, size_t length) override;
    IoResult write(const void* source, size_t length) override;
    Result<int64_t> tell() const override;
    Result<std::optional<int64_t>> size() const override;
    Status seek(SeekOrigin origin, int64_t offset) override;
    Status resize(int64_t length) override;
    Status flush() override;
    Status sync() override;
    Status close() override;

private:
    StreamError stateError() const;
    std::unique_ptr<cocos2d::FileStream> _backend;
    FileOpenOptions _options;
    mutable StreamError _fault{};
    Status _closeResult{};
};
}
