#include "logic_exp.h"
#include "utils/logger.h"

namespace mcs {
    llvm::Value* LogicExp::codeGen() const {
        return nullptr;
    }

    bool LogicExp::checkAllMemberPointers() const {
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