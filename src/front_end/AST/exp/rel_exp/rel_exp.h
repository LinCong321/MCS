#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class RelExp : public Exp {
    public:
        RelExp(Node* lhs, std::string* op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~RelExp() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node>           lhs_;
        std::unique_ptr<std::string>    op_;
        std::unique_ptr<Node>           rhs_;
    };
}