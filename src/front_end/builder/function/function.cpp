#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create return inst----------------------------------------

    llvm::ReturnInst* createVoidReturnInst(llvm::Value* value) {
        if (value != nullptr) {
            LOG_ERROR("Void function ", Context::getInstance().getCurrentFunctionName(),
                      "() should not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), Context::getInstance().getInsertBlock());
    }

    llvm::ReturnInst* createNonVoidReturnInst(llvm::Value* value, llvm::Type* type) {
        if (value == nullptr) {
            LOG_WARN("Non-void function ", Context::getInstance().getCurrentFunctionName(),
                     "() does not return a value.");
            value = getNullValue(type);
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), getCastedValue(value, type),
                                        Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createReturnInst(llvm::Value* value) {
        const auto type = Context::getInstance().getReturnTypeOfCurrentFunction();
        if (type == nullptr) {
            LOG_ERROR("Unable to create return inst because type is nullptr.");
            return nullptr;
        }
        return type->isVoidTy() ? createVoidReturnInst(value) : createNonVoidReturnInst(value, type);
    }

    // --------------------------------------------get function--------------------------------------------

    llvm::Function* getFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        return getFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        const auto funcType = llvm::FunctionType::get(retType, params, false);
        const auto linkage = (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        return llvm::Function::Create(funcType, linkage, name, Context::getInstance().getModule());
    }

    // --------------------------------------------create function--------------------------------------------

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        if (Context::getInstance().findSymbol(name)) {
            LOG_ERROR("Cannot create function because its name (aka \"", name,
                      "\") has already exists in the symbol table.");
            return nullptr;
        }

        const auto function = getFunction(retType, name, params);
        Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function));
        if (!Context::getInstance().insertSymbol(name, Symbol(function))) {
            LOG_ERROR("Cannot create function because it cannot be inserted to the symbol table.");
            return nullptr;
        }

        return function;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}