#pragma once

#include "IR/type/type.h"
#include "IR/scope/scope.h"

namespace mcs {
    llvm::Type* getLLVMType(const std::string& str);
    llvm::Value* getCastedValue(llvm::Value* value, Type type);
    llvm::Constant* getConstantValue(llvm::Value* value, const std::string& str);
}