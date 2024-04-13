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

    bool Context::clearInsertionPoint() {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to clear insertion point because blocks_ is empty.");
            return false;
        }
        blocks_.back()->clearBasicBlock();
        return true;
    }

    llvm::LLVMContext& Context::getContext() {
        return context_;
    }

    void Context::pushBlock(llvm::BasicBlock* basicBlock) {
        blocks_.emplace_back(std::make_unique<CodeBlock>(basicBlock));
    }

    bool Context::insertBlock(llvm::BasicBlock* basicBlock) {
        if (!insertBlockIntoCurrentFunction(basicBlock)) {
            LOG_ERROR("Unable to insert block because basicBlock cannot be inserted into the current function.");
            return false;
        }
        pushBlock(basicBlock);
        return true;
    }

    bool Context::setInsertPoint(llvm::BasicBlock* basicBlock) {
        if (!insertBlockIntoCurrentFunction(basicBlock)) {
            LOG_ERROR("Unable to set insert point because basicBlock cannot be inserted into the current function.");
            return false;
        }
        return moveCurrentSymbolTableToNewBlock(basicBlock);
    }

    bool Context::insertSymbol(const std::string& name, const Symbol& symbol) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to insert symbol because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to insert symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->insertSymbol(name, symbol);
    }

    Scope Context::getCurrentScope() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current scope because blocks_ is empty.");
            return Scope::UNKNOWN;
        }
        return blocks_.size() == 1 ? Scope::GLOBAL : Scope::LOCAL;
    }

    llvm::BasicBlock* Context::getInsertBlock() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get insert block because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get insert block because blocks_.back() is nullptr.");
            return nullptr;
        }
        return blocks_.back()->getBasicBlock();
    }

    llvm::Function* Context::getCurrentFunction() const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to get current function because blocks_ is empty.");
            return nullptr;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to get current function because blocks_.back() is nullptr.");
            return nullptr;
        }
        return blocks_.back()->getFunction();
    }

    std::string Context::getCurrentFunctionName() const {
        const auto function = getCurrentFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to get current function name because function is nullptr.");
            return {};
        }
        return function->getName().str();
    }

    bool Context::findSymbol(const std::string& name) const {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to check symbol because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to check symbol because blocks_.back() is nullptr.");
            return false;
        }
        return blocks_.back()->checkExist(name);
    }

    llvm::Type* Context::getReturnTypeOfCurrentFunction() const {
        const auto function = getCurrentFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to get the return type of current function because function is nullptr.");
            return nullptr;
        }
        return function->getReturnType();
    }

    bool Context::getSymbol(const std::string& name, Symbol& symbol) const {
        for (auto it = blocks_.crbegin(); it != blocks_.crend(); it++) {
            if (*it == nullptr) {
                LOG_ERROR("Unable to get symbol because *it is nullptr.");
                return false;
            }
            if ((*it)->checkExist(name)) {
                symbol = (*it)->getSymbol(name);
                return true;
            }
        }
        return false;
    }

    bool Context::moveCurrentSymbolTableToNewBlock(llvm::BasicBlock* basicBlock) {
        if (blocks_.empty()) {
            LOG_ERROR("Unable to move current symbol table to a new block because blocks_ is empty.");
            return false;
        }
        if (blocks_.back() == nullptr) {
            LOG_ERROR("Unable to move current symbol table to a new block because blocks_.back() is nullptr.");
            return false;
        }
        blocks_.back() = std::make_unique<CodeBlock>(basicBlock, blocks_.back()->getSymbolTable());
        return true;
    }

    bool Context::insertBlockIntoCurrentFunction(llvm::BasicBlock* basicBlock) const {
        const auto function = getCurrentFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to insert a block into the current function because function is nullptr.");
            return false;
        }
        function->insert(function->end(), basicBlock);
        return true;
    }
}