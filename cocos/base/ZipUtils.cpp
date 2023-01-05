/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "base/ZipUtils.h"

#ifdef MINIZIP_FROM_SYSTEM
#    include <minizip/unzip.h>
#else  // from our embedded sources
#    include "unzip.h"
#endif
#include "ioapi_mem.h"
#include <ioapi.h>

#include <memory>

#include <zlib.h>
#include <assert.h>
#include <stdlib.h>
#include <set>

#include "base/CCData.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include <map>
#include <mutex>

#include "yasio/cxx17/string_view.hpp"

// minizip 1.2.0 is same with other platforms
#define unzGoToFirstFile64(A, B, C, D) unzGoToFirstFile2(A, B, C, D, NULL, 0, NULL, 0)
#define unzGoToNextFile64(A, B, C, D) unzGoToNextFile2(A, B, C, D, NULL, 0, NULL, 0)

NS_CC_BEGIN

unsigned int ZipUtils::s_uEncryptedPvrKeyParts[4] = {0, 0, 0, 0};
unsigned int ZipUtils::s_uEncryptionKey[1024];
bool ZipUtils::s_bEncryptionKeyIsValid = false;

// --------------------- ZipUtils ---------------------

inline void ZipUtils::decodeEncodedPvr(unsigned int* data, ssize_t len)
{
    const int enclen    = 1024;
    const int securelen = 512;
    const int distance  = 64;

    // check if key was set
    // make sure to call caw_setkey_part() for all 4 key parts
    CCASSERT(s_uEncryptedPvrKeyParts[0] != 0,
             "Cocos2D: CCZ file is encrypted but key part 0 is not set. Did you call "
             "ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[1] != 0,
             "Cocos2D: CCZ file is encrypted but key part 1 is not set. Did you call "
             "ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[2] != 0,
             "Cocos2D: CCZ file is encrypted but key part 2 is not set. Did you call "
             "ZipUtils::setPvrEncryptionKeyPart(...)?");
    CCASSERT(s_uEncryptedPvrKeyParts[3] != 0,
             "Cocos2D: CCZ file is encrypted but key part 3 is not set. Did you call "
             "ZipUtils::setPvrEncryptionKeyPart(...)?");

    // create long key
    if (!s_bEncryptionKeyIsValid)
    {
        unsigned int y, p, e;
        unsigned int rounds = 6;
        unsigned int sum    = 0;
        unsigned int z      = s_uEncryptionKey[enclen - 1];

        do
        {
#define DELTA 0x9e3779b9
#define MX (((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (s_uEncryptedPvrKeyParts[(p & 3) ^ e] ^ z)))

            sum += DELTA;
            e = (sum >> 2) & 3;

            for (p = 0; p < enclen - 1; p++)
            {
                y = s_uEncryptionKey[p + 1];
                z = s_uEncryptionKey[p] += MX;
            }

            y = s_uEncryptionKey[0];
            z = s_uEncryptionKey[enclen - 1] += MX;

        } while (--rounds);

        s_bEncryptionKeyIsValid = true;
    }

    int b = 0;
    int i = 0;

    // encrypt first part completely
    for (; i < len && i < securelen; i++)
    {
        data[i] ^= s_uEncryptionKey[b++];

        if (b >= enclen)
        {
            b = 0;
        }
    }

    // encrypt second section partially
    for (; i < len; i += distance)
    {
        data[i] ^= s_uEncryptionKey[b++];

        if (b >= enclen)
        {
            b = 0;
        }
    }
}

inline unsigned int ZipUtils::checksumPvr(const unsigned int* data, ssize_t len)
{
    unsigned int cs = 0;
    const int cslen = 128;

    len = (len < cslen) ? len : cslen;

    for (int i = 0; i < len; i++)
    {
        cs = cs ^ data[i];
    }

    return cs;
}

// memory in iPhone is precious
// Should buffer factor be 1.5 instead of 2 ?
#define BUFFER_INC_FACTOR (2)

int ZipUtils::inflateMemoryWithHint(unsigned char* in,
                                    ssize_t inLength,
                                    unsigned char** out,
                                    ssize_t* outLength,
                                    ssize_t outLengthHint)
{
    /* ret value */
    int err = Z_OK;

    ssize_t bufferSize = outLengthHint;
    *out               = (unsigned char*)malloc(bufferSize);

    z_stream d_stream; /* decompression stream */
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree  = (free_func)0;
    d_stream.opaque = (voidpf)0;

    d_stream.next_in   = in;
    d_stream.avail_in  = static_cast<unsigned int>(inLength);
    d_stream.next_out  = *out;
    d_stream.avail_out = static_cast<unsigned int>(bufferSize);

    /* window size to hold 256k */
    if ((err = inflateInit2(&d_stream, 15 + 32)) != Z_OK)
        return err;

    for (;;)
    {
        err = inflate(&d_stream, Z_NO_FLUSH);

        if (err == Z_STREAM_END)
        {
            break;
        }

        switch (err)
        {
        case Z_NEED_DICT:
            err = Z_DATA_ERROR;
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            inflateEnd(&d_stream);
            return err;
        }

        // not enough memory ?
        if (err != Z_STREAM_END)
        {
            *out = (unsigned char*)realloc(*out, bufferSize * BUFFER_INC_FACTOR);

            /* not enough memory, ouch */
            if (!*out)
            {
                CCLOG("cocos2d: ZipUtils: realloc failed");
                inflateEnd(&d_stream);
                return Z_MEM_ERROR;
            }

            d_stream.next_out  = *out + bufferSize;
            d_stream.avail_out = static_cast<unsigned int>(bufferSize);
            bufferSize *= BUFFER_INC_FACTOR;
        }
    }

    *outLength = bufferSize - d_stream.avail_out;
    err        = inflateEnd(&d_stream);
    return err;
}

ssize_t ZipUtils::inflateMemoryWithHint(unsigned char* in, ssize_t inLength, unsigned char** out, ssize_t outLengthHint)
{
    ssize_t outLength = 0;
    int err           = inflateMemoryWithHint(in, inLength, out, &outLength, outLengthHint);

    if (err != Z_OK || *out == nullptr)
    {
        if (err == Z_MEM_ERROR)
        {
            CCLOG("cocos2d: ZipUtils: Out of memory while decompressing map data!");
        }
        else if (err == Z_VERSION_ERROR)
        {
            CCLOG("cocos2d: ZipUtils: Incompatible zlib version!");
        }
        else if (err == Z_DATA_ERROR)
        {
            CCLOG("cocos2d: ZipUtils: Incorrect zlib compressed data!");
        }
        else
        {
            CCLOG("cocos2d: ZipUtils: Unknown error while decompressing map data!");
        }

        if (*out)
        {
            free(*out);
            *out = nullptr;
        }
        outLength = 0;
    }

    return outLength;
}

ssize_t ZipUtils::inflateMemory(unsigned char* in, ssize_t inLength, unsigned char** out)
{
    // 256k for hint
    return inflateMemoryWithHint(in, inLength, out, 256 * 1024);
}

int ZipUtils::inflateGZipFile(const char* path, unsigned char** out)
{
    int len;
    unsigned int offset = 0;

    CCASSERT(out, "out can't be nullptr.");
    CCASSERT(&*out, "&*out can't be nullptr.");

    gzFile inFile = gzopen(path, "rb");
    if (inFile == nullptr)
    {
        CCLOG("cocos2d: ZipUtils: error open gzip file: %s", path);
        return -1;
    }

    /* 512k initial decompress buffer */
    unsigned int bufferSize      = 512 * 1024;
    unsigned int totalBufferSize = bufferSize;

    *out = (unsigned char*)malloc(bufferSize);
    if (*out == NULL)
    {
        CCLOG("cocos2d: ZipUtils: out of memory");
        return -1;
    }

    for (;;)
    {
        len = gzread(inFile, *out + offset, bufferSize);
        if (len < 0)
        {
            CCLOG("cocos2d: ZipUtils: error in gzread");
            free(*out);
            *out = nullptr;
            return -1;
        }
        if (len == 0)
        {
            break;
        }

        offset += len;

        // finish reading the file
        if ((unsigned int)len < bufferSize)
        {
            break;
        }

        bufferSize *= BUFFER_INC_FACTOR;
        totalBufferSize += bufferSize;
        unsigned char* tmp = (unsigned char*)realloc(*out, totalBufferSize);

        if (!tmp)
        {
            CCLOG("cocos2d: ZipUtils: out of memory");
            free(*out);
            *out = nullptr;
            return -1;
        }

        *out = tmp;
    }

    if (gzclose(inFile) != Z_OK)
    {
        CCLOG("cocos2d: ZipUtils: gzclose failed");
    }

    return offset;
}

bool ZipUtils::isCCZFile(const char* path)
{
    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);

    if (compressedData.isNull())
    {
        CCLOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }

    return isCCZBuffer(compressedData.getBytes(), compressedData.getSize());
}

bool ZipUtils::isCCZBuffer(const unsigned char* buffer, ssize_t len)
{
    if (static_cast<size_t>(len) < sizeof(struct CCZHeader))
    {
        return false;
    }

    struct CCZHeader* header = (struct CCZHeader*)buffer;
    return header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' &&
           (header->sig[3] == '!' || header->sig[3] == 'p');
}

bool ZipUtils::isGZipFile(const char* path)
{
    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);

    if (compressedData.isNull())
    {
        CCLOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }

    return isGZipBuffer(compressedData.getBytes(), compressedData.getSize());
}

bool ZipUtils::isGZipBuffer(const unsigned char* buffer, ssize_t len)
{
    if (len < 2)
    {
        return false;
    }

    return buffer[0] == 0x1F && buffer[1] == 0x8B;
}

int ZipUtils::inflateCCZBuffer(const unsigned char* buffer, ssize_t bufferLen, unsigned char** out)
{
    struct CCZHeader* header = (struct CCZHeader*)buffer;

    // verify header
    if (header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == '!')
    {
        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST(header->version);
        if (version > 2)
        {
            CCLOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if (CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB)
        {
            CCLOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }
    }
    else if (header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == 'p')
    {
        // encrypted ccz file
        header = (struct CCZHeader*)buffer;

        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST(header->version);
        if (version > 0)
        {
            CCLOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if (CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB)
        {
            CCLOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }

        // decrypt
        unsigned int* ints = (unsigned int*)(buffer + 12);
        ssize_t enclen     = (bufferLen - 12) / 4;

        decodeEncodedPvr(ints, enclen);

#if _CC_DEBUG > 0
        // verify checksum in debug mode
        unsigned int calculated = checksumPvr(ints, enclen);
        unsigned int required   = CC_SWAP_INT32_BIG_TO_HOST(header->reserved);

        if (calculated != required)
        {
            CCLOG("cocos2d: Can't decrypt image file. Is the decryption key valid?");
            return -1;
        }
#endif
    }
    else
    {
        CCLOG("cocos2d: Invalid CCZ file");
        return -1;
    }

    unsigned int len = CC_SWAP_INT32_BIG_TO_HOST(header->len);

    *out = (unsigned char*)malloc(len);
    if (!*out)
    {
        CCLOG("cocos2d: CCZ: Failed to allocate memory for texture");
        return -1;
    }

    unsigned long destlen = len;
    size_t source         = (size_t)buffer + sizeof(*header);
    int ret               = uncompress(*out, &destlen, (Bytef*)source, bufferLen - sizeof(*header));

    if (ret != Z_OK)
    {
        CCLOG("cocos2d: CCZ: Failed to uncompress data");
        free(*out);
        *out = nullptr;
        return -1;
    }

    return len;
}

int ZipUtils::inflateCCZFile(const char* path, unsigned char** out)
{
    CCASSERT(out, "Invalid pointer for buffer!");

    // load file into memory
    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);

    if (compressedData.isNull())
    {
        CCLOG("cocos2d: Error loading CCZ compressed file");
        return -1;
    }

    return inflateCCZBuffer(compressedData.getBytes(), compressedData.getSize(), out);
}

void ZipUtils::setPvrEncryptionKeyPart(int index, unsigned int value)
{
    CCASSERT(index >= 0, "Cocos2d: key part index cannot be less than 0");
    CCASSERT(index <= 3, "Cocos2d: key part index cannot be greater than 3");

    if (s_uEncryptedPvrKeyParts[index] != value)
    {
        s_uEncryptedPvrKeyParts[index] = value;
        s_bEncryptionKeyIsValid        = false;
    }
}

void ZipUtils::setPvrEncryptionKey(unsigned int keyPart1,
                                   unsigned int keyPart2,
                                   unsigned int keyPart3,
                                   unsigned int keyPart4)
{
    setPvrEncryptionKeyPart(0, keyPart1);
    setPvrEncryptionKeyPart(1, keyPart2);
    setPvrEncryptionKeyPart(2, keyPart3);
    setPvrEncryptionKeyPart(3, keyPart4);
}

// --------------------- ZipFile ---------------------
// from unzip.cpp
#define UNZ_MAXFILENAMEINZIP 256

static const std::string emptyFilename("");

struct ZipEntryInfo
{
    unz_file_pos pos;
    uLong uncompressed_size;
};

struct ZipFilePrivate
{
    ZipFilePrivate()
    {
        functionOverrides.zopen_file     = ZipFile_open_file_func;
        functionOverrides.zopendisk_file = ZipFile_opendisk_file_func;
        functionOverrides.zread_file     = ZipFile_read_file_func;
        functionOverrides.zwrite_file    = ZipFile_write_file_func;
        functionOverrides.ztell_file     = ZipFile_tell_file_func;
        functionOverrides.zseek_file     = ZipFile_seek_file_func;
        functionOverrides.zclose_file    = ZipFile_close_file_func;
        functionOverrides.zerror_file    = ZipFile_error_file_func;
        functionOverrides.opaque         = this;
    }

    // unzip overrides to support FileStream
    static long ZipFile_tell_file_func(voidpf opaque, voidpf stream)
    {
        if (stream == nullptr)
            return -1;

        auto* fs = (FileStream*)stream;

        return fs->tell();
    }

    static long ZipFile_seek_file_func(voidpf opaque, voidpf stream, uint32_t offset, int origin)
    {
        if (stream == nullptr)
            return -1;

        auto* fs = (FileStream*)stream;

        return fs->seek((int32_t)offset, origin);  // must return 0 for success or -1 for error
    }

    static voidpf ZipFile_open_file_func(voidpf opaque, const char* filename, int mode)
    {
        FileStream::Mode fsMode;
        if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER) == ZLIB_FILEFUNC_MODE_READ)
            fsMode = FileStream::Mode::READ;
        else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
            fsMode = FileStream::Mode::APPEND;
        else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
            fsMode = FileStream::Mode::WRITE;
        else
            return nullptr;

        return FileUtils::getInstance()->openFileStream(filename, fsMode).release();
    }

    static voidpf ZipFile_opendisk_file_func(voidpf opaque, voidpf stream, uint32_t number_disk, int mode)
    {
        if (stream == nullptr)
            return nullptr;

        auto* zipFileInfo        = (ZipFilePrivate*)opaque;
        std::string diskFilename = zipFileInfo->zipFileName;

        const auto pos = diskFilename.rfind('.', std::string::npos);

        if (pos != std::string::npos && pos != 0)
        {
            const size_t bufferSize = 5;
            char extensionBuffer[bufferSize];
            snprintf(&extensionBuffer[0], bufferSize, ".z%02u", number_disk + 1);
            diskFilename.replace(pos, std::min((size_t)4, zipFileInfo->zipFileName.size() - pos), extensionBuffer);
            return ZipFile_open_file_func(opaque, diskFilename.c_str(), mode);
        }

        return nullptr;
    }

    static uint32_t ZipFile_read_file_func(voidpf opaque, voidpf stream, void* buf, uint32_t size)
    {
        if (stream == nullptr)
            return (uint32_t)-1;

        auto* fs = (FileStream*)stream;
        return fs->read(buf, size);
    }

    static uint32_t ZipFile_write_file_func(voidpf opaque, voidpf stream, const void* buf, uint32_t size)
    {
        if (stream == nullptr)
            return (uint32_t)-1;

        auto* fs = (FileStream*)stream;
        return fs->write(buf, size);
    }

    static int ZipFile_close_file_func(voidpf opaque, voidpf stream)
    {
        if (stream == nullptr)
            return -1;

        auto* fs          = (FileStream*)stream;
        const auto result = fs->close();  // 0 for success, -1 for error
        delete fs;
        return result;
    }

    // THis isn't supported by FileStream, so just check if the stream is null and open
    static int ZipFile_error_file_func(voidpf opaque, voidpf stream)
    {
        if (stream == nullptr)
        {
            return -1;
        }

        auto* fs = (FileStream*)stream;

        if (fs->isOpen())
        {
            return 0;
        }

        return -1;
    }
    // End of Overrides

    std::string zipFileName;
    unzFile zipFile;
    std::mutex zipFileMtx;
    std::unique_ptr<ourmemory_s> memfs;

    // std::unordered_map is faster if available on the platform
    typedef hlookup::string_map<struct ZipEntryInfo> FileListContainer;
    FileListContainer fileList;

    zlib_filefunc_def functionOverrides{};
};

ZipFile* ZipFile::createWithBuffer(const void* buffer, unsigned int size)
{
    ZipFile* zip = new ZipFile();
    if (zip->initWithBuffer(buffer, size))
    {
        return zip;
    }
    else
    {
        delete zip;
        return nullptr;
    }
}

ZipFile::ZipFile() : _data(new ZipFilePrivate())
{
    _data->zipFile = nullptr;
}

ZipFile::ZipFile(std::string_view zipFile, std::string_view filter) : _data(new ZipFilePrivate())
{
    _data->zipFileName = zipFile;
    _data->zipFile     = unzOpen2(zipFile.data(), &_data->functionOverrides);
    setFilter(filter);
}

ZipFile::~ZipFile()
{
    if (_data && _data->zipFile)
    {
        unzClose(_data->zipFile);
    }

    CC_SAFE_DELETE(_data);
}

bool ZipFile::setFilter(std::string_view filter)
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(!_data);
        CC_BREAK_IF(!_data->zipFile);

        // clear existing file list
        _data->fileList.clear();

        // UNZ_MAXFILENAMEINZIP + 1 - it is done so in unzLocateFile
        char szCurrentFileName[UNZ_MAXFILENAMEINZIP + 1];
        unz_file_info64 fileInfo;

        // go through all files and store position information about the required files
        int err = unzGoToFirstFile64(_data->zipFile, &fileInfo, szCurrentFileName, sizeof(szCurrentFileName) - 1);
        while (err == UNZ_OK)
        {
            unz_file_pos posInfo;
            int posErr = unzGetFilePos(_data->zipFile, &posInfo);
            if (posErr == UNZ_OK)
            {
                std::string currentFileName = szCurrentFileName;
                // cache info about filtered files only (like 'assets/')
                if (filter.empty() || currentFileName.substr(0, filter.length()) == filter)
                {
                    ZipEntryInfo entry;
                    entry.pos                        = posInfo;
                    entry.uncompressed_size          = (uLong)fileInfo.uncompressed_size;
                    _data->fileList[currentFileName] = entry;
                }
            }
            // next file - also get the information about it
            err = unzGoToNextFile64(_data->zipFile, &fileInfo, szCurrentFileName, sizeof(szCurrentFileName) - 1);
        }
        ret = true;

    } while (false);

    return ret;
}

bool ZipFile::fileExists(std::string_view fileName) const
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(!_data);

        ret = _data->fileList.find(fileName) != _data->fileList.end();
    } while (false);

    return ret;
}

std::vector<std::string> ZipFile::listFiles(std::string_view pathname) const
{

    // filter files which `filename.startsWith(pathname)`
    // then make each path unique

    std::set<std::string_view> fileSet;
    ZipFilePrivate::FileListContainer::const_iterator it  = _data->fileList.begin();
    ZipFilePrivate::FileListContainer::const_iterator end = _data->fileList.end();
    // ensure pathname ends with `/` as a directory
    std::string ensureDir;
    std::string_view dirname = pathname[pathname.length() - 1] == '/' ? pathname : (ensureDir.append(pathname) += '/');
    for (auto&& item : _data->fileList)
    {
        std::string_view filename = item.first;
        if (cxx20::starts_with(filename, cxx17::string_view{dirname}))
        {
            std::string_view suffix{filename.substr(dirname.length())};
            auto pos = suffix.find('/');
            if (pos == std::string::npos)
            {
                fileSet.insert(suffix);
            }
            else
            {
                // fileSet.insert(parts[0] + "/");
                fileSet.insert(suffix.substr(0, pos + 1));
            }
        }
    }

    return std::vector<std::string>{fileSet.begin(), fileSet.end()};
}

unsigned char* ZipFile::getFileData(std::string_view fileName, ssize_t* size)
{
    unsigned char* buffer = nullptr;
    if (size)
        *size = 0;

    do
    {
        CC_BREAK_IF(!_data->zipFile);
        CC_BREAK_IF(fileName.empty());

        auto it = _data->fileList.find(fileName);
        CC_BREAK_IF(it == _data->fileList.end());

        ZipEntryInfo& fileInfo = it->second;

        std::unique_lock<std::mutex> lck(_data->zipFileMtx);

        int nRet = unzGoToFilePos(_data->zipFile, &fileInfo.pos);
        CC_BREAK_IF(UNZ_OK != nRet);

        nRet = unzOpenCurrentFile(_data->zipFile);
        CC_BREAK_IF(UNZ_OK != nRet);

        buffer = (unsigned char*)malloc(fileInfo.uncompressed_size);
        int CC_UNUSED nSize =
            unzReadCurrentFile(_data->zipFile, buffer, static_cast<unsigned int>(fileInfo.uncompressed_size));
        CCASSERT(nSize == 0 || nSize == (int)fileInfo.uncompressed_size, "the file size is wrong");

        if (size)
        {
            *size = fileInfo.uncompressed_size;
        }
        unzCloseCurrentFile(_data->zipFile);
    } while (0);

    return buffer;
}

bool ZipFile::getFileData(std::string_view fileName, ResizableBuffer* buffer)
{
    bool res = false;
    do
    {
        CC_BREAK_IF(!_data->zipFile);
        CC_BREAK_IF(fileName.empty());

        ZipFilePrivate::FileListContainer::iterator it = _data->fileList.find(fileName);
        CC_BREAK_IF(it == _data->fileList.end());

        ZipEntryInfo& fileInfo = it->second;

        std::unique_lock<std::mutex> lck(_data->zipFileMtx);

        int nRet = unzGoToFilePos(_data->zipFile, &fileInfo.pos);
        CC_BREAK_IF(UNZ_OK != nRet);

        nRet = unzOpenCurrentFile(_data->zipFile);
        CC_BREAK_IF(UNZ_OK != nRet);

        buffer->resize(fileInfo.uncompressed_size);
        int CC_UNUSED nSize =
            unzReadCurrentFile(_data->zipFile, buffer->buffer(), static_cast<unsigned int>(fileInfo.uncompressed_size));
        CCASSERT(nSize == 0 || nSize == (int)fileInfo.uncompressed_size, "the file size is wrong");
        unzCloseCurrentFile(_data->zipFile);
        res = true;
    } while (0);

    return res;
}

std::string ZipFile::getFirstFilename()
{
    if (unzGoToFirstFile(_data->zipFile) != UNZ_OK)
        return emptyFilename;
    std::string path;
    unz_file_info_s info;
    getCurrentFileInfo(&path, &info);
    return path;
}

std::string ZipFile::getNextFilename()
{
    if (unzGoToNextFile(_data->zipFile) != UNZ_OK)
        return emptyFilename;
    std::string path;
    unz_file_info_s info;
    getCurrentFileInfo(&path, &info);
    return path;
}

int ZipFile::getCurrentFileInfo(std::string* filename, unz_file_info_s* info)
{
    char path[FILENAME_MAX + 1];
    int ret = unzGetCurrentFileInfo(_data->zipFile, info, path, sizeof(path), nullptr, 0, nullptr, 0);
    if (ret != UNZ_OK)
    {
        *filename = emptyFilename;
    }
    else
    {
        filename->assign(path);
    }
    return ret;
}

bool ZipFile::initWithBuffer(const void* buffer, unsigned int size)
{
    if (!buffer || size == 0)
        return false;

    zlib_filefunc_def memory_file = {0};

    std::unique_ptr<ourmemory_t> memfs(
        new ourmemory_t{(char*)const_cast<void*>(buffer), static_cast<uint32_t>(size), 0, 0, 0});
    fill_memory_filefunc(&memory_file, memfs.get());

    _data->zipFile = unzOpen2(nullptr, &memory_file);
    if (!_data->zipFile)
        return false;
    _data->memfs = std::move(memfs);

    setFilter(emptyFilename);
    return true;
}

bool ZipFile::zfopen(std::string_view fileName, ZipFileStream* zfs)
{
    if (!zfs)
        return false;
    auto it = _data->fileList.find(fileName);
    if (it != _data->fileList.end())
    {
        zfs->entry  = &it->second;
        zfs->offset = 0;
        return true;
    }
    zfs->entry  = nullptr;
    zfs->offset = -1;
    return false;
}

int ZipFile::zfread(ZipFileStream* zfs, void* buf, unsigned int size)
{
    int n = 0;
    do
    {
        CC_BREAK_IF(zfs == nullptr || zfs->offset >= zfs->entry->uncompressed_size);

        std::unique_lock<std::mutex> lck(_data->zipFileMtx);

        int nRet = unzGoToFilePos(_data->zipFile, &zfs->entry->pos);
        CC_BREAK_IF(UNZ_OK != nRet);

        nRet = unzOpenCurrentFile(_data->zipFile);
        unzSeek64(_data->zipFile, zfs->offset, SEEK_SET);
        n = unzReadCurrentFile(_data->zipFile, buf, size);
        if (n > 0)
            zfs->offset += n;

        unzCloseCurrentFile(_data->zipFile);

    } while (false);

    return n;
}

int32_t ZipFile::zfseek(ZipFileStream* zfs, int32_t offset, int origin)
{
    int32_t result = -1;
    if (zfs != nullptr)
    {
        switch (origin)
        {
        case SEEK_SET:
            result = offset;
            break;
        case SEEK_CUR:
            result = zfs->offset + offset;
            break;
        case SEEK_END:
            result = (int32_t)zfs->entry->uncompressed_size + offset;
            break;
        default:;
        }

        if (result >= 0)
        {
            zfs->offset = result;
        }
        else
            result = -1;
    }

    return result;
}

void ZipFile::zfclose(ZipFileStream* zfs)
{
    if (zfs != nullptr && zfs->entry != nullptr)
    {
        zfs->entry  = nullptr;
        zfs->offset = -1;
    }
}

long long ZipFile::zfsize(ZipFileStream* zfs)
{
    if (zfs != nullptr && zfs->entry != nullptr)
    {
        return zfs->entry->uncompressed_size;
    }

    return -1;
}

unsigned char* ZipFile::getFileDataFromZip(std::string_view zipFilePath, std::string_view filename, ssize_t* size)
{
    unsigned char* buffer = nullptr;
    unzFile file          = nullptr;
    *size                 = 0;

    do
    {
        CC_BREAK_IF(zipFilePath.empty());

        file = unzOpen(zipFilePath.data());
        CC_BREAK_IF(!file);

        // minizip 1.2.0 is same with other platforms
        int ret = unzLocateFile(file, filename.data(), nullptr);

        CC_BREAK_IF(UNZ_OK != ret);

        char filePathA[260];
        unz_file_info_s fileInfo;
        ret = unzGetCurrentFileInfo(file, &fileInfo, filePathA, sizeof(filePathA), nullptr, 0, nullptr, 0);
        CC_BREAK_IF(UNZ_OK != ret);

        ret = unzOpenCurrentFile(file);
        CC_BREAK_IF(UNZ_OK != ret);

        buffer                   = (unsigned char*)malloc(fileInfo.uncompressed_size);
        int CC_UNUSED readedSize = unzReadCurrentFile(file, buffer, static_cast<unsigned>(fileInfo.uncompressed_size));
        CCASSERT(readedSize == 0 || readedSize == (int)fileInfo.uncompressed_size, "the file size is wrong");

        *size = fileInfo.uncompressed_size;
        unzCloseCurrentFile(file);
    } while (0);

    if (file)
    {
        unzClose(file);
    }

    return buffer;
}

NS_CC_END
