#pragma once

#include "IR/symbol_table/symbol_table.h"
#include "llvm/IR/BasicBlock.h"

namespace mcs {
    class CodeBlock {
    public:
        explicit CodeBlock(llvm::BasicBlock* basicBlock) : basicBlock_(basicBlock),
                                                           returnValue_(nullptr),
                                                           symbolTable_(new SymbolTable) {}
        ~CodeBlock() = default;

    public:
        void setReturnValue(llvm::Value* value);
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    public:
        std::string getFunctionName() const;
        llvm::Function* getFunction() const;
        llvm::Value* getReturnValue() const;
        llvm::BasicBlock* getBasicBlock() const;
        bool checkExist(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;

    private:
        llvm::BasicBlock*               basicBlock_;
        llvm::Value*                    returnValue_;
        std::unique_ptr<SymbolTable>    symbolTable_;
    };
}