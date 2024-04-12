#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class BinaryExp : public Exp {
    public:
        BinaryExp(Node* lhs, std::string* op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        BinaryExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(std::make_unique<std::string>(1, op)), rhs_(rhs) {}
        ~BinaryExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    protected:
        std::unique_ptr<Node>           lhs_;
        std::unique_ptr<std::string>    op_;
        std::unique_ptr<Node>           rhs_;
    };
}