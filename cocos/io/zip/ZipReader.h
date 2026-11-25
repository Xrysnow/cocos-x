#pragma once
#include "io/zip/ZipTypes.h"
#include <span>
#include <string_view>
namespace cc::archive
{
class CC_DLL ZipReader final {
public:
    using Ptr = std::shared_ptr<ZipReader>;
    static io::Result<Ptr> openFile(std::string_view nativePath, const ZipReadOptions& options = {});
    static io::Result<Ptr> openBuffer(Bytes bytes, const ZipReadOptions& options = {});
    static io::Result<Ptr> openStream(io::StreamPtr stream, const ZipReadOptions& options = {});
    std::span<const ZipEntryInfo> entries() const;
    io::Result<EntryId> find(std::string_view name) const;
    io::Result<io::StreamPtr> openEntry(EntryId id, const EntryReadOptions& options = {}) const;
    io::Result<Bytes> readEntry(EntryId id, const EntryReadOptions& options = {}) const;
    io::Status verify(EntryId id, const EntryReadOptions& options = {}) const;
    const std::string& sourceName() const;
    struct State;
private:
    explicit ZipReader(std::shared_ptr<State> state) : _state(std::move(state)) {}
    static io::Result<Ptr> index(std::shared_ptr<State> state, const ZipReadOptions& options);
    std::shared_ptr<State> _state;
};
}
