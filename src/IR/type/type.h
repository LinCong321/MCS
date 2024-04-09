#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    enum class Type : uint {
        INT = 0,
        FLOAT,
        VOID,
        UNKNOWN,
    };

    Type strToType(const std::string& str);
    Type getTypeOfValue(const llvm::Value* value);
    std::ostream& operator<<(std::ostream& out, Type type);
    Type getMaxType(const llvm::Value* value1, const llvm::Value* value2);
}