#pragma once

#include "platform/SystemInfo.h"
#include <initializer_list>

namespace cc::system_info {
void missing(ValueMap& data, const char* field, const char* reason);
ValueMap failure(const char* code, const char* context, int64_t nativeCode = 0);
ValueMap finish(ValueMap data, std::initializer_list<const char*> fields);
ValueMap readComputer(bool identifiers);
ValueMap readOs();
ValueMap readCpu();
ValueMap readMemory();
ValueMap readUptime();
ValueMap readNetwork();
void startNetworkEvents();
void stopNetworkEvents();
void networkChanged();
} // namespace cc::system_info
