#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    bool declareVariable(llvm::Type* type, const std::string& id, llvm::Value* value, bool isConstant);
    bool declareVariable(const std::string& type, const std::string& id, llvm::Value* value, bool isConstant);
}