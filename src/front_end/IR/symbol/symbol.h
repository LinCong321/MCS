#pragma once

#include "llvm/IR/Value.h"

namespace mcs {
    class Symbol {
    public:
        Symbol() : isConstant_(false), type_(nullptr), name_(), value_(nullptr) {}
        ~Symbol() = default;

    public:
        Symbol(llvm::Type* type, std::string name);
        Symbol(bool isConstant, llvm::Type* type, llvm::Value* value);

    public:
        bool isConstant() const;
        llvm::Type* getType() const;
        std::string getName() const;
        llvm::Value* getValue() const;

    private:
        bool    isConstant_;
        llvm::Type*   type_;
        std::string   name_;
        llvm::Value* value_;
    };
}