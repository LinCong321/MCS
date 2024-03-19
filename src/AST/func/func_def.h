#pragma once

#include "node/node.h"

namespace mcs {
    class FuncDef : public Node {
    public:
        FuncDef(std::string* funcType, std::string* id, Node* block) : funcType_(funcType), id_(id), block_(block) {}
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;
    private:
        std::unique_ptr<std::string> funcType_;
        std::unique_ptr<std::string> id_;
        std::unique_ptr<Node> block_;
    };
}