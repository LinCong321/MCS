#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Node {
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codeGen() = 0;
    };
}