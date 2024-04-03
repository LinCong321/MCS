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

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.emplace_back(std::make_unique<CodeBlock>(basicBlock));
    }

    bool Context::setCurrentReturnValue(llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to set current return value because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to set current return value because blocks_.back() is nullptr.");
            return false;
        }
        blocks_.back()->setReturnValue(value);
        return true;
    }

    bool Context::insertSymbol(const std::string& symbol, llvm::Value* value) {
        switch (getCurrentScope()) {
            case Scope::GLOBAL:
                return insertGlobalSymbol(symbol, value);
            case Scope::LOCAL:
                return insertLocalSymbol(symbol, value);
            default:
                LOG_ERROR("Unable to insert symbol because the scope type is unknown.");
                return false;
        }
    }

    Scope Context::getCurrentScope() const {
        return blocks_.empty() ? Scope::GLOBAL : Scope::LOCAL;
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
            LOG_ERROR("Unable to get current return value because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get current return value because blocks_.back() is nullptr.");
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

    bool Context::checkSymbol(const std::string& symbol) const {
        switch (getCurrentScope()) {
            case Scope::GLOBAL:
                return checkGlobalSymbol(symbol);
            case Scope::LOCAL:
                return checkLocalSymbol(symbol);
            default:
                LOG_ERROR("Unable to check symbol because the scope type is unknown.");
                return false;
        }
    }

    llvm::Value* Context::getVariable(const std::string& symbol) const {
        const auto localVariable = getLocalVariable(symbol);
        return localVariable != nullptr ? localVariable : getGlobalVariable(symbol);
    }

    bool Context::checkLocalSymbol(const std::string& symbol) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to check local symbol because blocks is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to check local symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->checkExist(symbol);
    }

    bool Context::checkGlobalSymbol(const std::string& symbol) const {
        return symbolTable_.find(symbol) != symbolTable_.end();
    }

    llvm::Value* Context::getLocalVariable(const std::string& symbol) const {
        for (auto it = blocks_.crbegin(); it != blocks_.crend(); it++) {
            if (*it == nullptr) {
                LOG_ERROR("Unable to get local variable because *it is nullptr.");
                return nullptr;
            }
            if ((*it)->checkExist(symbol)) {
                return (*it)->getVariable(symbol);
            }
        }
        return nullptr;
    }

    llvm::Value* Context::getGlobalVariable(const std::string& symbol) const {
        const auto it = symbolTable_.find(symbol);
        if (it == symbolTable_.end()) {
            LOG_ERROR("Unable to get global variable because the symbol (aka \"", symbol,
                      "\") is not in the global symbol table.");
            return nullptr;
        }
        return it->second;
    }

    bool Context::insertLocalSymbol(const std::string& symbol, llvm::Value* value) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to insert local symbol because blocks_ is empty.");
            return true;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to insert local symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->insertSymbol(symbol, value);
    }

    bool Context::insertGlobalSymbol(const std::string& symbol, llvm::Value* value) {
        symbolTable_[symbol] = value;
        return true;
    }
}