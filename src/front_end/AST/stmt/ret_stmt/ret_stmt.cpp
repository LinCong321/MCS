#include "ret_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* RetStmt::codeGen() const {
        if (Context::getInstance().getInsertBlock() == nullptr) {
            LOG_WARN("The function ", mcs::Context::getInstance().getCurrentFunctionName(),
                     "() has already returned, so this return statement is unreachable!");
            return nullptr;
        }
        const auto returnInst = (retVal_ == nullptr) ? createReturnInst() : createReturnInst(retVal_->codeGen());
        Context::getInstance().clearInsertionPoint();
        return returnInst;
    }
}