#pragma once

#include "AST/node/node.h"

namespace mcs {
    class LValue {
    public:
        explicit LValue(std::string* id) : id_(id) {}

    public:
        std::string getId() const;
        void pushBack(Node* node);
        std::vector<llvm::Value*> getIndices() const;

    private:
        std::unique_ptr<std::string> id_;
        std::vector<std::unique_ptr<Node>> indices_;
    };
}