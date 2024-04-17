#pragma once

#include "IR/type/type.h"
#include "llvm/IR/Function.h"

namespace mcs {
    using Params = const std::vector<llvm::Type*>&;

    llvm::Function* getFunction(Type retType, const std::string& name, Params params = {});
    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, Params params = {});

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name, Params params = {});
    llvm::Function* createFunction(const std::string& retType, const std::string& name, Params params = {});
}