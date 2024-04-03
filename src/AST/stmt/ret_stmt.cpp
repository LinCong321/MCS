#include "ret_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace {
    bool checkReturned() {
        if (mcs::Context::getInstance().getCurrentReturnValue() != nullptr) {
            LOG_WARN("The function ", mcs::Context::getInstance().getCurrentFunctionName(),
                     "() has already returned, so this return statement is unreachable!");
            return true;
        }
        return false;
    }
}

namespace mcs {
    llvm::Value* RetStmt::codeGen() const {
        if (checkReturned() || !checkAllMemberPointers()) {
            return nullptr;
        }
        const auto returnValue = retVal_->codeGen();
        Context::getInstance().setCurrentReturnValue(returnValue);
        return returnValue;
    }

    bool RetStmt::checkAllMemberPointers() const {
        if (retVal_ == nullptr) {
            LOG_INFO("The function ", Context::getInstance().getCurrentFunctionName(), "() has no return value.");
            return false;
        }
        return true;
    }
}