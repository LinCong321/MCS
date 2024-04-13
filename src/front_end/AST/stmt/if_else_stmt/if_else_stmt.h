#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class IfElseStmt : public Stmt {
    public:
        IfElseStmt(Node* cond, Node* thenStmt, Node* elseStmt = nullptr) : cond_(cond),
                                                                           thenStmt_(thenStmt),
                                                                           elseStmt_(elseStmt) {}
        ~IfElseStmt() = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;
        llvm::Value* createBranchInst() const;
        void createBranchInstWithElse() const;
        void createBranchInstWithoutElse() const;
        bool createThenBranch(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const;
        bool createElseBranch(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const;
        static std::pair<llvm::BasicBlock*, llvm::BasicBlock*> getBlockPair(llvm::Value* condition);

    private:
        std::unique_ptr<Node> cond_;
        std::unique_ptr<Node> thenStmt_;
        std::unique_ptr<Node> elseStmt_;
    };
}