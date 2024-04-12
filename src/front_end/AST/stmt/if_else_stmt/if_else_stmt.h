#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class IfElseStmt : public Stmt {
    public:
        IfElseStmt(Node* cond, Node* thenStmt, Node* elseStmt = nullptr) : cond_(cond),
                                                                           thenStmt_(thenStmt),
                                                                           elseStmt_(elseStmt) {}
        ~IfElseStmt() = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node> cond_;
        std::unique_ptr<Node> thenStmt_;
        std::unique_ptr<Node> elseStmt_;
    };
}