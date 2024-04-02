#pragma once

#include "exp.h"
#include "IR/type/type.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    class BinaryExp : public Exp {
    public:
        BinaryExp(Node* lhs, char op, Node* rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
        ~BinaryExp() override = default;

    public:
        llvm::Value* codeGen() override;

    private:
        bool checkAllMemberPtr() const;
        llvm::Instruction::BinaryOps getOperation(Type type) const;

    private:
        std::unique_ptr<Node>   lhs_;
        char                    op_;
        std::unique_ptr<Node>   rhs_;
    };
}