#include "continue_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    llvm::Value* ContinueStmt::codeGen() const {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to generate code because getting loop information failed.");
            return nullptr;
        }
        return createBranchInst(loopInfo.getContinueBlock());
    }

    llvm::Value* ContinueStmt::createBranchInst(llvm::BasicBlock*basicBlock) {
        llvm::BranchInst::Create(basicBlock, Context::getInstance().getInsertBlock());
        Context::getInstance().clearInsertionPoint();
        return nullptr;
    }
}