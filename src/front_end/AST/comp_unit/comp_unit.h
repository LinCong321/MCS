#pragma once

#include "node/node.h"

namespace mcs {
    class CompUnit : public Node {
    public:
        explicit CompUnit(Node* node);
        ~CompUnit() override = default;

    public:
        llvm::Value* codeGen() const override;

    public:
        void pushBack(Node* node);

    private:
        std::vector<std::unique_ptr<Node>> units_;
    };
}