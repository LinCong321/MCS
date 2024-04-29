#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createReturnInst(llvm::Value* value = nullptr);
    llvm::Instruction* createCallInst(const std::string& id, const std::vector<llvm::Value*>& values);
}