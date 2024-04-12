#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Symbol {
    public:
        explicit Symbol(llvm::Value* value = nullptr, llvm::Type* type = nullptr, bool isConstant = false)
            : value_(value), type_(type), isConstant_(isConstant) {}
        ~Symbol() = default;

    public:
        bool isConstant() const;
        llvm::Type* getType() const;
        llvm::Value* getValue() const;

    private:
        llvm::Value*    value_;
        llvm::Type*     type_;
        bool            isConstant_;
    };
}