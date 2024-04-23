#pragma once

#include "AST/node/node.h"

namespace mcs {
    class ArraySize {
    public:
        explicit ArraySize(Node* node);
        ~ArraySize() = default;

    public:
        void pushBack(Node* node);

    private:
        std::vector<std::unique_ptr<Node>> arraySize_;
    };
}