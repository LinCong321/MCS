#pragma once

#include "AST/exp/exp.h"
#include "AST/lvalue/lvalue.h"

namespace mcs {
    class VarExp : public Exp {
    public:
        explicit VarExp(LValue* lValue) : lvalue_(lValue) {}
        ~VarExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<LValue> lvalue_;
    };
}