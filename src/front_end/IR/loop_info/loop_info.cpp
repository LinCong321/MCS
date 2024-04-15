#include "loop_info.h"

namespace mcs {
    llvm::BasicBlock* LoopInfo::getBreakBlock() const {
        return breakBlock_;
    }

    llvm::BasicBlock* LoopInfo::getContinueBlock() const {
        return continueBlock_;
    }
}