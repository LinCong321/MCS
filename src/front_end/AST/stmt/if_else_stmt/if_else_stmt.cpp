#include "if_else_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/public/public.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    llvm::Value* IfElseStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto function = Context::getInstance().getCurrentFunction();
        const auto thenBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto elseBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto mergeBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto currentBlock = Context::getInstance().getInsertBlock();
        llvm::BranchInst::Create(thenBB, elseBB, getCastedValue(cond_->codeGen(), Type::BOOL), currentBlock);

        function->insert(function->end(), thenBB);
        Context::getInstance().pushBlock(thenBB);
        thenStmt_->codeGen();
        Context::getInstance().popBlock();
        llvm::BranchInst::Create(mergeBB, thenBB);

        function->insert(function->end(), elseBB);
        Context::getInstance().pushBlock(elseBB);
        elseStmt_->codeGen();
        Context::getInstance().popBlock();
        llvm::BranchInst::Create(mergeBB, elseBB);

        function->insert(function->end(), mergeBB);
        Context::getInstance().setInsertPoint(mergeBB);
        return nullptr;
    }

    bool IfElseStmt::checkAllMemberPointers() const {
        if (cond_ == nullptr) {
            LOG_ERROR("cond_ is nullptr.");
            return false;
        }
        if (thenStmt_ == nullptr) {
            LOG_ERROR("thenStmt_ is nullptr.");
            return false;
        }
        if (elseStmt_ == nullptr) {
            LOG_ERROR("elseStmt_ is nullptr.");
            return false;
        }
        return true;
    }
}