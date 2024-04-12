#pragma once

#include "AST/exp/binary_exp/binary_exp.h"

namespace mcs {
    class LogicExp : public BinaryExp {
    public:
        LogicExp(Node* lhs, std::string* op, Node* rhs) : BinaryExp(lhs, rhs), op_(op) {}

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<std::string> op_;
    };
}