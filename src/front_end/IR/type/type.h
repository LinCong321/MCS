#pragma once

#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace mcs {
    enum class Type : uint {
        VOID = 0,
        BOOL,
        INT,
        FLOAT,
        UNKNOWN,
    };

    Type getTypeOf(const std::string& str);
    Type getTypeOf(const llvm::Type* type);
    Type getTypeOf(const llvm::Value* value);
    Type getTypeOf(llvm::Type::TypeID typeId);

    std::ostream& operator<<(std::ostream& out, Type type);
}