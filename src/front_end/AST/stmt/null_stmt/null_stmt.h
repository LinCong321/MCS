#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class NullStmt : public Stmt{
    public:
        NullStmt() = default;
        ~NullStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}
    };
}