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

        const auto trueBlock  = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto falseBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto condition  = getCastedValue(cond_->codeGen(), Type::BOOL);
        
        llvm::BranchInst::Create(trueBlock, falseBlock, condition, Context::getInstance().getInsertBlock());
        return createBranch(trueBlock, falseBlock);
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

    bool IfElseStmt::createBranchInst(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) {
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(mergeBlock, branchBlock);
            return true;
        }
        return false;
    }

    llvm::Value* IfElseStmt::createBranch(llvm::BasicBlock* trueBlock, llvm::BasicBlock* falseBlock) const {
        if (elseStmt_ != nullptr) {
            createBranchWithElse(trueBlock, falseBlock);
        } else {
            createBranchWithoutElse(trueBlock, falseBlock);
        }
        return nullptr;
    }

    bool IfElseStmt::createThenBranch(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().insertBlock(elseBlock);
        thenStmt_->codeGen();
        bool result = createBranchInst(elseBlock, mergeBlock);
        Context::getInstance().popBlock();
        return result;
    }

    bool IfElseStmt::createElseBranch(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().insertBlock(thenBlock);
        elseStmt_->codeGen();
        bool result = createBranchInst(thenBlock, mergeBlock);
        Context::getInstance().popBlock();
        return result;
    }

    void IfElseStmt::createBranchWithElse(llvm::BasicBlock* thenBlock, llvm::BasicBlock* elseBlock) const {
        const auto mergeBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto thenBranch = createThenBranch(thenBlock, mergeBlock);
        const auto elseBranch = createElseBranch(elseBlock, mergeBlock);
        if (thenBranch | elseBranch) {
            Context::getInstance().setInsertPoint(mergeBlock);
        } else {
            Context::getInstance().clearInsertionPoint();
        }
    }

    void IfElseStmt::createBranchWithoutElse(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const {
        createThenBranch(thenBlock, mergeBlock);
        Context::getInstance().setInsertPoint(mergeBlock);
    }
}