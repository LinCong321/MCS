#pragma once

#include "llvm/IR/Constant.h"

namespace mcs {
    llvm::Constant* getConstantInt32(int value);
    llvm::Constant* getConstantBool(bool value);
    llvm::Constant* getConstantFloat(float value);

    llvm::Constant* getNullValue(llvm::Type* type);
    llvm::Constant* getNullValue(const llvm::Value* value);

    llvm::Constant* getConstantValue(const llvm::Value* value, llvm::Type* type);
}