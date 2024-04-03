#pragma once

#include <stack>

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
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool setCurrentReturnValue(llvm::Value* value);
        bool insertSymbol(const std::string& symbol, llvm::Value* value, Scope scope);

    public:
        Scope getCurrentScope() const;
        llvm::BasicBlock* getCurrentBlock() const;
        llvm::Value* getCurrentReturnValue() const;
        std::string getCurrentFunctionName() const;
        bool checkSymbol(const std::string& symbol, Scope scope) const;
        llvm::Value* getVariable(const std::string& symbol, Scope scope) const;
        
    private:
        Context() : context_(), module_("main", context_), blocks_(), symbolTable_() {}
        ~Context() = default;

    private:
        bool checkLocalSymbol(const std::string& symbol) const;
        bool checkGlobalSymbol(const std::string& symbol) const;
        llvm::Value* getLocalVariable(const std::string& symbol) const;
        llvm::Value* getGlobalVariable(const std::string& symbol) const;
        bool insertLocalSymbol(const std::string& symbol, llvm::Value* value);
        bool insertGlobalSymbol(const std::string& symbol, llvm::Value* value);
        
    private:
        llvm::LLVMContext                       context_;
        llvm::Module                            module_;
        std::stack<std::unique_ptr<CodeBlock>>  blocks_;
        std::map<std::string, llvm::Value*>     symbolTable_;
    };
}