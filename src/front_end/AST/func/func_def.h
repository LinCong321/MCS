#pragma once

#include "AST/node/node.h"

namespace mcs {
    class FuncDef : public Node {
    public:
        FuncDef(std::string* retType, std::string* name, Node* block) : retType_(retType), name_(name), block_(block) {}
        ~FuncDef() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<std::string>    retType_;
        std::unique_ptr<std::string>    name_;
        std::unique_ptr<Node>           block_;
    };
}