#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace {
    constexpr std::string_view MAIN = "main";
    constexpr std::string_view INIT_GLOBAL_VAR = "initGlobalVar";
}

namespace mcs {
    // ----------------------------------------create function----------------------------------------

    llvm::Function* createFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        const auto funcType = llvm::FunctionType::get(retType, params, false);
        const auto linkage = (name == MAIN) ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto func = llvm::Function::Create(funcType, linkage, name, Context::getInstance().getModule());

        if (name == INIT_GLOBAL_VAR) {
            Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", func));
            Context::getInstance().insertSymbol(name, Symbol(funcType, func));
        } else {
            Context::getInstance().insertSymbol(name, Symbol(funcType, func));
            Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", func));
        }

        return func;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}