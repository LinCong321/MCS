#pragma once

#include "IR/type/type.h"
#include "llvm/IR/Function.h"

namespace mcs {
    using Params = std::vector<std::pair<llvm::Type*, std::string>>;

    llvm::Function* getFunction(Type retType, const std::string& name, const Params& params = {});
    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, const Params& params = {});

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name, const Params& params = {});
    llvm::Function* createFunction(const std::string& retType, const std::string& name, const Params& params = {});
}