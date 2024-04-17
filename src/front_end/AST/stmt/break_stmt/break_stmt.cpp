#include "break_stmt.h"
#include "IR/context/context.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* BreakStmt::codeGen() const {
        const auto breakInst = createBreakInst();
        Context::getInstance().clearInsertionPoint();
        return breakInst;
    }
}