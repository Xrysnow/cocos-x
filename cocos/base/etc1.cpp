// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "base/etc1.h"

#include <string.h>

static const char kMagic[] = {'P', 'K', 'M', ' ', '1', '0'};

static const etc1_uint32 ETC1_PKM_FORMAT_OFFSET         = 6;
static const etc1_uint32 ETC1_PKM_ENCODED_WIDTH_OFFSET  = 8;
static const etc1_uint32 ETC1_PKM_ENCODED_HEIGHT_OFFSET = 10;
static const etc1_uint32 ETC1_PKM_WIDTH_OFFSET          = 12;
static const etc1_uint32 ETC1_PKM_HEIGHT_OFFSET         = 14;

static const etc1_uint32 ETC1_RGB_NO_MIPMAPS = 0;

// static void writeBEUint16(etc1_byte* pOut, etc1_uint32 data) {
//     pOut[0] = (etc1_byte) (data >> 8);
//     pOut[1] = (etc1_byte) data;
// }

static etc1_uint32 readBEUint16(const etc1_byte* pIn)
{
    return (pIn[0] << 8) | pIn[1];
}

// Format a PKM header

// void etc1_pkm_format_header(etc1_byte* pHeader, etc1_uint32 width, etc1_uint32 height) {
//     memcpy(pHeader, kMagic, sizeof(kMagic));
//     etc1_uint32 encodedWidth = (width + 3) & ~3;
//     etc1_uint32 encodedHeight = (height + 3) & ~3;
//     writeBEUint16(pHeader + ETC1_PKM_FORMAT_OFFSET, ETC1_RGB_NO_MIPMAPS);
//     writeBEUint16(pHeader + ETC1_PKM_ENCODED_WIDTH_OFFSET, encodedWidth);
//     writeBEUint16(pHeader + ETC1_PKM_ENCODED_HEIGHT_OFFSET, encodedHeight);
//     writeBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET, width);
//     writeBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET, height);
// }

// Check if a PKM header is correctly formatted.

etc1_bool etc1_pkm_is_valid(const etc1_byte* pHeader)
{
    if (memcmp(pHeader, kMagic, sizeof(kMagic)))
    {
        return false;
    }
    etc1_uint32 format        = readBEUint16(pHeader + ETC1_PKM_FORMAT_OFFSET);
    etc1_uint32 encodedWidth  = readBEUint16(pHeader + ETC1_PKM_ENCODED_WIDTH_OFFSET);
    etc1_uint32 encodedHeight = readBEUint16(pHeader + ETC1_PKM_ENCODED_HEIGHT_OFFSET);
    etc1_uint32 width         = readBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET);
    etc1_uint32 height        = readBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET);
    return format == ETC1_RGB_NO_MIPMAPS && encodedWidth >= width && encodedWidth - width < 4 &&
           encodedHeight >= height && encodedHeight - height < 4;
}

// Read the image width from a PKM header

etc1_uint32 etc1_pkm_get_width(const etc1_byte* pHeader)
{
    return readBEUint16(pHeader + ETC1_PKM_WIDTH_OFFSET);
}

// Read the image height from a PKM header

etc1_uint32 etc1_pkm_get_height(const etc1_byte* pHeader)
{
    return readBEUint16(pHeader + ETC1_PKM_HEIGHT_OFFSET);
}
