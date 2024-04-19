#pragma once

#include "AST/node/node.h"

namespace mcs {
    class FuncArgsExp {
    public:
        FuncArgsExp(Node* node);
        ~FuncArgsExp() = default;

    public:
        void pushBack(Node* node);
        bool readEach(const std::function<void(const Node& node)>& function);

    private:
        std::vector<std::unique_ptr<Node>> funcArgs_;
    };
}