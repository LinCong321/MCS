#pragma once

#include "node/node.h"

namespace mcs {
    class Block : public Node {
    public:
        Block(Node* stmt) : stmt_(stmt) {}
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;
    private:
        std::unique_ptr<Node> stmt_;
    };
}