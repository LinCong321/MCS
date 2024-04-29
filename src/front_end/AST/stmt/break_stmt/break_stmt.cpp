#include "break_stmt.h"
#include "IR/context/context.h"
#include "builder/branch/branch.h"

namespace mcs {
    llvm::Value* BreakStmt::codeGen() const {
        const auto breakInst = createBreakInst();
        Context::getInstance().clearInsertionPoint();
        return breakInst;
    }
}