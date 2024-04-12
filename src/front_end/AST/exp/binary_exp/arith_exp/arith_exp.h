#pragma once

#include "AST/exp/binary_exp/binary_exp.h"

namespace mcs {
    class ArithExp : public BinaryExp {
    public:
        ArithExp(Node* lhs, char op, Node* rhs) : BinaryExp(lhs, rhs), op_(op) {}
        ~ArithExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        char op_;
    };
}