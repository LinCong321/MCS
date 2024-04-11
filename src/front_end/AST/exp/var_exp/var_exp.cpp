#include "var_exp.h"
#include "utils/logger.h"
#include "builder/memory/memory.h"

namespace mcs {
    llvm::Value* VarExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createLoadInst(lvalue_->getId());
    }

    bool VarExp::checkAllMemberPointers() const {
        if (lvalue_ == nullptr) {
            LOG_ERROR("lvalue_ is nullptr.");
            return false;
        }
        return true;
    }
}