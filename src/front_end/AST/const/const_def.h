#pragma once

#include "AST/node/node.h"

namespace mcs {
    class ConstDef {
    public:
        explicit ConstDef(std::string* id, Node* value = nullptr) : id_(id), value_(value) {}
        ~ConstDef() = default;

    public:
        std::string getId() const;
        llvm::Value* getValue() const;

    private:
        std::unique_ptr<std::string>    id_;
        std::unique_ptr<Node>           value_;
    };
}