#include "ret_stmt.h"
#include "builder/function/function.h"

namespace mcs {
    llvm::Value* RetStmt::codeGen() const {
        return (retVal_ == nullptr) ? createReturnInst() : createReturnInst(retVal_->codeGen());
    }
}