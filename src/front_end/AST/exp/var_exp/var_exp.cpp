#include "var_exp.h"
#include "utils/logger.h"
#include "number/number.h"
#include "builder/instruction/instruction.h"

namespace mcs {
    llvm::Value* VarExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createLoadInst(lvalue_->getId());
    }

    void VarExp::constFold(std::unique_ptr<Node>& node) {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to fold constant because there is a nullptr in member pointers.");
            return;
        }
        auto number = getNumber(lvalue_->getId());
        if (number != nullptr) {
            node = std::move(number);
        }
    }

    bool VarExp::checkAllMemberPointers() const {
        if (lvalue_ == nullptr) {
            LOG_ERROR("lvalue_ is nullptr.");
            return false;
        }
        return true;
    }
}