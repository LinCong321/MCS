#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create function----------------------------------------

    llvm::Function* createFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        const auto funcType = llvm::FunctionType::get(retType, params, false);
        const auto linkage = (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto func = llvm::Function::Create(funcType, linkage, name, Context::getInstance().getModule());
        Context::getInstance().setInsertPoint(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", func));
        return func;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}