#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class ContinueStmt : public Stmt {
    public:
        ContinueStmt() = default;
        ~ContinueStmt() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        static llvm::Value* createBranchInst(llvm::BasicBlock* basicBlock);
    };
}