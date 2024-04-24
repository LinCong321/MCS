#pragma once

#include "AST/node/node.h"

namespace mcs {
    class ArraySize {
    public:
        explicit ArraySize(Node* node);
        ~ArraySize() = default;

    public:
        void constFold();
        void pushBack(Node* node);
        bool readEach(const std::function<void(Node&)>& function) const;

    private:
        std::vector<std::unique_ptr<Node>> arraySize_;
    };
}