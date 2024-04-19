#pragma once

#include "AST/exp/exp.h"
#include "AST/exp/func_args_exp/func_args_exp.h"

namespace mcs {
    class FuncCallExp : public Exp {
    public:
        explicit FuncCallExp(std::string* id, FuncArgsExp* funcArgs = nullptr) : id_(id), funcArgs_(funcArgs) {}
        ~FuncCallExp() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;
        std::vector<llvm::Value*> getArgs() const;

    private:
        std::unique_ptr<std::string> id_;
        std::unique_ptr<FuncArgsExp> funcArgs_;
    };
}