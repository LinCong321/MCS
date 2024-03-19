#pragma once

#include "node/node.h"

namespace mcs {
    class CompUnit : public Node {
    public:
        CompUnit(Node* node);
        ~CompUnit() = default;

    public:
        void pushBack(Node* node);
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;

    private:
        std::vector<std::unique_ptr<Node>> units_;
    };
}