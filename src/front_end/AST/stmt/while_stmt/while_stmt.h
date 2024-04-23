#pragma once

#include "AST/stmt/stmt.h"

namespace mcs {
    class WhileStmt : public Stmt {
    public:
        WhileStmt(Node* cond, Node* stmt) : cond_(cond), stmt_(stmt) {}
        ~WhileStmt() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        bool checkAllMemberPointers() const;
        void createLoopBody(llvm::BasicBlock* condBlock, llvm::BasicBlock* bodyBlock) const;
        llvm::BasicBlock* createCondBlock(llvm::BasicBlock* bodyBlock, llvm::BasicBlock* nextBlock) const;

    private:
        std::unique_ptr<Node> cond_;
        std::unique_ptr<Node> stmt_;
    };
}