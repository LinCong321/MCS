#pragma once

#include "AST/number/number.h"

namespace mcs {
    class FloatNum : public Number {
    public:
        explicit FloatNum(float val) : val_(val) {}
        ~FloatNum() override = default;

    public:
        explicit FloatNum(Node* node) : val_(getFloatVal(node)) {}
        FloatNum(char op, Node* node) : val_(getFloatVal(op, node)) {}
        FloatNum(Node* lhs, char op, Node* rhs) : val_(getFloatVal(lhs, op, rhs)) {}

    public:
        Type getType() const override;
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override {}

    public:
        float getValue() const;

    private:
        static float getFloatVal(Node* node);
        static float getFloatVal(char op, Node* node);
        static float getFloatVal(Node* lhs, char op, Node* rhs);

    private:
        float val_;
    };
}