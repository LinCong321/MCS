#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    enum class Type : uint {
        INT = 1,
        FLOAT = 2,
        VOID = 3,
        UNKNOWN = 4,
    };

    Type strToType(const std::string& str);
    Type getTypeOfValue(const llvm::Value* value);
    std::ostream& operator<<(std::ostream& out, Type type);
}