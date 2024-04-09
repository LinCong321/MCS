#pragma once

#include "IR/type/type.h"
#include "llvm/IR/Function.h"

namespace mcs {
    bool createFunctionReturnValue();
    llvm::Function* createFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params = {});
    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params = {});
    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params = {});
}