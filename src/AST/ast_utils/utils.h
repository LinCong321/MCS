#pragma once

#include "llvm/IR/Type.h"

namespace mcs {
    llvm::Type* strToType(const std::string& type);
}