#include "symbol.h"

namespace mcs {
    llvm::Type* Symbol::getType() const {
        return type_;
    }

    llvm::Value* Symbol::getValue() const {
        return value_;
    }
}