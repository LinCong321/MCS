#pragma once

#include "IR/type/type.h"
#include "llvm/IR/Constants.h"

namespace mcs {
    llvm::Type* getLLVMType(Type type);
    llvm::Type* getLLVMType(const std::string& str);

    llvm::PointerType* getPointerType(llvm::Type* type);

    llvm::Value* getCastedValue(llvm::Value* value, Type type);
    llvm::Value* getCastedValue(llvm::Value* value, const std::string& str);

    llvm::Constant* getConstantInt(int value);
    llvm::Constant* getConstantFloat(float value);
    llvm::Constant* getConstantValue(const llvm::Value* value, const std::string& str);
}