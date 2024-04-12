#include "arith_exp.h"
#include "utils/logger.h"
#include "builder/operation/operation.h"

namespace mcs {
    llvm::Value* ArithExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createArithmeticOperation(lhs_->codeGen(), op_, rhs_->codeGen());
    }

    bool ArithExp::checkAllMemberPointers() const {
        if (lhs_ == nullptr) {
            LOG_ERROR("lhs_ is nullptr.");
            return false;
        }
        if (rhs_ == nullptr) {
            LOG_ERROR("rhs_ is nullptr.");
            return false;
        }
        return true;
    }
}