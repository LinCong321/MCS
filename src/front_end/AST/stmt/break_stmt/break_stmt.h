#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class BreakStmt : public Stmt {
    public:
        BreakStmt() = default;
        ~BreakStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}
    };
}