#pragma once

#include "AST/stmt/stmt.h"
#include "AST/lvalue/lvalue.h"

namespace mcs {
    class AssignStmt : public Stmt {
    public:
        AssignStmt(LValue* lValue, Node* exp) : lvalue_(lValue), exp_(exp) {}
        ~AssignStmt() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<LValue> lvalue_;
        std::unique_ptr<Node>   exp_;
    };
}