#pragma once

#include "IR/type/type.h"
#include "IR/scope/scope.h"

namespace mcs {
    llvm::Type* strToType(const std::string& type);
    llvm::Value* getCastedValue(llvm::Value* value, Type to);
    llvm::Value* assignToVariable(llvm::Value* variable, llvm::Value* value, Scope scope);
}