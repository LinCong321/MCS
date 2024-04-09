#pragma once

#include "stmt.h"

namespace mcs {
    class BlockStmt : public Stmt {
    public:
        explicit BlockStmt(Node* block) : block_(block) {}
        ~BlockStmt() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node> block_;
    };
}