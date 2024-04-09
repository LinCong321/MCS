#include "func_def.h"
#include "function.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* FuncDef::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        std::vector<llvm::Type*> argTypes;
        const auto function = createFunction(*retType_, *id_, argTypes);

        Context::getInstance().setScope(Scope::LOCAL);
        block_->codeGen();
        Context::getInstance().setScope(Scope::GLOBAL);

        createFunctionReturnValue();
        return function;
    }

    bool FuncDef::checkAllMemberPointers() const {
        if (retType_ == nullptr) {
            LOG_ERROR("retType_ is nullptr.");
            return false;
        }
        if (id_ == nullptr) {
            LOG_ERROR("id_ is nullptr.");
            return false;
        }
        if (block_ == nullptr) {
            LOG_ERROR("block_ is nullptr.");
            return false;
        }
        return true;
    }
}