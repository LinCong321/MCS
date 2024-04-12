#pragma once

#include <ostream>

namespace mcs {
    enum class Operator : uint {
        ARITHMETIC,
        LOGICAL,
        RELATIONAL,
        UNKNOWN,
    };

    Operator strToOp(const std::string& str);
    std::ostream& operator<<(std::ostream& out, Operator op);
}