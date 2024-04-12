#include "rel_exp.h"

namespace mcs {
    llvm::Value *RelExp::codeGen() const {
        return nullptr;
    }

    bool RelExp::checkAllMemberPointers() const {
        return false;
    }
}