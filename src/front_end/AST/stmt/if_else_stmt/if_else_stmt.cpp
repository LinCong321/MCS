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

    llvm::Value* IfElseStmt::createBranch(llvm::BasicBlock* trueBlock, llvm::BasicBlock* falseBlock) const {
        if (elseStmt_ == nullptr) {
            createBranchWithoutElse(trueBlock, falseBlock);
        } else {
            createBranchWithElse(trueBlock, falseBlock);
        }
        return nullptr;
    }

    bool IfElseStmt::createThenBranch(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().setInsertPoint(thenBlock);
        thenStmt_->codeGen();
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(mergeBlock, thenBlock);
            return true;
        }
        return false;
    }

    bool IfElseStmt::createElseBranch(llvm::BasicBlock* elseBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().setInsertPoint(elseBlock);
        elseStmt_->codeGen();
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(mergeBlock, elseBlock);
            return true;
        }
        return false;
    }

    void IfElseStmt::createBranchWithElse(llvm::BasicBlock* thenBlock, llvm::BasicBlock* elseBlock) const {
        const auto mergeBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto thenBranch = createThenBranch(thenBlock, mergeBlock);
        const auto elseBranch = createElseBranch(elseBlock, mergeBlock);
        if (thenBranch || elseBranch) {
            Context::getInstance().setInsertPoint(mergeBlock);
        }
    }

    void IfElseStmt::createBranchWithoutElse(llvm::BasicBlock* thenBlock, llvm::BasicBlock* mergeBlock) const {
        createThenBranch(thenBlock, mergeBlock);
        Context::getInstance().setInsertPoint(mergeBlock);
    }
}