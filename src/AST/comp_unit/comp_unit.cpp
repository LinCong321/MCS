#include "comp_unit.h"

namespace mcs {
    llvm::Value *CompUnit::codeGen() {
        return checkAllMemberPtr() ? funcDef_->codeGen() : nullptr;
    }

    bool CompUnit::checkAllMemberPtr() const {
        if (funcDef_ == nullptr) {
            return false;
        }
        return true;
    }
}