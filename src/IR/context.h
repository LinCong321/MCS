#pragma once

#include <stack>
#include <memory>
#include "basic_block.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();
        
    public:
        llvm::LLVMContext& getContext();
        llvm::Module*& getModule();
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool popBlock();
        bool setCurrentReturnValue(llvm::Value* value);
        llvm::Value* getCurrentReturnValue() const;
        
    private:
        Context() : context_(), module_(new llvm::Module("main", context_)), blocks_() {}
        ~Context() { delete module_; }
        
    private:
        llvm::LLVMContext                        context_;
        llvm::Module*                            module_;
        std::stack<std::unique_ptr<BasicBlock>>  blocks_;
    };
}