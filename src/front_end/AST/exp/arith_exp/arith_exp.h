#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class ArithExp : public Exp {
    public:
        ArithExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~ArithExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node>   lhs_;
        char                    op_;
        std::unique_ptr<Node>   rhs_;
    };
}