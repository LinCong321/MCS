#include "unary_exp.h"
#include "utils/logger.h"

namespace mcs {
    llvm::Value *UnaryExp::codeGen() const {

    }

    bool UnaryExp::checkAllMemberPointers() const {
        if (val_ == nullptr) {
            LOG_ERROR("val_ is nullptr.");
            return false;
        }
        return true;
    }
}