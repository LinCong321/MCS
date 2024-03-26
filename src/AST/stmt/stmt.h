#pragma once

#include "node/node.h"

namespace mcs {
    class Stmt : public Node {
    public:
        llvm::Value* codeGen() override;
    };

    class RetStmt : public Stmt {
    public:
        explicit RetStmt(Node* retVal) : retVal_(retVal) {}
        ~RetStmt() override = default;

    public:
        llvm::Value* codeGen() override;

    private:
        static bool checkReturned();
        bool checkAllMemberPtr() const;

    private:
        std::unique_ptr<Node> retVal_;
    };
}