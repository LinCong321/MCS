#pragma once

#include "llvm/IR/Type.h"

namespace mcs {
    llvm::Type* getType(const std::string& type);
}