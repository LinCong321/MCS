#include "context.h"
#include "utils/logger.h"

namespace mcs {
    Context& Context::getInstance() {
        static Context self;
        return self;
    }

    void Context::createSymbolTable() {
        tables_.emplace_back();
    }

    bool Context::deleteSymbolTable() {
        if (tables_.empty()) {
            LOG_ERROR("Unable to delete symbol table because tables_ is empty.");
            return false;
        }
        tables_.pop_back();
        return true;
    }

    llvm::Module& Context::getModule() {
        return module_;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    void Context::setInsertPoint(llvm::BasicBlock* basicBlock) {
        insertBlock_ = basicBlock;
        createSymbolTable();
    }

    bool Context::insertSymbol(const std::string& name, const Symbol& symbol) {
        if (tables_.empty()) {
            LOG_ERROR("Unable to insert symbol because tables_ is empty.");
            return false;
        }
        tables_.back().insertSymbol(name, symbol);
        return true;
    }

    Scope Context::getCurrentScope() const {
        return tables_.size() > 1 ? Scope::LOCAL : Scope::GLOBAL;
    }

    llvm::BasicBlock* Context::getInsertBlock() const {
        return insertBlock_;
    }

    llvm::Function* Context::getCurrentFunction() const {
        if (insertBlock_ == nullptr) {
            LOG_ERROR("Unable to get current function name because insertBlock_ is nullptr.");
            return {};
        }
        return insertBlock_->getParent();
    }

    std::string Context::getCurrentFunctionName() const {
        const auto function = getCurrentFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to get current function name because function is nullptr.");
            return {};
        }
        return function->getName().str();
    }

    bool Context::checkSymbol(const std::string& name) const {
        if (tables_.empty()) {
            LOG_ERROR("Unable to check local symbol because blocks_ is empty.");
            return false;
        }
        return tables_.back().checkExist(name);
    }

    Symbol Context::getSymbol(const std::string& name) const {
        for (auto it = tables_.crbegin(); it != tables_.crend(); it++) {
            if (it->checkExist(name)) {
                return it->getSymbol(name);
            }
        }
        return Symbol();
    }

    llvm::Type* Context::getReturnTypeOfCurrentFunction() const {
        const auto function = getCurrentFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to get current function return type because function is nullptr.");
            return nullptr;
        }
        return function->getReturnType();
    }
}