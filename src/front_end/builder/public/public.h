#pragma once

#include "IR/type/type.h"

namespace mcs {
    llvm::Type* getLLVMType(Type type);
    llvm::Type* getLLVMType(const std::string& str);

    llvm::Value* getCastedValue(llvm::Value* value, Type type);
    llvm::Value* getCastedValue(llvm::Value* value, llvm::Type* type);
}