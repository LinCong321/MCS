#include "block.h"

namespace mcs {
    llvm::Value* Block::codeGen() {
        return checkAllMemberPtr() ? stmt_->codeGen() : nullptr;
    }

    bool Block::checkAllMemberPtr() const {
        if (stmt_ == nullptr) {
            return false;
        }
        return true;
    }
}