#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    llvm::Value* getUnaryOperation(char op, llvm::Value* value);
    llvm::Value* getBinaryOperation(llvm::Value* lhs, char op, llvm::Value* rhs);
}