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

    llvm::Value* CodeBlock::getReturnValue() const {
        return returnValue_;
    }

    std::string CodeBlock::getFunctionName() const {
        if (basicBlock_ == nullptr) {
            LOG_ERROR("Unable to get function name because basicBlock_ is nullptr.");
            return {};
        }
        const auto parent = basicBlock_->getParent();
        if (parent == nullptr) {
            LOG_ERROR("Unable to get function name because parent is nullptr.");
            return {};
        }
        return parent->getName().str();
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
            return {};
        }
        return symbolTable_->getSymbol(name);
    }
}