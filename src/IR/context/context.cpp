#include "context.h"
#include "utils/logger.h"

namespace mcs {
    Context& Context::getInstance() {
        static Context self;
        return self;
    }

    bool Context::popBlock() {
        if (blocks_.empty()) {
            LOG_ERROR("Cannot pop block because blocks_ is empty.");
            return false;
        }
        blocks_.pop();
        return true;
    }

    llvm::Module& Context::getModule() {
        return module_;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    llvm::BasicBlock* Context::getCurrentBlock() {
        if (blocks_.empty()) {
            LOG_ERROR("Cannot get current block because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Cannot get current block because blocks_.top() is nullptr.");
            return nullptr;
        }
        return blocks_.top()->getBasicBlock();
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.push(std::make_unique<CodeBlock>(basicBlock));
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
        if (blocks_.empty()) {
            LOG_ERROR("Cannot get current return value because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Cannot get current return value because blocks_.top() is nullptr.");
            return nullptr;
        }
        return blocks_.top()->getReturnValue();
    }

    std::string Context::getCurrentFunctionName() const {
        if (blocks_.empty()) {
            LOG_ERROR("Cannot get current function name because blocks_ is empty.");
            return {};
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Cannot get current function name because blocks_.top() is nullptr.");
            return {};
        }
        return blocks_.top()->getFunctionName();
    }
}