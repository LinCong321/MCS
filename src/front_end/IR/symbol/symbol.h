#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Symbol {
    public:
        Symbol() : isConstant_(false), type_(nullptr), value_(nullptr), pointerElementType_(nullptr) {}
        Symbol(bool isConstant, llvm::Type* type, llvm::Value* value, llvm::Type* pointerElementType = nullptr)
            : isConstant_(isConstant), type_(type), value_(value), pointerElementType_(pointerElementType) {}
        ~Symbol() = default;

    public:
        bool isConstant() const;
        llvm::Type* getType() const;
        llvm::Value* getValue() const;
        llvm::Type* getPointerElementType() const;

    private:
        bool            isConstant_;
        llvm::Type*     type_;
        llvm::Value*    value_;
        llvm::Type*     pointerElementType_;
    };
}