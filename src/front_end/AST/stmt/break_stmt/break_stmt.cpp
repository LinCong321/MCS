#include "break_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    llvm::Value* BreakStmt::codeGen() const {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to generate code because getting loop information failed.");
            return nullptr;
        }
        return createBranchInst(loopInfo.getBreakBlock());
    }

    llvm::Value* BreakStmt::createBranchInst(llvm::BasicBlock* basicBlock) {
        llvm::BranchInst::Create(basicBlock, Context::getInstance().getInsertBlock());
        Context::getInstance().clearInsertionPoint();
        return nullptr;
    }
}