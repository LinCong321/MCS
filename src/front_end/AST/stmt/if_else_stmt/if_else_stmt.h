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
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        bool checkAllMemberPointers() const;
        llvm::Value* createBranch(llvm::BasicBlock* trueBlock, llvm::BasicBlock* falseBlock) const;

    private:
        bool createThenBranch(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const;
        bool createElseBranch(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const;
        void createBranchWithElse(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const;
        void createBranchWithoutElse(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const;

    private:
        std::unique_ptr<Node> cond_;
        std::unique_ptr<Node> thenStmt_;
        std::unique_ptr<Node> elseStmt_;
    };
}