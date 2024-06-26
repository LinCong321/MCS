#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class BlockStmt : public Stmt {
    public:
        explicit BlockStmt(Node* block) : block_(block) {}
        ~BlockStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node> block_;
    };
}