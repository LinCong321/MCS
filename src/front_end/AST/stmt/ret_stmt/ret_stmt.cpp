#include "ret_stmt.h"
#include "IR/context/context.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* RetStmt::codeGen() const {
        const auto returnInst = getReturnInst();
        Context::getInstance().clearInsertionPoint();
        return returnInst;
    }

    llvm::Instruction* RetStmt::getReturnInst() const {
        return (retVal_ == nullptr) ? createReturnInst() : createReturnInst(retVal_->codeGen());
    }

    void RetStmt::constFold(std::unique_ptr<Node>& node) {
        if (retVal_ != nullptr) {
            retVal_->constFold(retVal_);
        }
    }
}