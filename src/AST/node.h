#pragma once

#include <memory>
#include <string>
#include "llvm/IR/Value.h"

namespace mcs {
    class Node {
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codeGen() = 0;
    };

    class CompUnit : public Node {
    public:
        CompUnit(Node* funcDef) : funcDef_(funcDef) {}
        llvm::Value* codeGen() override;
    private:
        std::unique_ptr<Node> funcDef_;
    };

    class FuncDef : public Node {
    public:
        FuncDef(std::string* funcType, std::string* id, Node* block) : funcType_(funcType), id_(id), block_(block) {}
        llvm::Value* codeGen() override;
        const char* getId() const;
    private:
        std::unique_ptr<std::string> funcType_;
        std::unique_ptr<std::string> id_;
        std::unique_ptr<Node> block_;
    };

    class Block : public Node {
    public:
        Block(Node* stmt) : stmt_(stmt) {}
        llvm::Value* codeGen() override;
    private:
        std::unique_ptr<Node> stmt_;
    };

    class Stmt : public Node {};

    class RetStmt : public Stmt {
    public:
        RetStmt(int retVal) : retVal_(retVal) {}
        llvm::Value* codeGen() override;
    private:
        int retVal_;
    };
}