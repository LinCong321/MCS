#include "code_block.h"

#include <memory>
#include "utils/logger.h"
#include "llvm/IR/Function.h"

namespace mcs {
    CodeBlock::CodeBlock(llvm::BasicBlock* basicBlock, std::unique_ptr<SymbolTable> symbolTable)
        : basicBlock_(basicBlock), symbolTable_(nullptr) {
        if (symbolTable == nullptr) {
            symbolTable_ = std::make_unique<SymbolTable>();
        } else {
            symbolTable_ = std::move(symbolTable);
        }
    }

    void CodeBlock::clearBasicBlock() {
        basicBlock_ = nullptr;
    }

    std::unique_ptr<SymbolTable> CodeBlock::getSymbolTable() {
        return std::move(symbolTable_);
    }

    bool CodeBlock::insertSymbol(const std::string& name, const Symbol& symbol) {
        if (symbolTable_ == nullptr) {
            LOG_ERROR("Unable to insert symbol because symbolTable_ is nullptr.");
            return false;
        }
        symbolTable_->insertSymbol(name, symbol);
        return true;
    }

    llvm::Function* CodeBlock::getFunction() const {
        if (basicBlock_ == nullptr) {
            LOG_ERROR("Unable to get function because basicBlock_ is nullptr.");
            return {};
        }
        return basicBlock_->getParent();
    }

    llvm::BasicBlock* CodeBlock::getBasicBlock() const {
        return basicBlock_;
    }

    bool CodeBlock::checkExist(const std::string& name) const {
        if (symbolTable_ == nullptr) {
            LOG_ERROR("Unable to check exist because symbolTable_ is nullptr.");
            return false;
        }
        return symbolTable_->checkExist(name);
    }

    Symbol CodeBlock::getSymbol(const std::string& name) const {
        if (symbolTable_ == nullptr) {
            LOG_ERROR("Unable to get symbol because symbolTable_ is nullptr.");
            return Symbol();
        }
        return symbolTable_->getSymbol(name);
    }
}