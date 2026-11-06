// Copyright (c) 2018-2019 HALX99
// Copyright (c) 2020 C4games Ltd
#pragma once

#include <string>
#include <string_view>
#include <cstdint>

#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class CC_DLL FileStream
{
public:
    virtual ~FileStream() = default;

    enum class Mode
    {
        READ,
        WRITE,
        APPEND,
        OVERLAPPED,
    };

    enum class Access { Read, Write, ReadWrite };
    enum class Creation { OpenExisting, CreateNew, OpenOrCreate, CreateAlways, TruncateExisting };
    struct OpenOptions
    {
        Access access = Access::Read;
        Creation creation = Creation::OpenExisting;
        bool append = false;
    };

    // Keep the original virtual opening hook, including FileUtils delegates.
    // Extended values are opaque modes produced here; old values remain 0..3.
    static bool encodeOpenOptions(const OpenOptions& options, Mode& mode) noexcept;
    static bool decodeOpenOptions(Mode mode, OpenOptions& options) noexcept;

    /**
     *  Open a file
     *  @param path file to open
     *  @param mode File open mode, being READ | WRITE | APPEND
     *  @return true if successful, false if not
     */
    virtual bool open(std::string_view path, FileStream::Mode mode) = 0;

    /**
     *  Close a file stream
     *  @return 0 if successful, -1 if not
     */
    virtual int close() = 0;

    /**
     *  Seek to position in a file stream
     *  @param offset how many bytes to move within the stream
     *  @param origin SEEK_SET | SEEK_CUR | SEEK_END
     *  @return 0 if successful, -1 if not
     */
    virtual int seek(int64_t offset, int origin) = 0;

    /**
     *  Read data from file stream
     *  @param buf pointer to data
     *  @param size the amount of data to read in bytes
     *  @return amount of data read successfully, -1 if error
     */
    virtual int read(void* buf, unsigned int size) = 0;

    /**
     *  Write data to file stream
     *  @param buf pointer to data
     *  @param size the amount of data to write in bytes
     *  @return amount of data written successfully, -1 if error
     */
    virtual int write(const void* buf, unsigned int size) = 0;

    /**
     *  Get the current position in the file stream
     *  @return current position, -1 if error
     */
    virtual int64_t tell() = 0;

    /**
     *  Get the size of the file stream
     *  @return stream size, -1 if error (Mode::WRITE and Mode::APPEND may return -1)
     */
    virtual int64_t size() = 0;

    /**
     *  Get status of file stream
     *  @return true if open, false if closed
     */
    virtual bool isOpen() const = 0;

    // Optional capabilities for richer stream consumers. Legacy backends remain
    // source-compatible and explicitly decline unsupported mutations.
    virtual bool isReadable() const noexcept { return true; }
    virtual bool isWritable() const noexcept { return false; }
    virtual bool canResize() const noexcept { return false; }
    virtual bool canSync() const noexcept { return false; }
    virtual int resize(int64_t length);
    virtual int sync();

    virtual operator bool() const { return isOpen(); }

protected:
    FileStream(){};
};

NS_CC_END
