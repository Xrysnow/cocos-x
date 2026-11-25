#include "platform/FileDialogInternal.h"
#include "platform/AppDirectories.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <deque>

namespace cc::dialog {
namespace {
FileDialogError invalid(std::string message) { return {DialogErrorCode::InvalidArgument, std::move(message)}; }

struct DirectoryPage {
    std::string token;
    std::weak_ptr<DocumentProvider> owner;
    std::vector<DocumentHandle> entries;
    size_t offset = 0;
};
// Worker-local ownership releases cached grants when the session's I/O worker exits.
thread_local std::deque<DirectoryPage> pages;

DocumentResult written(DocumentHandle destination, std::string child, DocumentHandle source,
                       TransferLimits limits, const AccessJob& job)
{
    DocumentResult result;
    if (!destination || !source || source.kind() != DocumentKind::File || !limits.timeoutSeconds) {
        result.error = invalid("Expected a readable file, destination and transfer limits");
        return result;
    }
    std::shared_ptr<Snapshot> stage;
    result.error = prepareSnapshot(source, "source", limits, job, stage);
    if (result.error) return result;
    if (!job.beginWrite()) { result.status = DialogStatus::Cancelled; result.cancelReason = CancelReason::Caller; return result; }
    DocumentHandle actual;
    result.error = Documents::get(destination)->write(child, [&](io::Stream& out) {
        return copyDocument(stage->document, out, limits, job.cancelled);
    }, actual, result.effect);
    if (!result.error) {
        result.status = DialogStatus::Ok;
        result.documents.push_back(std::move(actual));
    }
    return result;
}
}

FileDialogError copyDocument(DocumentHandle source, io::Stream& destination, TransferLimits limits,
                             const std::function<bool()>& cancelled)
{
    if (!source || source.kind() != DocumentKind::File || !limits.timeoutSeconds)
        return invalid("Expected a readable source file and a positive timeout");
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(limits.timeoutSeconds);
    return Documents::get(source)->read([&](io::Stream& input) -> FileDialogError {
        uint64_t total = 0;
        std::array<unsigned char, 64 * 1024> buffer;
        for (;;) {
            if (cancelled()) return {DialogErrorCode::IoError, "Transfer stopped"};
            if (std::chrono::steady_clock::now() >= deadline) return {DialogErrorCode::Timeout, "Transfer timed out"};
            const auto read = input.read(buffer.data(), buffer.size());
            if (read.transferred > buffer.size()) return {DialogErrorCode::InvalidResult, "Invalid stream count"};
            if (cancelled()) return {DialogErrorCode::IoError, "Transfer stopped"};
            if (std::chrono::steady_clock::now() >= deadline || read.status == io::IoStatus::Timeout)
                return {DialogErrorCode::Timeout, "Read timed out"};
            if (read.status != io::IoStatus::Ok && read.status != io::IoStatus::EndOfStream) {
                const auto code = read.error.code == io::ErrorCode::PermissionDenied ?
                    DialogErrorCode::PermissionDenied : DialogErrorCode::IoError;
                return {code, "Read failed", "stream", read.error.nativeCode};
            }
            if (read.transferred > limits.maxBytes - total)
                return {DialogErrorCode::LimitExceeded, "Transfer byte limit exceeded"};
            if (read.transferred) {
                auto write = destination.writeAll(buffer.data(), read.transferred);
                if (std::chrono::steady_clock::now() >= deadline || write.status == io::IoStatus::Timeout)
                    return {DialogErrorCode::Timeout, "Write timed out"};
                if (!write || write.transferred != read.transferred)
                    return {DialogErrorCode::IoError, "Write failed", "stream", write.error.nativeCode};
                total += read.transferred;
            }
            if (read.status == io::IoStatus::EndOfStream) return {};
            if (!read.transferred) return {DialogErrorCode::IoError, "Read made no progress"};
        }
    });
}

}

namespace cc {
using namespace dialog;
DialogSubmission DocumentAccess::withReadStream(DocumentHandle doc, DocumentReader reader, DocumentCallback cb)
{
    return submitAccess([doc, reader = std::move(reader)](const AccessJob&) {
        DocumentResult result;
        if (!doc || doc.kind() != DocumentKind::File || !reader) result.error = invalid("Expected a file and a stream reader");
        else result.error = Documents::get(doc)->read(reader);
        if (!result.error) result.status = DialogStatus::Ok;
        return result;
    }, std::move(cb));
}

DialogSubmission DocumentAccess::importFile(DocumentHandle source, std::string destination, TransferLimits limits, DocumentCallback cb)
{
    return submitAccess([source, destination = std::move(destination), limits](const AccessJob& job) {
        DocumentResult result;
        if (!source || source.kind() != DocumentKind::File) { result.error = invalid("Expected a file to import"); return result; }
        std::filesystem::path path, createdDirectory;
        if (destination.empty()) {
            auto root = cc::detail::ensureAppDirectory(AppDirectory::PersistentData, "imports");
            if (root.status != DirectoryStatus::Ok) { result.error = {DialogErrorCode::IoError, "Cannot create import directory"}; return result; }
            createdDirectory = std::filesystem::u8path(root.path) / uniqueName();
            if (!std::filesystem::create_directory(createdDirectory)) { result.error = {DialogErrorCode::IoError, "Cannot reserve import path"}; return result; }
            auto name = source.displayName();
            path = createdDirectory / std::filesystem::u8path(validName(name) ? name : "document");
        } else {
            if (!DocumentAccess::fromLocalPath(destination)) { result.error = invalid("Expected an absolute import path"); return result; }
            path = std::filesystem::u8path(destination);
        }
        // Import only publishes a new file. Cancellation and publishing are serialized by beginWrite.
        DocumentHandle actual;
        auto name = path.filename().u8string();
        auto dir = localDocument(path.parent_path(), DocumentKind::Directory);
        result.error = Documents::get(dir)->write({name.begin(), name.end()}, [&](io::Stream& out) -> FileDialogError {
            if (auto error = copyDocument(source, out, limits, job.cancelled)) return error;
            if (!job.beginWrite()) return {DialogErrorCode::IoError, "Import cancelled"};
            return {};
        }, actual, result.effect);
        if (result.error) {
            std::error_code ignored;
            if (!createdDirectory.empty()) std::filesystem::remove(createdDirectory, ignored);
        } else {
            result.status = DialogStatus::Ok;
            result.documents.push_back(std::move(actual));
        }
        return result;
    }, std::move(cb), limits.timeoutSeconds);
}

DialogSubmission DocumentAccess::listChildren(DocumentHandle directory, std::string token, uint32_t limit, DocumentCallback cb)
{
    return submitAccess([directory, token = std::move(token), limit](const AccessJob&) {
        DocumentResult result;
        if (!directory || directory.kind() != DocumentKind::Directory || !limit || limit > 1024) {
            result.error = invalid("Expected a directory and page size between 1 and 1024"); return result;
        }
        auto owner = Documents::get(directory);
        DirectoryPage page;
        if (token.empty()) {
            page.owner = owner;
            result.error = owner->children(8192, page.entries);
            if (result.error) return result;
        } else {
            auto it = std::find_if(pages.begin(), pages.end(), [&](const auto& p) { return p.token == token && p.owner.lock() == owner; });
            if (it == pages.end()) { result.error = invalid("Unknown or expired directory page"); return result; }
            page = std::move(*it);
            pages.erase(it);
        }
        auto count = std::min<size_t>(limit, page.entries.size() - page.offset);
        auto first = page.entries.begin() + page.offset;
        result.documents.assign(first, first + count);
        page.offset += count;
        if (page.offset < page.entries.size()) {
            result.nextPage = page.token = uniqueName();
            if (pages.size() == 8) pages.pop_front();
            pages.push_back(std::move(page));
        }
        result.status = DialogStatus::Ok;
        return result;
    }, std::move(cb), 300);
}

DialogSubmission DocumentAccess::exportChild(DocumentHandle dir, std::string name, DocumentHandle source, TransferLimits limits, DocumentCallback cb)
{
    return submitAccess([dir, name = std::move(name), source, limits](const AccessJob& job) {
        if (!dir || dir.kind() != DocumentKind::Directory || !validName(name)) {
            DocumentResult result; result.error = invalid("Expected directory and a single filename"); return result;
        }
        return written(dir, name, source, limits, job);
    }, std::move(cb), limits.timeoutSeconds);
}
DialogSubmission DocumentAccess::writeTarget(SaveTarget target, DocumentHandle source, TransferLimits limits, DocumentCallback cb)
{
    return submitAccess([target, source, limits](const AccessJob& job) {
        return written(Documents::get(target), {}, source, limits, job);
    }, std::move(cb), limits.timeoutSeconds);
}
}
