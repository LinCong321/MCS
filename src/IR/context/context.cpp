#include "context.h"
#include "utils/logger.h"

namespace mcs {
    Context& Context::getInstance() {
        static Context self;
        return self;
    }

    bool Context::popBlock() {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to pop block because blocks_ is empty.");
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
            LOG_ERROR("Unable to get current block because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to get current block because blocks_.top() is nullptr.");
            return nullptr;
        }
        return blocks_.top()->getBasicBlock();
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.push(std::make_unique<CodeBlock>(basicBlock));
    }

    bool Context::setCurrentReturnValue(llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to set current return value because blocks_ is empty.");
            return false;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to set current return value because blocks_.top() is nullptr.");
            return false;
        }
        blocks_.top()->setReturnValue(value);
        return true;
    }

    bool Context::insertLocalSymbol(const std::string& symbol, llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to insert local symbol because blocks_ is empty.");
            return {};
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to insert local symbol because blocks_.top() is nullptr.");
            return {};
        }
        return blocks_.top()->insertSymbol(symbol, value);
    }

    llvm::Value* Context::getCurrentReturnValue() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current return value because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to get current return value because blocks_.top() is nullptr.");
            return nullptr;
        }
        return blocks_.top()->getReturnValue();
    }

    std::string Context::getCurrentFunctionName() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current function name because blocks_ is empty.");
            return {};
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to get current function name because blocks_.top() is nullptr.");
            return {};
        }
        return blocks_.top()->getFunctionName();
    }

    bool Context::checkLocalSymbol(const std::string& symbol) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to check local symbol because blocks_ is empty.");
            return {};
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to check local symbol because blocks_.top() is nullptr.");
            return {};
        }
        return blocks_.top()->checkExist(symbol);
    }

    llvm::Value* Context::getLocalVariable(const std::string& id) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get local variable because blocks_ is empty.");
            return {};
        }
        if (blocks_.top() == nullptr) {
            LOG_ERROR("Unable to get local variable because blocks_.top() is nullptr.");
            return {};
        }
        return blocks_.top()->getVariable(id);
    }
}