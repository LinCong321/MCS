#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Symbol {
    public:
        explicit Symbol(llvm::Type* type = nullptr, llvm::Value* value = nullptr, bool isConstant = false)
            : type_(type), value_(value), isConstant_(isConstant) {}
        ~Symbol() = default;

    public:
        bool isConstant() const;
        llvm::Type* getType() const;
        llvm::Value* getValue() const;

    private:
        llvm::Type*     type_;
        llvm::Value*    value_;
        bool            isConstant_;
    };
}