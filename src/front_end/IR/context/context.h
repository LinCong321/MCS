#pragma once

#include "IR/scope/scope.h"
#include "IR/code_block/code_block.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();

    public:
        bool popBlock();
        llvm::Module& getModule();
        bool clearInsertionPoint();
        llvm::LLVMContext& getContext();
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool setInsertPoint(llvm::BasicBlock* basicBlock);
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    public:
        Scope getCurrentScope() const;
        llvm::BasicBlock* getInsertBlock() const;
        llvm::Function* getCurrentFunction() const;
        std::string getCurrentFunctionName() const;
        bool findSymbol(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;
        llvm::Type* getReturnTypeOfCurrentFunction() const;

    private:
        Context() : context_(), module_("main", context_), blocks_() {}
        ~Context() = default;

    private:
        llvm::LLVMContext                       context_;
        llvm::Module                            module_;
        std::vector<std::unique_ptr<CodeBlock>> blocks_;
    };
}