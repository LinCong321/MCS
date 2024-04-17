#include "continue_stmt.h"
#include "IR/context/context.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* ContinueStmt::codeGen() const {
        const auto continueInst = createContinueInst();
        Context::getInstance().clearInsertionPoint();
        return continueInst;
    }
}