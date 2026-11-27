#include "Import.h"
#include "platform/FileUtils.h"
#include "platform/FileStream.h"
#include <cctype>
namespace cc::haptics
{
using namespace detail;
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
    return compile(
        bytes,
        options,
        suffix == ".ahap"     ? AssetFormat::AppleAhap
        : suffix == ".haptic" ? AssetFormat::MetaHaptic
                              : AssetFormat::Auto);
}
}  // namespace cc::haptics
