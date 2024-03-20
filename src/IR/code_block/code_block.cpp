#include "code_block.h"
#include "utils/logger.h"
#include "llvm/IR/Function.h"

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

    std::string CodeBlock::getFunctionName() const {
        if (basicBlock_ == nullptr) {
            LOG_ERROR("Cannot get function name because basicBlock_ is nullptr.");
            return {};
        }
        const auto parent = basicBlock_->getParent();
        if (parent == nullptr) {
            LOG_ERROR("Cannot get function name because parent is nullptr.");
            return {};
        }
        return parent->getName().str();
    }
}