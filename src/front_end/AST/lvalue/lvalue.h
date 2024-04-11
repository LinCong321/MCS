#pragma once

#include "AST/node/node.h"

namespace mcs {
    class LValue {
    public:
        explicit LValue(std::string* id) : id_(id) {}

    public:
        std::string getId() const;

    private:
        std::unique_ptr<std::string> id_;
    };
}