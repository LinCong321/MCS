#pragma once

#include "node/node.h"

namespace mcs {
    class CompUnit : public Node {
    public:
        CompUnit(Node* funcDef) : funcDef_(funcDef) {}
        llvm::Value* codeGen() override;
        bool checkAllMemberPtr() const override;
    private:
        std::unique_ptr<Node> funcDef_;
    };
}