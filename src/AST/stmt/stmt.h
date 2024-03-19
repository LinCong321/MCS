#pragma once

#include "node/node.h"

namespace mcs {
    class Stmt : public Node {};

    class RetStmt : public Stmt {
    public:
        RetStmt(int retVal) : retVal_(retVal) {}
        ~RetStmt() = default;
    public:
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;
    private:
        int retVal_;
    };
}