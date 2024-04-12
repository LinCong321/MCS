#include "code_block.h"
#include "utils/logger.h"
#include "llvm/IR/Function.h"

namespace mcs {
    void CodeBlock::setReturnValue(llvm::Value* value) {
        returnValue_ = value;
    }

    bool CodeBlock::insertSymbol(const std::string& name, const Symbol& symbol) {
        if (symbolTable_ == nullptr) {
            LOG_ERROR("Unable to insert symbol because symbolTable_ is nullptr.");
            return false;
        }
        symbolTable_->insertSymbol(name, symbol);
        return true;
    }

    std::string CodeBlock::getFunctionName() const {
        const auto function = getFunction();
        if (function == nullptr) {
            LOG_ERROR("Unable to get function name because function is nullptr.");
            return {};
        }
        return function->getName().str();
    }

    llvm::Function* CodeBlock::getFunction() const {
        if (basicBlock_ == nullptr) {
            LOG_ERROR("Unable to get function because basicBlock_ is nullptr.");
            return {};
        }
        return basicBlock_->getParent();
    }

    llvm::Value* CodeBlock::getReturnValue() const {
        return returnValue_;
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
            LOG_ERROR("Unable to check exist because symbolTable_ is nullptr.");
            return Symbol();
        }
        return symbolTable_->getSymbol(name);
    }
}