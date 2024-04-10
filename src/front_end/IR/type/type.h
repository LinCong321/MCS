#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    enum class Type : uint {
        INT = 0,
        FLOAT,
        VOID,
        UNKNOWN,
    };

    std::ostream& operator<<(std::ostream& out, Type type);

    Type strToType(const std::string& str);
    Type getTypeOf(const llvm::Type* type);
    Type getTypeOf(const llvm::Value* value);
    Type getMaxType(const llvm::Value* value1, const llvm::Value* value2);
}