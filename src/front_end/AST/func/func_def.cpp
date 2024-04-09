#include "func_def.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "code_gen/func/func.h"

namespace mcs {
    llvm::Value* FuncDef::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        std::vector<llvm::Type*> params;
        const auto function = createFunction(*retType_, *id_, params);

        Context::getInstance().setCurrentScope(Scope::LOCAL);
        block_->codeGen();
        Context::getInstance().setCurrentScope(Scope::GLOBAL);

        if (!createFunctionReturnValue(*retType_)) {
            LOG_ERROR("Unable to generate code because the function return value cannot be created.");
            return nullptr;
        }

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