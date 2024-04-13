#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createAllocaInst(llvm::Type* type);
    llvm::Instruction* createLoadInst(const std::string& id);
    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable);
    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id);
}