#pragma once

#include "IR/scope/scope.h"
#include "IR/symbol_table/symbol_table.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();

    public:
        void createSymbolTable();
        bool deleteSymbolTable();
        llvm::Module& getModule();
        llvm::LLVMContext& getContext();
        void setInsertPoint(llvm::BasicBlock* basicBlock);
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    public:
        Scope getCurrentScope() const;
        llvm::BasicBlock* getInsertBlock() const;
        llvm::Function* getCurrentFunction() const;
        std::string getCurrentFunctionName() const;
        bool checkSymbol(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;
        llvm::Type* getReturnTypeOfCurrentFunction() const;

    private:
        Context() : context_(), module_("main", context_), tables_(1), insertBlock_(nullptr) {}
        ~Context() = default;

    private:
        llvm::LLVMContext           context_;
        llvm::Module                module_;
        std::vector<SymbolTable>    tables_;
        llvm::BasicBlock*           insertBlock_;
    };
}