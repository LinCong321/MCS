#pragma once

#include "llvm/IR/Value.h"
#include "IR/parameter/parameter.h"

namespace mcs {
    bool declareFunctionParam(const Parameter& parameter, llvm::Value* value);

    bool declareVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value);
    bool declareVariable(bool isConstant, const std::string& type, const std::string& id, llvm::Value* value);

    bool declareArray(bool isConstant, llvm::Type* type, const std::string& id, llvm::Constant* initializer = nullptr);
}