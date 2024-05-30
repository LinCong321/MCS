#pragma once

#include "IR/type/type.h"
#include "IR/parameter/parameter.h"

namespace mcs {
    bool createFunctionParams(llvm::Function* function, const std::vector<Parameter>& params);

    llvm::Function* getFunction(Type retType, const std::string& name, const std::vector<Parameter>& params = {});
    llvm::Function* getFunction(llvm::Type* retType, const std::string& name,
                                const std::vector<Parameter>& params = {});

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<Parameter>& params = {});
}