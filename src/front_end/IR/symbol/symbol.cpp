#include "symbol.h"

namespace mcs {
    Symbol::Symbol(llvm::Type* type, std::string name)
        : isConstant_(false), type_(type), name_(std::move(name)), value_(nullptr) {
        // Do nothing.
    }

    Symbol::Symbol(bool isConstant, llvm::Type* type, llvm::Value* value)
        : isConstant_(isConstant), type_(type), name_(), value_(value) {
        // Do nothing.
    }

    bool Symbol::isConstant() const {
        return isConstant_;
    }

    llvm::Type* Symbol::getType() const {
        return type_;
    }

    std::string Symbol::getName() const {
        return name_;
    }

    llvm::Value* Symbol::getValue() const {
        return value_;
    }
}