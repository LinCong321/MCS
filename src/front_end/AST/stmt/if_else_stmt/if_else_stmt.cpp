#include "if_else_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"
#include "builder/public/public.h"

namespace mcs {
    llvm::Value* IfElseStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto thenBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto elseBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto mergeBB = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto cond = getCastedValue(cond_->codeGen(), Type::BOOL);
        llvm::BranchInst::Create(thenBB, elseBB, cond, Context::getInstance().getInsertBlock());

        Context::getInstance().insertBlock(thenBB);
        thenStmt_->codeGen();
        Context::getInstance().popBlock();
        llvm::BranchInst::Create(mergeBB, thenBB);

        Context::getInstance().insertBlock(elseBB);
        elseStmt_->codeGen();
        Context::getInstance().popBlock();
        llvm::BranchInst::Create(mergeBB, elseBB);

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