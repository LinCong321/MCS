#pragma once

#include "IR/type/type.h"

namespace mcs {
    llvm::Type* getLLVMType(Type type);
    llvm::Type* getLLVMType(llvm::Type* type);
    llvm::Type* getLLVMType(const std::string& str);
    llvm::Type* getLLVMType(const std::string& str, const std::vector<int>& arraySize);

    llvm::Type* getPointerType(llvm::Type* type);
    llvm::Type* getPointerType(const std::string& str, const std::vector<int>& arraySize);

    llvm::Value* getCastedValue(llvm::Value* value, Type type);
    llvm::Value* getCastedValue(llvm::Value* value, llvm::Type* type);
}