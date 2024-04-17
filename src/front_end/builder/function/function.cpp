#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // --------------------------------------------get function--------------------------------------------

    llvm::Function* getFunction(Type retType, const std::string& name, Params params) {
        return getFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, Params params) {
        const auto funcType = llvm::FunctionType::get(retType, params, false);
        const auto linkage  = (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto function = llvm::Function::Create(funcType, linkage, name, Context::getInstance().getModule());
        Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function));
        return function;
    }

    // --------------------------------------------create function--------------------------------------------

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name, Params params) {
        if (Context::getInstance().findSymbol(name)) {
            LOG_ERROR("Cannot create function because its name (aka \"", name,
                      "\") already exists in the symbol table.");
            return nullptr;
        }

        const auto function = getFunction(retType, name, params);
        if (!Context::getInstance().insertSymbol(name, Symbol())) {
            LOG_ERROR("Cannot create function because it cannot be inserted to the symbol table.");
            return nullptr;
        }

        return function;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name, Params params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}