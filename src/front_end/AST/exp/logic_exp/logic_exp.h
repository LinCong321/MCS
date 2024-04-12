#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class LogicExp : public Exp {
    public:
        LogicExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~LogicExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;
        llvm::Value* createOrOperation() const;
        llvm::Value* createAndOperation() const;
        llvm::Value* createLogicalOperation() const;

    protected:
        std::unique_ptr<Node>   lhs_;
        char                    op_;
        std::unique_ptr<Node>   rhs_;
    };
}