/****************************************************************************
 Copyright (c) 2021-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

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

#include "base/Macros.h"

#include <cstdarg>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace cc {
namespace StringUtils {

template <typename T>
std::string toString(T arg) {
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

CC_DLL int vprintf(char *buf, const char *last, const char *fmt, va_list args);
CC_DLL int printf(char *buf, const char *last, const char *fmt, ...);
// Return the full formatted string, or an empty string on a formatting error.
CC_DLL std::string format(const char *fmt, ...) CC_FORMAT_PRINTF(1, 2);
CC_DLL std::string vformat(const char *fmt, va_list args);
CC_DLL std::vector<std::string> split(const std::string &str, const std::string &delims, uint32_t maxSplits = 0);
CC_DLL std::string &replace(std::string &str, const std::string &findStr, const std::string &replaceStr);
CC_DLL std::string &replaceAll(std::string &str, const std::string &findStr, const std::string &replaceStr);
CC_DLL std::string &tolower(std::string &str);
CC_DLL std::string &toupper(std::string &str);

} // namespace StringUtils

namespace StringUtil = StringUtils;

} // namespace cc
