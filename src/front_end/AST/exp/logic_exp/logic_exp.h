#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class LogicExp : public Exp {
    public:
        LogicExp(Node* lhs, std::string* op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~LogicExp() override = default;

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