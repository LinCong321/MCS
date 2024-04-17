#pragma once

#include "AST/exp/exp.h"

namespace mcs {
    class FuncCallExp : public Exp {
    public:
        explicit FuncCallExp(std::string* id) : id_(id) {}
        ~FuncCallExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<std::string> id_;
    };
}