#include "lval.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    llvm::Value* LVal::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        const auto symbol = Context::getInstance().getSymbol(*id_);
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getCurrentBlock());
    }

    bool LVal::checkAllMemberPointers() const {
        if (id_ == nullptr) {
            LOG_ERROR("id_ is nullptr.");
            return false;
        }
        return true;
    }
}