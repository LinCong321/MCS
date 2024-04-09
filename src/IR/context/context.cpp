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
        blocks_.pop_back();
        return true;
    }

    llvm::Module& Context::getModule() {
        return module_;
    }

    void Context::setScope(Scope scope) {
        scope_ = scope;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.emplace_back(std::make_unique<CodeBlock>(basicBlock));
    }

    bool Context::setCurrentReturnValue(llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to set current return symbol because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to set current return symbol because blocks_.back() is nullptr.");
            return false;
        }
        blocks_.back()->setReturnValue(value);
        return true;
    }

    bool Context::insertSymbol(const std::string& name, const Symbol& symbol) {
        switch (getScope()) {
            case Scope::GLOBAL:
                return insertGlobalSymbol(name, symbol);
            case Scope::LOCAL:
                return insertLocalSymbol(name, symbol);
            default:
                LOG_ERROR("Unable to insert symbol because the scope type is unknown.");
                return false;
        }
    }

    Scope Context::getScope() const {
        return scope_;
    }

    llvm::BasicBlock* Context::getCurrentBlock() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current block because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get current block because blocks_.back() is nullptr.");
            return nullptr;
        }
        return blocks_.back()->getBasicBlock();
    }

    llvm::Value* Context::getCurrentReturnValue() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current return symbol because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get current return symbol because blocks_.back() is nullptr.");
            return nullptr;
        }
        return blocks_.back()->getReturnValue();
    }

    std::string Context::getCurrentFunctionName() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current function name because blocks_ is empty.");
            return {};
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get current function name because blocks_.back() is nullptr.");
            return {};
        }
        return blocks_.back()->getFunctionName();
    }

    bool Context::checkSymbol(const std::string& name) const {
        switch (getScope()) {
            case Scope::GLOBAL:
                return checkGlobalSymbol(name);
            case Scope::LOCAL:
                return checkLocalSymbol(name);
            default:
                LOG_ERROR("Unable to check symbol because the scope type is unknown.");
                return false;
        }
    }

    Symbol Context::getSymbol(const std::string& name) const {
        for (auto it = blocks_.crbegin(); it != blocks_.crend(); it++) {
            if (*it == nullptr) {
                LOG_ERROR("Unable to get symbol because *it is nullptr.");
                return {};
            }
            if ((*it)->checkExist(name)) {
                return (*it)->getSymbol(name);
            }
        }
        return {};
    }

    bool Context::checkLocalSymbol(const std::string& name) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to check local symbol because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to check local symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->checkExist(name);
    }

    bool Context::checkGlobalSymbol(const std::string& name) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to check global symbol because blocks is empty.");
            return false;
        }
        if (blocks_.front() == nullptr) {
            LOG_ERROR("Unable to check global symbol because blocks_.front() is nullptr.");
            return false;
        }
        return blocks_.front()->checkExist(name);
    }

    bool Context::insertLocalSymbol(const std::string& name, const Symbol& symbol) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to insert local symbol because blocks_ is empty.");
            return true;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to insert local symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->insertSymbol(name, symbol);
    }

    bool Context::insertGlobalSymbol(const std::string& name, const Symbol& symbol) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to insert local symbol because blocks_ is empty.");
            return true;
        }
        if (blocks_.front() == nullptr) {
            LOG_ERROR("Unable to insert local symbol because blocks_.front() is nullptr.");
            return false;
        }
        return blocks_.front()->insertSymbol(name, symbol);
    }
}