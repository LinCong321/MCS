#pragma once

#include "scope/scope.h"
#include "code_block/code_block.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();

    public:
        bool popBlock();
        llvm::Module& getModule();
        llvm::LLVMContext& getContext();
        void setCurrentScope(Scope scope);
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool setCurrentReturnValue(llvm::Value* value);
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    public:
        Scope getCurrentScope() const;
        llvm::BasicBlock* getCurrentBlock() const;
        llvm::Value* getCurrentReturnValue() const;
        std::string getCurrentFunctionName() const;
        bool checkSymbol(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;

    private:
        Context() : context_(), module_("main", context_), scope_(Scope::GLOBAL), blocks_() {}
        ~Context() = default;

    private:
        bool checkLocalSymbol(const std::string& name) const;
        bool checkGlobalSymbol(const std::string& name) const;
        bool insertLocalSymbol(const std::string& name, const Symbol& symbol);
        bool insertGlobalSymbol(const std::string& name, const Symbol& symbol);

    private:
        using Blocks = std::vector<std::unique_ptr<CodeBlock>>;

    private:
        llvm::LLVMContext   context_;
        llvm::Module        module_;
        Scope               scope_;
        Blocks              blocks_;
    };
}