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
        return createBranchInst();
    }

    bool IfElseStmt::checkAllMemberPointers() const {
        if (cond_ == nullptr) {
            LOG_ERROR("condition_ is nullptr.");
            return false;
        }
        if (thenStmt_ == nullptr) {
            LOG_ERROR("thenStmt_ is nullptr.");
            return false;
        }
        return true;
    }

    llvm::Value* IfElseStmt::createBranchInst() const {
        if (elseStmt_ == nullptr) {
            createBranchInstWithoutElse();
        } else {
            createBranchInstWithElse();
        }
        return nullptr;
    }

    void IfElseStmt::createBranchInstWithElse() const {
        const auto [thenBlock, elseBlock] = getBlockPair(cond_->codeGen());
        const auto mergeBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());

        bool needMergeBlock = false;
        needMergeBlock |= createThenBranch(thenBlock, mergeBlock);
        needMergeBlock |= createElseBranch(elseBlock, mergeBlock);

        if (needMergeBlock) {
            Context::getInstance().setInsertPoint(mergeBlock);
        } else {
            Context::getInstance().clearInsertionPoint();
        }
    }

    void IfElseStmt::createBranchInstWithoutElse() const {
        const auto [thenBlock, mergeBlock] = getBlockPair(cond_->codeGen());
        createThenBranch(thenBlock, mergeBlock);
        Context::getInstance().setInsertPoint(mergeBlock);
    }


    bool IfElseStmt::createElseBranch(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().insertBlock(thenBlock);
        elseStmt_->codeGen();
        bool result = false;
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(mergeBlock, thenBlock);
            result = true;
        }
        Context::getInstance().popBlock();
        return result;
    }

    bool IfElseStmt::createThenBranch(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().insertBlock(elseBlock);
        thenStmt_->codeGen();
        bool result = false;
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(mergeBlock, elseBlock);
            result = true;
        }
        Context::getInstance().popBlock();
        return result;
    }

    std::pair<llvm::BasicBlock*, llvm::BasicBlock*> IfElseStmt::getBlockPair(llvm::Value* condition) {
        const auto trueBlock  = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto falseBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        llvm::BranchInst::Create(trueBlock, falseBlock, getCastedValue(condition, Type::BOOL),
                                 Context::getInstance().getInsertBlock());
        return std::make_pair(trueBlock, falseBlock);
    }
}