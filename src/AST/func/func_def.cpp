#include <iostream>
#include "func_def.h"
#include "utils/logger.h"
#include "ast_utils/utils.h"
#include "IR/context/context.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"


namespace mcs {
    llvm::Value* FuncDef::codeGen() {
        if (!checkAllMemberPtr()) {
            LOG_ERROR("There is a nullptr in member pointers.");
            return nullptr;
        }
        std::vector<llvm::Type*> argTypes;

        const auto functionType = llvm::FunctionType::get(getType(*funcType_), llvm::ArrayRef(argTypes), false);

        const auto linkage = (*id_ == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        const auto function = llvm::Function::Create(functionType, linkage, *id_, Context::getInstance().getModule());

        const auto basicBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(), "entry", function);
        Context::getInstance().pushBlock(basicBlock);

        block_->codeGen();

        llvm::ReturnInst::Create(Context::getInstance().getContext(),
                                 Context::getInstance().getCurrentReturnValue(),
                                 basicBlock);

        Context::getInstance().popBlock();

        return function;
    }

    bool FuncDef::checkAllMemberPtr() const {
        if (funcType_ == nullptr) {
            return false;
        }
        if (id_ == nullptr) {
            return false;
        }
        if (block_ == nullptr) {
            return false;
        }
        return true;
    }
}