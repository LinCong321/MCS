#pragma once

#include "type.h"

namespace mcs {
    llvm::Type* getCastedType(const std::string& type);
    llvm::Value* getCastedValue(llvm::Value* value, Type to);
}