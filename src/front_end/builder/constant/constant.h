#pragma once

#include "llvm/IR/Constant.h"

namespace mcs {
    llvm::Constant* getInt32(int value);
    llvm::Constant* getBool(bool value);
    llvm::Constant* getFloat(float value);

    llvm::Constant* getNullValue(llvm::Type* type);
    llvm::Constant* getNullValue(const llvm::Value* value);
    llvm::Constant* getConstant(const llvm::Value* value, llvm::Type* type);
}