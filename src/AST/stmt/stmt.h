#pragma once

#include "AST/pub/node.h"

namespace mcs {
    class Stmt : public Node {};

    class RetStmt : public Stmt {
    public:
        RetStmt(int retVal) : retVal_(retVal) {}
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;
    private:
        int retVal_;
    };
}