#pragma once

#include "pub/node.h"

namespace mcs {
    class Block : public Node {};

    class BlockItem : public Block {
    public:
        explicit BlockItem(Node* node);
        ~BlockItem() override = default;

    public:
        llvm::Value* codeGen() const override;

    public:
        void pushBack(Node* node);

    private:
        std::vector<std::unique_ptr<Node>> items_;
    };
}