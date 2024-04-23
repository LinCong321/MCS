#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class ContinueStmt : public Stmt {
    public:
        ContinueStmt() = default;
        ~ContinueStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}
    };
}