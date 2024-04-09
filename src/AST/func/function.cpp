#include "function.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "pub/code_gen_helper.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    bool createFunctionReturnValue() {
        llvm::ReturnInst::Create(Context::getInstance().getContext(),
                                 Context::getInstance().getCurrentReturnValue(),
                                 Context::getInstance().getCurrentBlock());
        if (!Context::getInstance().popBlock()) {
            LOG_ERROR("Unable to create function return value because the code block cannot be popped out.");
            return false;
        }
        return true;
    }

    llvm::Function* createFunction(Type retType, const std::string& name, const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        const auto functionType = llvm::FunctionType::get(retType, params, false);
        const auto linkage = (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto function = llvm::Function::Create(functionType, linkage, name, Context::getInstance().getModule());
        const auto basicBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(), "entry", function);
        Context::getInstance().pushBlock(basicBlock);
        return function;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<llvm::Type*>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}