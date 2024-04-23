#include "unary_exp.h"
#include "utils/logger.h"
#include "number/number.h"
#include "builder/operation/operation.h"

namespace mcs {
    llvm::Value* UnaryExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createUnaryOperation(op_, val_->codeGen());
    }

    void UnaryExp::constFold(std::unique_ptr<Node>& node) {
        if (val_ != nullptr) {
            val_->constFold(val_);
        }
        auto number = getNumber(op_, val_.get());
        if (number != nullptr) {
            node = std::move(number);
        }
    }

    bool UnaryExp::checkAllMemberPointers() const {
        if (val_ == nullptr) {
            LOG_ERROR("val_ is nullptr.");
            return false;
        }
        return true;
    }
}