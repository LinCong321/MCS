#pragma once

#include <list>
#include <stack>

#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "IR/loop_info/loop_info.h"
#include "IR/symbol_table/symbol_table.h"
#include "IR/insertion_point/insertion_point.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();

    public:
        llvm::Module& getModule();
        llvm::LLVMContext& getContext();

    public:
        void createSymbolTable();
        bool deleteSymbolTable();

    public:
        bool popBlock();
        bool clearInsertionPoint();
        llvm::BasicBlock* getInsertBlock() const;
        bool pushBlock(llvm::BasicBlock* basicBlock);
        bool setInsertPoint(llvm::BasicBlock* basicBlock);

    public:
        bool popLoopInfo();
        void pushLoopInfo(const LoopInfo& loopInfo);
        bool getCurrentLoopInfo(LoopInfo& loopInfo) const;

    public:
        Scope getCurrentScope() const;
        std::string getCurrentFunctionName() const;
        llvm::Type* getReturnTypeOfCurrentFunction() const;

    public:
        bool findSymbol(const std::string& name) const;
        llvm::Type* getSymbolType(const std::string& name) const;
        bool getSymbol(const std::string& name, Symbol& symbol) const;
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    private:
        Context() : context_(), module_("main", context_), insertionPoint_() {}
        ~Context() = default;

    private:
        llvm::LLVMContext       context_;
        llvm::Module            module_;
        InsertionPoint          insertionPoint_;
        std::list<SymbolTable>  tables_;
        std::stack<LoopInfo>    loopInfo_;
    };
}