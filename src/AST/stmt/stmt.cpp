#include "stmt.h"
#include "IR/context/context.h"
#include "utils/utils.h"
#include "llvm/IR/Constants.h"

namespace mcs {
    llvm::Value* RetStmt::codeGen() {
        const auto returnValue = llvm::ConstantInt::get(getType("int"), retVal_, true);
        Context::getInstance().setCurrentReturnValue(returnValue);
        return returnValue;
    }

    bool RetStmt::checkAllMemberPtr() const {
        return true;
    }
}