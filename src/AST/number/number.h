#pragma once

#include "pub/node.h"

namespace mcs {
    class Number : public Node {};

    class IntNum : public Number {
    public:
        explicit IntNum(int32_t val) : val_(val) {}
        ~IntNum() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        int32_t val_;
    };

    class FloatNum : public Number {
    public:
        explicit FloatNum(float val) : val_(val) {}
        ~FloatNum() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        float val_;
    };
}