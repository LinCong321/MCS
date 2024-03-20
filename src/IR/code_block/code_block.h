#pragma once

#include <map>
#include "llvm/IR/BasicBlock.h"

namespace mcs {
    class CodeBlock {
    public:
        explicit CodeBlock(llvm::BasicBlock* basicBlock) : basicBlock_(basicBlock),
                                                           returnValue_(nullptr),
                                                           symbolTable_() {}
        ~CodeBlock() = default;
        
    public:
        void setReturnValue(llvm::Value* value);
        llvm::Value* getReturnValue() const;
        std::string getFunctionName() const;

    private:
        llvm::BasicBlock*                   basicBlock_;
        llvm::Value*                        returnValue_;
        std::map<std::string, llvm::Value*> symbolTable_;
    };
}