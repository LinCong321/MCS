#pragma once

#include "IR/type/type.h"
#include "AST/node/node.h"

namespace mcs {
    class Number : public Node {
    public:
        virtual Type getType() const = 0;
    };

    Type getTypeOf(Node* node);

    std::unique_ptr<Number> getNumber(char op, Node* node);
    std::unique_ptr<Number> getNumber(const std::string& name);
    std::unique_ptr<Number> getNumber(Node* lhs, char op, Node* rhs);

    std::unique_ptr<Number> getNumber(Node* node, Type type);
    std::unique_ptr<Number> getNumber(Node* node, const std::string& str);
}