#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    llvm::Value* createUnaryOperation(char op, llvm::Value* value);

    llvm::Value* createBinaryOperation(llvm::Value* lhs, char op, llvm::Value* rhs);
    llvm::Value* createBinaryOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs);
}