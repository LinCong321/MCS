#include "lval.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* LVal::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return Context::getInstance().getVariable(*id_);
    }

    bool LVal::checkAllMemberPointers() const {
        if (id_ == nullptr) {
            LOG_ERROR("id_ is nullptr.");
            return false;
        }
        return true;
    }
}