#pragma once

#include "IR/scope/scope.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "IR/loop_info/loop_info.h"
#include "IR/code_block/code_block.h"

namespace mcs {
    class Context {
    public:
        static Context& getInstance();

    public:
        llvm::Module& getModule();
        llvm::LLVMContext& getContext();

    public:
        bool popBlock();
        bool overwriteBlock();
        void pushBlock(llvm::BasicBlock* basicBlock);
        bool insertBlock(llvm::BasicBlock* basicBlock);

    public:
        bool clearInsertionPoint();
        llvm::BasicBlock* getInsertBlock() const;
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
        bool getSymbol(const std::string& name, Symbol& symbol) const;
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    private:
        llvm::Function* getCurrentFunction() const;
        bool setCurrentBasicBlock(llvm::BasicBlock* basicBlock);
        bool insertBlockIntoCurrentFunction(llvm::BasicBlock* basicBlock) const;

    private:
        Context() : context_(), module_("main", context_), blocks_(), loopInfo_() {}
        ~Context() = default;

    private:
        llvm::LLVMContext                       context_;
        llvm::Module                            module_;
        std::vector<std::unique_ptr<CodeBlock>> blocks_;
        std::vector<LoopInfo>                   loopInfo_;
    };
}