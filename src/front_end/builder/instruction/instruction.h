#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createCallInst(const std::string& id);
    llvm::Instruction* createReturnInst(llvm::Value* value = nullptr);

    llvm::Instruction* createAllocaInst(llvm::Type* type);
    llvm::Instruction* createLoadInst(const std::string& id);

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable);
    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id);

    llvm::Instruction* createBreakInst();
    llvm::Instruction* createContinueInst();
    llvm::Instruction* createJumpInst(llvm::BasicBlock* basicBlock);

    llvm::Instruction* createPHINode(const std::vector<std::pair<llvm::Value*, llvm::BasicBlock*>>& nodes);
    llvm::Instruction* createBranchInst(llvm::BasicBlock* ifTrue, llvm::BasicBlock* ifFalse, llvm::Value* cond);
}