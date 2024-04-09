#pragma once

#include "node/node.h"

namespace mcs {
    class Stmt : public Node {
    public:
        llvm::Value* codeGen() const override;
    };
}