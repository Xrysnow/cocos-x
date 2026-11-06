// Copyright (c) 2018-2019 HALX99.
// Copyright (c) 2020 C4games Ltd
#include "platform/CCPosixFileStream.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    #include "base/ZipUtils.h"
#endif

#include <sys/stat.h>
#include <assert.h>
#include <limits>
#include <algorithm>

#if defined(_WIN32)
int _ftruncate(int fd, int64_t size)
{
    // _chsize_s zero-fills extensions and reports CRT errno values, unlike
    // SetEndOfFile (whose newly extended bytes are unspecified).
    const auto error = ::_chsize_s(fd, size);
    if (error)
        errno = error;
    return error ? -1 : 0;
}
#endif

NS_CC_BEGIN

struct PXIoF
{
    int (*read)(PXFileHandle& handle, void*, unsigned int);
    int64_t (*seek)(PXFileHandle& handle, int64_t, int);
    int (*close)(PXFileHandle& handle);
    long long (*size)(PXFileHandle& handle);
};

static int pfs_posix_open(std::string_view path, FileStream::Mode mode, PXFileHandle& handle)
{
    FileStream::OpenOptions options;
    if (!FileStream::decodeOpenOptions(mode, options))
        return -1;
    int flags = options.access == FileStream::Access::Read ? O_RDONLY :
                options.access == FileStream::Access::Write ? O_WRONLY : O_RDWR;
    switch (options.creation)
    {
    case FileStream::Creation::OpenExisting: break;
    case FileStream::Creation::CreateNew: flags |= O_CREAT | O_EXCL; break;
    case FileStream::Creation::OpenOrCreate: flags |= O_CREAT; break;
    case FileStream::Creation::CreateAlways: flags |= O_CREAT | O_TRUNC; break;
    case FileStream::Creation::TruncateExisting: flags |= O_TRUNC; break;
    }
    if (options.append)
        flags |= O_APPEND;
    // string_view need not be terminated at its logical end.
    const std::string terminatedPath(path);
#if defined(_WIN32)
    handle._fd = posix_open_cxx(terminatedPath, flags | O_BINARY, S_IWRITE | S_IREAD);
#else
    handle._fd = posix_open_cxx(terminatedPath, flags, S_IRWXU);
    if (handle._fd != -1)
    {
        struct stat info{};
        const int statResult = fstat(handle._fd, &info);
        if (statResult != 0 || S_ISDIR(info.st_mode))
        {
            const int error = statResult == 0 ? EISDIR : errno;
            posix_close(handle._fd);
            handle._fd = -1;
            errno = error;
        }
    }
#endif
    return handle._fd;
}

// posix standard wrappers
static int pfs_posix_read(PXFileHandle& handle, void* buf, unsigned int size)
{
    return static_cast<int>(posix_read(handle._fd, buf, size));
}
static int64_t pfs_posix_seek(PXFileHandle& handle, int64_t offst, int origin)
{
    return posix_lseek64(handle._fd, offst, origin);
}
static int pfs_posix_close(PXFileHandle& handle)
{
    int fd = handle._fd;
    if (fd != -1)
    {
        handle._fd = -1;
        return posix_close(fd);
    }
    return 0;
}
static long long pfs_posix_size(PXFileHandle& handle)
{
#if defined(_WIN32)
    return _filelengthi64(handle._fd);
#else
    struct stat st;

    if (fstat(handle._fd, &st) == 0)
        return st.st_size;

    return -1;
#endif
}

static PXIoF pfs_posix_iof = {pfs_posix_read, pfs_posix_seek, pfs_posix_close, pfs_posix_size};

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// android AssetManager wrappers
static int pfs_asset_read(PXFileHandle& handle, void* buf, unsigned int size)
{
    return AAsset_read(handle._asset, buf, size);
}
static int64_t pfs_asset_seek(PXFileHandle& handle, int64_t offst, int origin)
{
    return AAsset_seek64(handle._asset, offst, origin);
}
static int pfs_asset_close(PXFileHandle& handle)
{
    if (handle._asset != nullptr)
    {
        AAsset_close(handle._asset);
        handle._asset = nullptr;
    }
    return 0;
}
static long long pfs_asset_size(PXFileHandle& handle)
{
    return AAsset_getLength64(handle._asset);
}
static PXIoF pfs_asset_iof = {pfs_asset_read, pfs_asset_seek, pfs_asset_close, pfs_asset_size};

// android obb
static int pfs_obb_read(PXFileHandle& handle, void* buf, unsigned int size)
{
    return FileUtilsAndroid::getObbFile()->zfread(&handle._zfs, buf, size);
}
static int64_t pfs_obb_seek(PXFileHandle& handle, int64_t offset, int origin)
{
    auto obb = FileUtilsAndroid::getObbFile();
    int64_t base = 0;
    switch (origin)
    {
    case SEEK_SET:
        break;
    case SEEK_CUR:
        base = handle._zfs.offset;
        break;
    case SEEK_END:
        base = obb->zfsize(&handle._zfs);
        break;
    default:
        errno = EINVAL;
        return -1;
    }

    // ZipFileStream and zfseek still use signed 32-bit positions. Calculate
    // the absolute target before narrowing, including SEEK_END's file size.
    const int64_t maxOffset = std::numeric_limits<int32_t>::max();
    if (base < 0 || base > maxOffset || offset < -base || offset > maxOffset - base)
    {
        errno = EOVERFLOW;
        return -1;
    }
    return obb->zfseek(&handle._zfs, static_cast<int32_t>(base + offset), SEEK_SET);
}
static int pfs_obb_close(PXFileHandle& handle)
{
    FileUtilsAndroid::getObbFile()->zfclose(&handle._zfs);
    return 0;
}
static long long pfs_obb_size(PXFileHandle& handle)
{
    return FileUtilsAndroid::getObbFile()->zfsize(&handle._zfs);
}
static PXIoF pfs_obb_iof = {pfs_obb_read, pfs_obb_seek, pfs_obb_close, pfs_obb_size};
#endif

PosixFileStream::~PosixFileStream()
{
    internalClose();
}

bool PosixFileStream::open(std::string_view path, FileStream::Mode mode)
{
    internalClose();
    FileStream::OpenOptions options;
    if (path.empty() || path.find('\0') != std::string_view::npos ||
        !FileStream::decodeOpenOptions(mode, options))
    {
        errno = EINVAL;
        return false;
    }

    bool ok = false;
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    ok = pfs_posix_open(path, mode, _handle) != -1;
#else  // Android
    if (path[0] != '/')
    {  // from package, always readonly
        if (options.access != FileStream::Access::Read)
        {
            errno = EACCES;
            return false;
        }
        std::string relativePath;
        size_t position = path.find("assets/");
        if (0 == position)
        {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath = path.substr(sizeof("assets/") - 1);
        }
        else
        {
            relativePath = path;
        }

        auto obb = FileUtilsAndroid::getObbFile();
        ok       = obb != nullptr && obb->zfopen(relativePath, &_handle._zfs);
        if (ok)
        {
            // Reject entries whose cursor would overflow inside zfread/zfseek.
            const auto entrySize = obb->zfsize(&_handle._zfs);
            if (entrySize < 0 || entrySize > std::numeric_limits<int32_t>::max())
            {
                obb->zfclose(&_handle._zfs);
                reset();
                errno = EOVERFLOW;
                return false;
            }
            this->_iof = &pfs_obb_iof;
        }
        else
        {
            AAssetManager* asMgr = FileUtilsAndroid::getAssetManager();
            if (!asMgr)
            {
                errno = ENODEV;
                return false;
            }
            AAsset* asset        = AAssetManager_open(asMgr, relativePath.c_str(), AASSET_MODE_UNKNOWN);
            ok                   = !!asset;
            if (!ok)
                errno = ENOENT;
            if (ok)
            {
                _handle._asset = asset;
                // setup file read/seek/close at here
                this->_iof = &pfs_asset_iof;
            }
        }
    }
    else
    {  // otherwise, as a absolutely path
        ok = pfs_posix_open(path, mode, _handle) != -1;
    }
#endif

    if (ok && !_iof)
        _iof = &pfs_posix_iof;
    if (ok)
        _options = options;

    return ok;
}

int PosixFileStream::internalClose()
{
    if (_iof)
    {
        int ret = _iof->close(_handle);
        reset();
        return ret;
    }
    return 0;
}

int PosixFileStream::close()
{
    return internalClose();
}

int PosixFileStream::seek(int64_t offset, int origin)
{
    if (!_iof)
    {
        errno = EBADF;
        return -1;
    }
    int64_t base = 0;
    if (origin == SEEK_CUR)
        base = tell();
    else if (origin == SEEK_END)
        base = size();
    else if (origin != SEEK_SET)
    {
        errno = EINVAL;
        return -1;
    }
    if (base < 0)
        return -1;
    if (offset < -base || (offset > 0 && offset > std::numeric_limits<int64_t>::max() - base))
    {
        errno = EINVAL;
        return -1;
    }
    const auto result = _iof->seek(_handle, base + offset, SEEK_SET);
    return result < 0 ? -1 : 0;                              // return 0 for success
}

int PosixFileStream::read(void* buf, unsigned int size)
{
    if (!isReadable())
    {
        errno = EBADF;
        return -1;
    }
    if (!size)
        return 0;
    if (!buf)
    {
        errno = EINVAL;
        return -1;
    }
    size = std::min(size, static_cast<unsigned int>(std::numeric_limits<int>::max()));
    int result;
    int attempts = 0;
    do { result = _iof->read(_handle, buf, size); }
    while (result < 0 && errno == EINTR && ++attempts < 8);
    return result;
}

int PosixFileStream::write(const void* buf, unsigned int size)
{
    if (!isWritable())
    {
        errno = EBADF;
        return -1;
    }
    if (!size)
        return 0;
    if (!buf)
    {
        errno = EINVAL;
        return -1;
    }
    const auto position = tell();
    const auto length = this->size();
    if (position < 0 || length < 0)
        return -1;
    if (!_options.append && position > length && resize(position) != 0)
        return -1;
    size = std::min(size, static_cast<unsigned int>(std::numeric_limits<int>::max()));
    int result;
    int attempts = 0;
    do { result = static_cast<int>(posix_write(_handle._fd, buf, size)); }
    while (result < 0 && errno == EINTR && ++attempts < 8);
    return result;
}

int64_t PosixFileStream::tell()
{
    if (_iof)
        return _iof->seek(_handle, 0, SEEK_CUR);
    errno = EBADF;
    return -1;
}

int64_t PosixFileStream::size()
{
    if (_iof)
        return _iof->size(_handle);
    errno = EBADF;
    return -1;
}

bool PosixFileStream::isOpen() const
{
    return _iof != nullptr;
}

bool PosixFileStream::isReadable() const noexcept
{
    return _iof && _options.access != FileStream::Access::Write;
}

bool PosixFileStream::isWritable() const noexcept
{
    return _iof == &pfs_posix_iof && _options.access != FileStream::Access::Read;
}

bool PosixFileStream::canResize() const noexcept { return isWritable(); }
bool PosixFileStream::canSync() const noexcept { return isWritable(); }

int PosixFileStream::resize(int64_t length)
{
    if (!isWritable())
    {
        errno = EBADF;
        return -1;
    }
    if (length < 0)
    {
        errno = EINVAL;
        return -1;
    }
    const auto position = tell();
    if (position < 0 || posix_ftruncate64(_handle._fd, length) != 0)
        return -1;
    return seek(std::min(position, length), SEEK_SET);
}

int PosixFileStream::sync()
{
    if (!canSync())
    {
        errno = EBADF;
        return -1;
    }
#if defined(_WIN32)
    return ::_commit(_handle._fd);
#else
    return ::fsync(_handle._fd);
#endif
}

void PosixFileStream::reset()
{
    memset(&_handle, 0, sizeof(_handle));
    _handle._fd = -1;
    _iof        = nullptr;
    _options = {};
}

NS_CC_END
