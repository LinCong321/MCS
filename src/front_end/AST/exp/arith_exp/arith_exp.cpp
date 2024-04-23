#include "arith_exp.h"
#include "utils/logger.h"
#include "number/number.h"
#include "builder/operation/operation.h"

namespace mcs {
    llvm::Value* ArithExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        const auto lhs = lhs_->codeGen();
        const auto rhs = rhs_->codeGen();
        return createBinaryOperation(lhs, op_, rhs);
    }

    void ArithExp::constFold(std::unique_ptr<Node>& node) {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to fold constant because there is a nullptr in member pointers.");
            return;
        }

        lhs_->constFold(lhs_);
        rhs_->constFold(rhs_);

        auto number = getNumber(lhs_.get(), op_, rhs_.get());
        if (number != nullptr) {
            node = std::move(number);
        }
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