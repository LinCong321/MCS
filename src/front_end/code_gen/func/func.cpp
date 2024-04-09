#include "func.h"
#include "pub/pub.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ------------------------------------create function return value------------------------------------

    llvm::ReturnInst* getVoidReturnInst() {
        if (mcs::Context::getInstance().getCurrentReturnValue() != nullptr) {
            LOG_ERROR("Void function ", Context::getInstance().getCurrentFunctionName(),
                      "() should not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), Context::getInstance().getCurrentBlock());
    }

    llvm::ReturnInst* getNonVoidReturnInst(Type type) {
        const auto value = Context::getInstance().getCurrentReturnValue();
        if (value == nullptr) {
            LOG_ERROR("Non-void function ", Context::getInstance().getCurrentFunctionName(),
                      "() does not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), getCastedValue(value, type),
                                        Context::getInstance().getCurrentBlock());
    }

    llvm::ReturnInst* getReturnInst(mcs::Type type) {
        return (type == mcs::Type::VOID) ? getVoidReturnInst() : getNonVoidReturnInst(type);
    }

    bool createFunctionReturnValue(Type type) {
        bool result = true;
        if (getReturnInst(type) == nullptr) {
            LOG_ERROR("Unable to create function return value because the return instruction is nullptr.");
            result = false;
        }
        if (!Context::getInstance().popBlock()) {
            LOG_ERROR("Unable to create function return value because the code block cannot be popped out.");
            result = false;
        }
        return result;
    }

    bool createFunctionReturnValue(const std::string& str) {
        return createFunctionReturnValue(strToType(str));
    }

    // ----------------------------------------create function----------------------------------------

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        const auto functionType = llvm::FunctionType::get(retType, params, false);
        const auto linkage = (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto function = llvm::Function::Create(functionType, linkage, name, Context::getInstance().getModule());
        const auto basicBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(), "entry", function);
        Context::getInstance().pushBlock(basicBlock);
        return function;
    }

    llvm::Function* createFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}