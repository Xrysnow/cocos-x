#pragma once

#include "input/gamepad/GamepadTypes.h"

#include <cstddef>
#include <string>
#include <vector>

namespace cc::input {

enum class MappingSource { BuiltIn, Application, User };
enum class MappingChange { Added, Replaced, Unchanged, Shadowed, ConditionSkipped, Error };

struct Diagnostic {
    std::size_t line = 0;
    std::size_t column = 0;
    std::string code;
    std::string message;
};

struct MappingResult {
    MappingChange change = MappingChange::Error;
    std::vector<Diagnostic> diagnostics;

    constexpr int sdlCode() const noexcept {
        switch (change) {
        case MappingChange::Added: return 1;
        case MappingChange::Error: return -1;
        default: return 0;
        }
    }
};

struct ImportReport {
    unsigned added = 0;
    unsigned replaced = 0;
    unsigned unchanged = 0;
    unsigned skipped = 0;
    unsigned failed = 0;
    std::vector<Diagnostic> diagnostics;
    Error batchError = Error::None;
};

} // namespace cc::input
