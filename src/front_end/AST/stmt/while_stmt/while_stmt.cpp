#include "while_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"
#include "builder/public/public.h"

namespace mcs {
    llvm::Value* WhileStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto bodyBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto nextBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto condBlock = createCondBlock(bodyBlock, nextBlock);

        Context::getInstance().pushLoopInfo(LoopInfo(condBlock, nextBlock));
        createLoopBody(condBlock, bodyBlock);
        Context::getInstance().popLoopInfo();

        Context::getInstance().setInsertPoint(nextBlock);
        return nullptr;
    }

    bool WhileStmt::checkAllMemberPointers() const {
        if (cond_ == nullptr) {
            LOG_ERROR("cond_ is nullptr.");
            return false;
        }
        if (stmt_ == nullptr) {
            LOG_ERROR("stmt_ is nullptr.");
            return false;
        }
        return true;
    }

    llvm::BasicBlock* WhileStmt::getCondBlock() {
        const auto condBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        llvm::BranchInst::Create(condBlock, Context::getInstance().getInsertBlock());
        Context::getInstance().setInsertPoint(condBlock);
        return condBlock;
    }

    void WhileStmt::createLoopBody(llvm::BasicBlock* condBlock, llvm::BasicBlock* bodyBlock) const {
        Context::getInstance().insertBlock(bodyBlock);
        stmt_->codeGen();
        if (Context::getInstance().getInsertBlock() != nullptr) {
            llvm::BranchInst::Create(condBlock, Context::getInstance().getInsertBlock());
        }
        Context::getInstance().popBlock();
    }

    llvm::BasicBlock* WhileStmt::createCondBlock(llvm::BasicBlock* bodyBlock, llvm::BasicBlock* nextBlock) const {
        const auto condBlock = getCondBlock();
        const auto condition = getCastedValue(cond_->codeGen(), Type::BOOL);
        llvm::BranchInst::Create(bodyBlock, nextBlock, condition, Context::getInstance().getInsertBlock());
        return condBlock;
    }
}