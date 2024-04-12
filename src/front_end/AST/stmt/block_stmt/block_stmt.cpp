#include "block_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* BlockStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        Context::getInstance().pushBlock(Context::getInstance().getInsertBlock());
        block_->codeGen();
        Context::getInstance().popBlock();

        return nullptr;
    }

    bool BlockStmt::checkAllMemberPointers() const {
        if (block_ == nullptr) {
            LOG_ERROR("block_ is nullptr.");
            return false;
        }
        return true;
    }
}