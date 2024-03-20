#pragma once

#include "node/node.h"

namespace mcs {
    class FuncDef : public Node {
    public:
        FuncDef(std::string* retType, std::string* id, Node* block) : retType_(retType),
                                                                      id_(id),
                                                                      block_(block) {}
        ~FuncDef() override = default;

    public:
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const;

    private:
        std::unique_ptr<std::string> retType_;
        std::unique_ptr<std::string> id_;
        std::unique_ptr<Node> block_;
    };
}