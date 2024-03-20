#pragma once

#include "node/node.h"

namespace mcs {
    class CompUnit : public Node {
    public:
        CompUnit(Node* node);
        ~CompUnit() = default;

    public:
        llvm::Value* codeGen() override;
        void pushBack(Node* node);

    private:
        std::vector<std::unique_ptr<Node>> units_;
    };
}