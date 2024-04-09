#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Symbol {
    public:
        explicit Symbol(llvm::Type* type = nullptr, llvm::Value* value = nullptr) : type_(type), value_(value) {}
        ~Symbol() = default;

    public:
        llvm::Type* getType() const;
        llvm::Value* getValue() const;

    private:
        llvm::Type*     type_;
        llvm::Value*    value_;
    };
}