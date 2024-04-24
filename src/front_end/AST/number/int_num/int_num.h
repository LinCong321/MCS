#pragma once

#include "AST/number/number.h"

namespace mcs {
    class IntNum : public Number {
    public:
        explicit IntNum(int32_t val) : val_(val) {}
        ~IntNum() override = default;

    public:
        explicit IntNum(Node* node) : val_(getIntVal(node)) {}
        IntNum(char op, Node* node) : val_(getIntVal(op, node)) {}
        IntNum(Node* lhs, char op, Node* rhs) : val_(getIntVal(lhs, op, rhs)) {}

    public:
        Type getType() const override;
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}

    public:
        int getValue() const;

    private:
        static int getIntVal(Node* node);
        static int getIntVal(char op, Node* node);
        static int getIntVal(Node* lhs, char op, Node* rhs);

    private:
        int32_t val_;
    };
}