#include "context.h"
#include "utils/logger.h"

namespace mcs {
    Context& Context::getInstance() {
        static Context self;
        return self;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    llvm::Module& Context::getModule() {
        return module_;
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.push(std::make_unique<CodeBlock>(basicBlock));
    }

    bool Context::popBlock() {
        if (blocks_.empty()) {
            LOG_ERROR("Cannot pop block because blocks_ is empty.");
            return false;
        }
        blocks_.pop();
        return true;
    }

    bool Context::setCurrentReturnValue(llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Cannot set current return value because blocks_ is empty.");
            return false;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Cannot set current return value because blocks_.top() is nullptr.");
            return false;
        }
        blocks_.top()->setReturnValue(value);
        return true;
    }

    llvm::Value* Context::getCurrentReturnValue() const {
        if (blocks_.empty() || blocks_.top() == nullptr) {
            return nullptr;
        }
        return blocks_.top()->getReturnValue();
    }
}