#pragma once

#include "node/node.h"

namespace mcs {
    class Exp : public Node {};

    class BinaryExp : public Exp {
    public:
        BinaryExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~BinaryExp() override = default;

    public:
        llvm::Value* codeGen() override;

    private:
        std::unique_ptr<Node>   lhs_;
        char                    op_;
        std::unique_ptr<Node>   rhs_;
    };
}