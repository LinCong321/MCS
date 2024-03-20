#include "stmt.h"
#include "utils/logger.h"
#include "ast_utils/utils.h"
#include "llvm/IR/Constants.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* RetStmt::codeGen() {
        if (Context::getInstance().getCurrentReturnValue() != nullptr) {
            LOG_WARN("The function ", Context::getInstance().getCurrentFunctionName(),
                     "() has already returned, so this return statement is unreachable!");
            return nullptr;
        }
        const auto returnValue = llvm::ConstantInt::get(strToType("int"), retVal_, true);
        Context::getInstance().setCurrentReturnValue(returnValue);
        return returnValue;
    }
}