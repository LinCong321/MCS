#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createBreakInst();
    llvm::Instruction* createContinueInst();
    llvm::Instruction* createJumpInst(llvm::BasicBlock* basicBlock);

    llvm::Instruction* createPHINode(const std::vector<std::pair<llvm::Value*, llvm::BasicBlock*>>& nodes);
    llvm::Instruction* createBranchInst(llvm::BasicBlock* ifTrue, llvm::BasicBlock* ifFalse, llvm::Value* cond);
}