#pragma once

#include "IR/type/type.h"
#include "llvm/IR/Function.h"

namespace mcs {
    llvm::Value* createReturnInst(llvm::Value* value = nullptr);

    llvm::Function* getFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params = {});
    llvm::Function* getFunction(llvm::Type* retType, const std::string& name,
                                const std::vector<llvm::Type*>& params = {});

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params = {});
    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params = {});
}