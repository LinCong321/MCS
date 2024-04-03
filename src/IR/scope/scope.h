#pragma once

#include <ostream>

namespace mcs {
    enum class Scope : uint {
        GLOBAL = 0,
        LOCAL,
        UNKNOWN,
    };

    std::ostream& operator<<(std::ostream& out, Scope scope);
}