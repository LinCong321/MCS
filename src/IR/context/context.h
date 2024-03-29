#pragma once

#include <stack>

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_block/code_block.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();
        
    public:
        bool popBlock();
        llvm::Module& getModule();
        llvm::LLVMContext& getContext();
        llvm::BasicBlock* getCurrentBlock();
        llvm::Value* getCurrentReturnValue() const;
        std::string getCurrentFunctionName() const;
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool setCurrentReturnValue(llvm::Value* value);
        
    private:
        Context() : context_(), module_("main", context_), blocks_() {}
        ~Context() = default;
        
    private:
        llvm::LLVMContext                       context_;
        llvm::Module                            module_;
        std::stack<std::unique_ptr<CodeBlock>>  blocks_;
    };
}