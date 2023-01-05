/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2020 C4games Ltd.
 Copyright (c) 2021-2022 Bytedance Inc.

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

#pragma once

#include "CCPlatformMacros.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

namespace backend
{
namespace PixelFormatUtils
{
typedef cocos2d::backend::PixelFormat PixelFormat;

struct PixelFormatDescriptor
{
    uint8_t bpp;  // bitsPerPixel: !!!regard bpp=0 as invalid pixel format
    uint8_t blockWidth;
    uint8_t blockHeight;
    uint8_t blockSize;
    uint8_t minBlockX;
    uint8_t minBlockY;
    bool alpha;  // with alpha channel?
    const char* name;
};

const PixelFormatDescriptor& getFormatDescriptor(PixelFormat format);
uint32_t computeRowPitch(PixelFormat format, uint32_t width);
inline uint8_t getBitsPerPixel(PixelFormat format)
{
    return getFormatDescriptor(format).bpp;
}
inline bool isCompressed(PixelFormat format)
{
    return format < PixelFormat::RGBA8;
}

/**convert functions*/

/**
Convert the format to the format param you specified, if the format is PixelFormat::NONE, it will detect it
automatically and convert to the closest format for you. It will return the converted format to you. if the outData !=
data, you must delete it manually.
*/
PixelFormat convertDataToFormat(const unsigned char* data,
                                size_t dataLen,
                                PixelFormat originFormat,
                                PixelFormat format,
                                unsigned char** outData,
                                size_t* outDataLen);

PixelFormat convertL8ToFormat(const unsigned char* data,
                              size_t dataLen,
                              PixelFormat format,
                              unsigned char** outData,
                              size_t* outDataLen);
PixelFormat convertLA8ToFormat(const unsigned char* data,
                               size_t dataLen,
                               PixelFormat format,
                               unsigned char** outData,
                               size_t* outDataLen);
PixelFormat convertRGB8ToFormat(const unsigned char* data,
                                size_t dataLen,
                                PixelFormat format,
                                unsigned char** outData,
                                size_t* outDataLen);
PixelFormat convertRGBA8ToFormat(const unsigned char* data,
                                 size_t dataLen,
                                 PixelFormat format,
                                 unsigned char** outData,
                                 size_t* outDataLen);
PixelFormat convertRGB5A1ToFormat(const unsigned char* data,
                                  size_t dataLen,
                                  PixelFormat format,
                                  unsigned char** outData,
                                  size_t* outDataLen);
PixelFormat convertRGB565ToFormat(const unsigned char* data,
                                  size_t dataLen,
                                  PixelFormat format,
                                  unsigned char** outData,
                                  size_t* outDataLen);
PixelFormat convertA8ToFormat(const unsigned char* data,
                              size_t dataLen,
                              PixelFormat format,
                              unsigned char** outData,
                              size_t* outDataLen);
PixelFormat convertRGBA4ToFormat(const unsigned char* data,
                                 size_t dataLen,
                                 PixelFormat format,
                                 unsigned char** outData,
                                 size_t* outDataLen);
PixelFormat convertBGRA8ToFormat(const unsigned char* data,
                                 size_t dataLen,
                                 PixelFormat format,
                                 unsigned char** outData,
                                 size_t* outDataLen);

// L8 to XXX
void convertL8ToRGB8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertL8ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertL8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertL8ToRGBA4(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertL8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertL8ToLA8(const unsigned char* data, size_t dataLen, unsigned char* outData);

// LA8 to XXX
void convertLA8ToRGB8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToRGBA4(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertLA8ToL8(const unsigned char* data, size_t dataLen, unsigned char* outData);

// RGB8 to XXX
void convertRGB8ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToL8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToLA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToRGBA4(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);

// RGBA8 to XXX
void convertRGBA8ToRGB8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToRGB565(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToL8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToLA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToRGBA4(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA8ToRGB5A1(const unsigned char* data, size_t dataLen, unsigned char* outData);

// XXX to RGBA8
void convertRGB5A1ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGB565ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertA8ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
void convertRGBA4ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);

// BGRA8 to XXX
void convertBGRA8ToRGBA8(const unsigned char* data, size_t dataLen, unsigned char* outData);
};  // namespace PixelFormatUtils
}  // namespace backend
NS_CC_END
