#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    bool declareVariable(llvm::Type* type, const std::string& id, llvm::Value* value);

    bool declareVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value);

    bool declareVariable(bool isConstant, const std::string& type, const std::string& id,
                         const std::vector<int>& arraySize, llvm::Value* value);
}