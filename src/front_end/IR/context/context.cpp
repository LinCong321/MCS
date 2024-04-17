#include "context.h"
#include "utils/logger.h"

namespace mcs {
    Context& Context::getInstance() {
        static Context self;
        return self;
    }

    llvm::Module& Context::getModule() {
        return module_;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    void Context::createSymbolTable() {
        tables_.emplace_back();
    }

    bool Context::deleteSymbolTable() {
        if (tables_.empty()) {
            LOG_ERROR("Unable to pop block because tables_ is empty.");
            return false;
        }
        tables_.pop_back();
        return true;
    }

    bool Context::popBlock() {
        insertionPoint_.clearFunction();
        return deleteSymbolTable();
    }

    bool Context::clearInsertionPoint() {
        return insertionPoint_.clearBlock(getCurrentScope());
    }

    llvm::BasicBlock* Context::getInsertBlock() const {
        return insertionPoint_.getBlock(getCurrentScope());
    }

    bool Context::pushBlock(llvm::BasicBlock* basicBlock) {
        createSymbolTable();
        return insertionPoint_.setBlock(basicBlock, getCurrentScope());
    }

    bool Context::setInsertPoint(llvm::BasicBlock* basicBlock) {
        return insertionPoint_.insertBlock(basicBlock, getCurrentScope());
    }

    bool Context::popLoopInfo() {
        if (loopInfo_.empty()) {
            LOG_ERROR("Unable to pop loop information because loopInfo_ is empty.");
            return false;
        }
        loopInfo_.pop();
        return true;
    }

    void Context::pushLoopInfo(const LoopInfo& loopInfo) {
        loopInfo_.push(loopInfo);
    }

    bool Context::getCurrentLoopInfo(LoopInfo& loopInfo) const {
        if (loopInfo_.empty()) {
            LOG_ERROR("Unable to get current loop information because loopInfo_ is empty.");
            return false;
        }
        loopInfo = loopInfo_.top();
        return true;
    }

    Scope Context::getCurrentScope() const {
        if (tables_.empty()) {
            LOG_ERROR("Unable to get current scope because blocks_ is empty.");
            return Scope::UNKNOWN;
        }
        return tables_.size() == 1 ? Scope::GLOBAL : Scope::LOCAL;
    }

    std::string Context::getCurrentFunctionName() const {
        return insertionPoint_.getFunctionName(getCurrentScope());
    }

    llvm::Type* Context::getReturnTypeOfCurrentFunction() const {
        return insertionPoint_.getFunctionReturnType(getCurrentScope());
    }

    bool Context::findSymbol(const std::string& name) const {
        if (tables_.empty()) {
            LOG_ERROR("Unable to check symbol because blocks_ is empty.");
            return false;
        }
        return tables_.back().checkExist(name);
    }

    bool Context::getSymbol(const std::string& name, Symbol& symbol) const {
        for (auto it = tables_.crbegin(); it != tables_.crend(); it++) {
            if (it->checkExist(name)) {
                symbol = it->getSymbol(name);
                return true;
            }
        }
        return false;
    }

    bool Context::insertSymbol(const std::string& name, const Symbol& symbol) {
        if (tables_.empty()) {
            LOG_ERROR("Unable to insert symbol because blocks_ is empty.");
            return false;
        }
        tables_.back().insertSymbol(name, symbol);
        return true;
    }
}