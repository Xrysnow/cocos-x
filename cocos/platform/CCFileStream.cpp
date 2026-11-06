// Copyright (c) 2018-2019 HALX99.
// Copyright (c) 2020 C4games Ltd
#include "platform/CCFileStream.h"
#include <cerrno>

NS_CC_BEGIN

bool FileStream::encodeOpenOptions(const OpenOptions& options, Mode& mode) noexcept
{
    const int access = static_cast<int>(options.access);
    const int creation = static_cast<int>(options.creation);
    if (access < 0 || access > 2 || creation < 0 || creation > 4 ||
        (options.access == Access::Read && (options.creation != Creation::OpenExisting || options.append)))
    {
        errno = EINVAL;
        return false;
    }
    if (options.access == Access::Read)
        mode = Mode::READ;
    else if (options.access == Access::ReadWrite && options.creation == Creation::CreateAlways && !options.append)
        mode = Mode::WRITE;
    else if (options.access == Access::ReadWrite && options.creation == Creation::OpenOrCreate)
        mode = options.append ? Mode::APPEND : Mode::OVERLAPPED;
    else
        mode = static_cast<Mode>(0x100 | access | (creation << 2) | (options.append ? 0x20 : 0));
    return true;
}

bool FileStream::decodeOpenOptions(Mode mode, OpenOptions& options) noexcept
{
    switch (mode)
    {
    case Mode::READ: options = {}; return true;
    case Mode::WRITE: options = {Access::ReadWrite, Creation::CreateAlways, false}; return true;
    case Mode::APPEND: options = {Access::ReadWrite, Creation::OpenOrCreate, true}; return true;
    case Mode::OVERLAPPED: options = {Access::ReadWrite, Creation::OpenOrCreate, false}; return true;
    default: break;
    }
    const auto encoded = static_cast<unsigned int>(mode);
    if ((encoded & ~0x3fu) != 0x100u)
    {
        errno = EINVAL;
        return false;
    }
    options = {static_cast<Access>(encoded & 3), static_cast<Creation>((encoded >> 2) & 7),
               (encoded & 0x20) != 0};
    Mode checked;
    return encodeOpenOptions(options, checked);
}

int FileStream::resize(int64_t)
{
    errno = ENOSYS;
    return -1;
}

int FileStream::sync()
{
    errno = ENOSYS;
    return -1;
}

NS_CC_END
