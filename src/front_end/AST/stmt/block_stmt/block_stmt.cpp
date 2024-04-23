#include "block_stmt.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    llvm::Value* BlockStmt::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        Context::getInstance().createSymbolTable();
        block_->codeGen();
        Context::getInstance().deleteSymbolTable();

        return nullptr;
    }

    void BlockStmt::constFold(std::unique_ptr<Node>&) {
        ConstantTable::getInstance().create();
        if (block_ != nullptr) {
            block_->constFold(block_);
        }
        ConstantTable::getInstance().remove();
    }

    bool BlockStmt::checkAllMemberPointers() const {
        if (block_ == nullptr) {
            LOG_ERROR("block_ is nullptr.");
            return false;
        }
        return true;
    }
}