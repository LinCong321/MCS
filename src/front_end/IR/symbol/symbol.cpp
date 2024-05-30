#include "symbol.h"

namespace mcs {
    bool Symbol::isConstant() const {
        return isConstant_;
    }

    llvm::Type* Symbol::getType() const {
        return type_;
    }

    llvm::Value* Symbol::getValue() const {
        return value_;
    }

    llvm::Type* Symbol::getPointerElementType() const {
        return pointerElementType_;
    }
}