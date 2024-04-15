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

        llvm::BranchInst::Create(loopInfo.getContinueBlock(), Context::getInstance().getInsertBlock());
        Context::getInstance().clearInsertionPoint();
        return nullptr;
    }
}