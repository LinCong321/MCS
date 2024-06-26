#include "assign_stmt.h"
#include "utils/logger.h"
#include "builder/memory/memory.h"

namespace mcs {
    llvm::Value* AssignStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createStoreInst(exp_->codeGen(), lvalue_->getId(), lvalue_->getIndices());
    }

    bool AssignStmt::checkAllMemberPointers() const {
        if (lvalue_ == nullptr) {
            LOG_ERROR("lvalue_ is nullptr.");
            return false;
        }
        if (exp_ == nullptr) {
            LOG_ERROR("exp_ is nullptr.");
            return false;
        }
        return true;
    }
}