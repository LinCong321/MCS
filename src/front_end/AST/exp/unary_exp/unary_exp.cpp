#include "unary_exp.h"
#include "utils/logger.h"
#include "builder/operation/operation.h"

namespace mcs {
    llvm::Value* UnaryExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return getUnaryOperation(op_, val_->codeGen());
    }

    bool UnaryExp::checkAllMemberPointers() const {
        if (val_ == nullptr) {
            LOG_ERROR("val_ is nullptr.");
            return false;
        }
        return true;
    }
}