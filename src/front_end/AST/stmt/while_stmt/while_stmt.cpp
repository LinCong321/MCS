#include "while_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/instruction/instruction.h"

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

    void WhileStmt::createLoopBody(llvm::BasicBlock* condBlock, llvm::BasicBlock* bodyBlock) const {
        Context::getInstance().setInsertPoint(bodyBlock);
        stmt_->codeGen();
        createJumpInst(condBlock);
    }

    llvm::BasicBlock* WhileStmt::createCondBlock(llvm::BasicBlock* bodyBlock, llvm::BasicBlock* nextBlock) const {
        const auto condBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        createJumpInst(condBlock);
        Context::getInstance().setInsertPoint(condBlock);
        createBranchInst(bodyBlock, nextBlock, cond_->codeGen());
        return condBlock;
    }
}