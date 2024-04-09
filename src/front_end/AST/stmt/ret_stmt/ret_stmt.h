#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class RetStmt : public Stmt {
    public:
        explicit RetStmt(Node* retVal = nullptr) : retVal_(retVal) {}
        ~RetStmt() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        static bool checkReturned();
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node> retVal_;
    };
}