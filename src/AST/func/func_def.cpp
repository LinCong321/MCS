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
        const auto functionType = llvm::FunctionType::get(strToType(*retType_), llvm::ArrayRef(argTypes), false);

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
        if (retType_ == nullptr) {
            LOG_ERROR("retType_ is nullptr.");
            return false;
        }
        if (id_ == nullptr) {
            LOG_ERROR("id_ is nullptr.");
            return false;
        }
        if (block_ == nullptr) {
            LOG_ERROR("block_ is nullptr.");
            return false;
        }
        return true;
    }
}