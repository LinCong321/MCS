#pragma once

#include "node/node.h"

namespace mcs {
    class VarDef {
    public:
        explicit VarDef(std::string* id, Node* value = nullptr) : id_(id), value_(value) {}
        ~VarDef() = default;

    public:
        std::string getId() const;
        llvm::Value* getValue() const;

    private:
        std::unique_ptr<std::string>    id_;
        std::unique_ptr<Node>           value_;
    };
}