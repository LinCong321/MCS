#pragma once

#include <memory>
#include <string>
#include "llvm/IR/Value.h"

namespace mcs {
    class Node {
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codeGen() = 0;
        virtual bool checkAllMemberPtr() const = 0;
    };
}