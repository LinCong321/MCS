#include "stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* Stmt::codeGen() {
        return nullptr;
    }

    llvm::Value* RetStmt::codeGen() {
        if (checkReturned() || !checkAllMemberPtr()) {
            return nullptr;
        }
        const auto returnValue = retVal_->codeGen();
        Context::getInstance().setCurrentReturnValue(returnValue);
        return returnValue;
    }

    bool RetStmt::checkReturned() {
        if (Context::getInstance().getCurrentReturnValue() != nullptr) {
            LOG_WARN("The function ", Context::getInstance().getCurrentFunctionName(),
                     "() has already returned, so this return statement is unreachable!");
            return true;
        }
        return false;
    }

    bool RetStmt::checkAllMemberPtr() const {
        if (retVal_ == nullptr) {
            LOG_INFO("The function ", Context::getInstance().getCurrentFunctionName(), "() has no return value.");
            return false;
        }
        return true;
    }
}