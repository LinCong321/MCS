#pragma once

#include "IR/scope/scope.h"
#include "llvm/IR/BasicBlock.h"

namespace mcs {
    class InsertionPoint {
    public:
        InsertionPoint() : globalBlock_(nullptr), localBlock_(nullptr), function_(nullptr) {}
        ~InsertionPoint() = default;

    public:
        void clearFunction();
        bool clearBlock(Scope scope);
        bool setBlock(llvm::BasicBlock* basicBlock, Scope scope);
        bool insertBlock(llvm::BasicBlock* basicBlock, Scope scope);

    public:
        llvm::BasicBlock* getBlock(Scope scope) const;
        std::string getFunctionName(Scope scope) const;
        llvm::Type* getFunctionReturnType(Scope scope) const;

    private:
        llvm::Function* getGlobalFunction() const;
        llvm::Function* getFunction(Scope scope) const;
        bool setFunction(llvm::BasicBlock* basicBlock);
        bool resetBlock(llvm::BasicBlock* basicBlock, Scope scope);

    private:
        llvm::BasicBlock*   globalBlock_;
        llvm::BasicBlock*   localBlock_;
        llvm::Function*     function_;
    };
}