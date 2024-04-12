#include "func_def.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/function/function.h"

namespace mcs {
    llvm::Value* FuncDef::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto function = createFunction(*retType_, *name_);
        block_->codeGen();
        Context::getInstance().deleteSymbolTable();

        return function;
    }

    bool FuncDef::checkAllMemberPointers() const {
        if (retType_ == nullptr) {
            LOG_ERROR("retType_ is nullptr.");
            return false;
        }
        if (name_ == nullptr) {
            LOG_ERROR("name_ is nullptr.");
            return false;
        }
        if (block_ == nullptr) {
            LOG_ERROR("block_ is nullptr.");
            return false;
        }
        return true;
    }
}