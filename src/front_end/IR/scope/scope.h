#pragma once

#include <ostream>

namespace mcs {
    enum class Scope : uint {
        GLOBAL = 0,
        LOCAL,
    };

    std::ostream& operator<<(std::ostream& out, Scope scope);
}