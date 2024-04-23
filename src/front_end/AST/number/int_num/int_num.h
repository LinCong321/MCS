#pragma once

#include "AST/number/number.h"

namespace mcs {
    class IntNum : public Number {
    public:
        explicit IntNum(int32_t val) : val_(val) {}
        ~IntNum() override = default;

    public:
        explicit IntNum(Node* node) : val_(getIntVal(node)) {}
        IntNum(char op, Node* val) : val_(getInitVal(op, val)) {}
        IntNum(Node* lhs, char op, Node* rhs) : val_(getInitVal(lhs, op, rhs)) {}

    public:
        Type getType() const override;
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}

    public:
        int getValue() const;

    private:
        static int getIntVal(Node* node);
        static int getInitVal(char op, Node* val);
        static int getInitVal(Node* lhs, char op, Node* rhs);

    private:
        int32_t val_;
    };
}