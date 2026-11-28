#include "Import.h"
#include "platform/FileUtils.h"
#include "platform/FileStream.h"
#include <cctype>
#include <list>
#include <mutex>
namespace cc::haptics
{
using namespace detail;
namespace
{
// FileUtils resolves and reads on each load so archive changes and same-name
// hot reloads are visible. Only already compiled author documents are retained.
struct CachedFile
{
    std::string path;
    ImportResult result;
    size_t bytes;
};

size_t storageBytes(const ImportResult& result)
{
    const auto& clip = ClipAccess::get(result.clip);
    size_t bytes = sizeof(clip) + clip.sourceJson.capacity() + 1 +
                   clip.layers.capacity() * sizeof(Layer) + clip.pulses.capacity() * sizeof(Pulse) +
                   clip.boundaries.capacity() * sizeof(Time);
    for (const auto& layer : clip.layers)
        bytes += (layer.envelope.capacity() + layer.textureOffset.capacity()) * sizeof(Point);
    for (const auto& controls : clip.controls)
    {
        bytes += controls.capacity() * sizeof(Command);
        for (const auto& command : controls) bytes += command.points.capacity() * sizeof(Point);
    }
    bytes += result.diagnostics.capacity() * sizeof(Diagnostic);
    for (const auto& d : result.diagnostics)
        bytes += d.path.capacity() + d.code.capacity() + d.message.capacity() + 3;
    return bytes;
}

class FileCache
{
    std::mutex mutex;
    std::list<CachedFile> files;
    size_t bytes{};
public:
    std::optional<ImportResult> find(std::string_view path, std::string_view source, const ImportOptions& options)
    {
        std::lock_guard lock(mutex);
        for (auto it = files.begin(); it != files.end(); ++it)
        {
            const auto& clip = it->result.clip;
            if (it->path == path && clip.importPolicy() == options.policy &&
                (options.format == AssetFormat::Auto || clip.format() == options.format) &&
                ClipAccess::get(clip).sourceJson == source)
            {
                files.splice(files.begin(), files, it);
                return it->result;
            }
        }
        return {};
    }

    void retain(std::string_view path, const ImportResult& result)
    {
        constexpr size_t limit = 4 * ByteLimit;
        const auto size = sizeof(CachedFile) + path.size() + 1 + storageBytes(result);
        if (size > limit) return;
        std::lock_guard lock(mutex);
        for (auto it = files.begin(); it != files.end(); ++it)
            if (it->path == path && it->result.clip.importPolicy() == result.clip.importPolicy())
            {
                bytes -= it->bytes;
                files.erase(it);
                break;
            }
        files.push_front({std::string(path), result, size});
        bytes += size;
        while (files.size() > 32 || bytes > limit)
        {
            bytes -= files.back().bytes;
            files.pop_back();
        }
    }
};
}
Result<ImportResult> HapticClip::load(std::string_view path, const ImportOptions& options)
{
    if (path.empty() || path.find('\0') != path.npos)
        return failure(Error::InvalidArgument, "Invalid path");
    auto stream = FileUtils::getInstance()->openFileStream(path, FileStream::Mode::READ);
    if (!stream)
        return failure(Error::IoError, "Unable to open resource");
    std::string bytes;
    std::array<char, 8192> buffer;
    for (;;)
    {
        auto requested = static_cast<unsigned>(std::min(buffer.size(), ByteLimit + 1 - bytes.size()));
        auto count     = stream->read(buffer.data(), requested);
        if (count < 0 || static_cast<unsigned>(count) > requested)
            return failure(Error::IoError, "Unable to read resource");
        if (!count)
            break;
        if (static_cast<size_t>(count) > ByteLimit - bytes.size())
            return failure(Error::InvalidAsset, "Resource exceeds 1 MiB");
        bytes.append(buffer.data(), count);
    }
    auto dot = path.rfind('.');
    std::string suffix(dot == path.npos ? std::string_view{} : path.substr(dot));
    for (char& c : suffix)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    static FileCache cache;
    if (auto hit = cache.find(path, bytes, options)) return {std::move(hit), {}};
    auto result = compile(
        bytes,
        options,
        suffix == ".ahap"     ? AssetFormat::AppleAhap
        : suffix == ".haptic" ? AssetFormat::MetaHaptic
                              : AssetFormat::Auto,
        suffix == ".he", &bytes);
    if (result.value && result.value->clip.format() != AssetFormat::MetaHaptic)
        cache.retain(path, *result.value);
    return result;
}
}  // namespace cc::haptics
