#pragma once

#include "AST/node/node.h"

namespace mcs {
    class Block : public Node {};

    class BlockItem : public Block {
    public:
        BlockItem() = default;
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