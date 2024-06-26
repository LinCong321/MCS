#include "rel_exp.h"
#include "utils/logger.h"
#include "builder/operation/operation.h"

namespace mcs {
    llvm::Value* RelExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        const auto lhs = lhs_->codeGen();
        const auto rhs = rhs_->codeGen();
        return createBinaryOperation(lhs, *op_, rhs);
    }

    bool RelExp::checkAllMemberPointers() const {
        if (lhs_ == nullptr) {
            LOG_ERROR("lhs_ is nullptr.");
            return false;
        }
        if (op_ == nullptr) {
            LOG_ERROR("op_ is nullptr.");
            return false;
        }
        if (rhs_ == nullptr) {
            LOG_ERROR("rhs_ is nullptr.");
            return false;
        }
        return true;
    }
}