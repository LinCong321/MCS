#pragma once

#include "AST/exp/exp.h"
#include "llvm/IR/BasicBlock.h"

namespace mcs {
    class LogicExp : public Exp {
    public:
        LogicExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~LogicExp() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}

    private:
        using PhiNode = std::pair<llvm::Value*, llvm::BasicBlock*>;

    private:
        bool checkAllMemberPointers() const;
        PhiNode getLhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const;
        PhiNode getRhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const;

    private:
        std::unique_ptr<Node>   lhs_;
        char                    op_;
        std::unique_ptr<Node>   rhs_;
    };
}