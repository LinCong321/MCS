#include "block.h"
#include "utils/logger.h"

namespace mcs {
    llvm::Value* Block::codeGen() {
        return checkAllMemberPtr() ? stmt_->codeGen() : nullptr;
    }

    bool Block::checkAllMemberPtr() const {
        if (stmt_ == nullptr) {
            LOG_ERROR("stmt_ is nullptr.");
            return false;
        }
        return true;
    }
}