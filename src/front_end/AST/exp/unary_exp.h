#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class UnaryExp : public Exp {
    public:
        UnaryExp(char op, Node* val) : op_(op), val_(val) {}
        ~UnaryExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        char                    op_;
        std::unique_ptr<Node>   val_;
    };
}