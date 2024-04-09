#pragma once

#include "stmt.h"

namespace mcs {
    class RetStmt : public Stmt {
    public:
        explicit RetStmt(Node* retVal) : retVal_(retVal) {}
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