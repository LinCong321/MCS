#include "func_call_exp.h"

#include "utils/logger.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* FuncCallExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createCallInst(*id_);
    }

    bool FuncCallExp::checkAllMemberPointers() const {
        if (id_ == nullptr) {
            LOG_ERROR("id_ is nullptr.");
            return false;
        }
        return true;
    }
}