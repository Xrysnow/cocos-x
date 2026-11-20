#pragma once

#include "platform/TextInputTypes.h"

#include <memory>

namespace cc
{
class TextInputBackend;
std::unique_ptr<TextInputBackend> createIOSTextInputBackend(void* hostView);
std::optional<TextInputStateChanged> iosKeyboardChange(void* hostView, void* notification, TextInputState observed);
}  // namespace cc
