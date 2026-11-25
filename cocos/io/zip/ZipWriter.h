#pragma once
#include "io/zip/ZipTypes.h"
#include <string_view>
namespace cc::archive
{
class CC_DLL ZipWriter final {
public:
    using Ptr = std::unique_ptr<ZipWriter>;
    static io::Result<Ptr> begin(std::string_view path, WriteIntent intent, const ZipWriteOptions& options = {});
    ~ZipWriter();
    io::Status add(std::string_view name, Bytes bytes, const EntryWriteOptions& options = {});
    io::Status addFile(std::string_view name, std::string_view path, const EntryWriteOptions& options = {});
    io::Status addStream(std::string_view name, io::Stream& input, const EntryWriteOptions& options = {});
    io::Status replace(std::string_view name, Bytes bytes, const EntryWriteOptions& options = {});
    io::Status addDirectory(std::string_view name);
    io::Status rename(std::string_view from, std::string_view to);
    io::Status remove(std::string_view name);
    io::Status setArchiveComment(std::string_view comment);
    io::Status setEntryComment(std::string_view name, std::string_view comment);
    io::Status setEntryOptions(std::string_view name, const EntryWriteOptions& options);
    io::Status commit();
    void discard() noexcept;
private:
    struct State;
    explicit ZipWriter(std::unique_ptr<State>);
    io::Status putBytes(std::string_view name, Bytes, bool replace, const EntryWriteOptions&);
    std::unique_ptr<State> _state;
};
}
