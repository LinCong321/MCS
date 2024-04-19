#pragma once

#include "IR/type/type.h"
#include "IR/symbol/symbol.h"

namespace mcs {
    bool createFunctionParams(llvm::Function* function, const std::vector<Symbol>& params);

    llvm::Function* getFunction(Type retType, const std::string& name, const std::vector<Symbol>& params = {});
    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, const std::vector<Symbol>& params = {});

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<Symbol>& params = {});
    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<Symbol>& params = {});
}