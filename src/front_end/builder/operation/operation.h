#pragma once

#include "llvm/IR/Value.h"
#include "IR/operator/operator.h"

namespace mcs {
    llvm::Value* getUnaryOperation(char op, llvm::Value* value);
    llvm::Value* getBinaryOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs);

    llvm::Value* getLogicalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs);
    llvm::Value* getArithmeticOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs);
    llvm::Value* getRelationalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs);
}