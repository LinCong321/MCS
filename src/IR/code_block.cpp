#include "code_block.h"

namespace mcs {
    llvm::BasicBlock* CodeBlock::getBasicBlock() const {
        return basicBlock_;
    }

    void CodeBlock::setReturnValue(llvm::Value* value) {
        returnValue_ = value;
    }

    llvm::Value* CodeBlock::getReturnValue() const {
        return returnValue_;
    }
}