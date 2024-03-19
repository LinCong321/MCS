#include "basic_block.h"

namespace mcs {
    llvm::BasicBlock* BasicBlock::getBasicBlock() const {
        return basicBlock_;
    }

    void BasicBlock::setReturnValue(llvm::Value* value) {
        returnValue_ = value;
    }

    llvm::Value* BasicBlock::getReturnValue() const {
        return returnValue_;
    }
}