#pragma once

#include "llvm/IR/BasicBlock.h"

namespace mcs {
    class LoopInfo {
    public:
        explicit LoopInfo(llvm::BasicBlock* continueBlock = nullptr, llvm::BasicBlock* breakBlock = nullptr)
            : continueBlock_(continueBlock), breakBlock_(breakBlock) {}
        ~LoopInfo() = default;

    public:
        llvm::BasicBlock* getBreakBlock() const;
        llvm::BasicBlock* getContinueBlock() const;

    private:
        llvm::BasicBlock* continueBlock_;
        llvm::BasicBlock* breakBlock_;
    };
}