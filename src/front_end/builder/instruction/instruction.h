#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createAllocaInst(llvm::Type* type);
    llvm::Instruction* createLoadInst(const std::string& id);
    llvm::Instruction* createReturnInst(llvm::Value* value = nullptr);

    llvm::Instruction* createStoreInst(llvm::Value* variable, llvm::Value* value);
    llvm::Instruction* createStoreInst(const std::string& id, llvm::Value* value);
}