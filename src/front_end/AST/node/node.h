#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Node {
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codeGen() const = 0;
    };
}