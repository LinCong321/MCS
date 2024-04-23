#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class RetStmt : public Stmt {
    public:
        explicit RetStmt(Node* retVal = nullptr) : retVal_(retVal) {}
        ~RetStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        llvm::Instruction* getReturnInst() const;

    private:
        std::unique_ptr<Node> retVal_;
    };
}