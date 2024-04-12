#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class BinaryExp : public Exp {
    public:
        BinaryExp(Node* lhs, Node* rhs) : lhs_(lhs), rhs_(rhs) {}
        ~BinaryExp() override = default;

    protected:
        std::unique_ptr<Node> lhs_;
        std::unique_ptr<Node> rhs_;
    };
}