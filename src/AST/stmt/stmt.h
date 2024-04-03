#pragma once

#include "pub/node.h"

namespace mcs {
    class Stmt : public Node {
    public:
        llvm::Value* codeGen() const override;
    };

    class RetStmt : public Stmt {
    public:
        explicit RetStmt(Node* retVal) : retVal_(retVal) {}
        ~RetStmt() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<Node> retVal_;
    };
}