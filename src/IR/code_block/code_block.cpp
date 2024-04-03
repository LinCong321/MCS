#include "code_block.h"
#include "utils/logger.h"
#include "llvm/IR/Function.h"

namespace mcs {
    void CodeBlock::setReturnValue(llvm::Value* value) {
        returnValue_ = value;
    }

    bool CodeBlock::insertSymbol(const std::string& symbol, llvm::Value* value) {
        symbolTable_[symbol] = value;
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

    bool CodeBlock::checkExist(const std::string& symbol) const {
        return symbolTable_.find(symbol) != symbolTable_.end();
    }

    llvm::Value* CodeBlock::getVariable(const std::string& symbol) const {
        const auto it = symbolTable_.find(symbol);
        if (it == symbolTable_.end()) {
            LOG_ERROR("Unable to get variable because the symbol (aka \"", symbol, "\" is not in the symbol table.");
            return nullptr;
        }
        return it->second;
    }
}