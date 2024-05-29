#include "func_def.h"

#include "builder/public/public.h"
#include "builder/function/function.h"
#include "builder/constant/constant.h"
#include "builder/instruction/instruction.h"

#include "utils/logger.h"
#include "IR/context/context.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    llvm::Value* FuncDef::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto function = createFunction(*retType_, *name_, getParams());

        block_->codeGen();

        if (Context::getInstance().getInsertBlock() != nullptr) {
            appendRetStmt();
        }
        Context::getInstance().popBlock();

        return function;
    }

    void FuncDef::constFold(std::unique_ptr<Node>&) {
        ConstantTable::getInstance().create();

        if (funcParams_ != nullptr) {
            funcParams_->constFold();
        }
        if (block_ != nullptr) {
            block_->constFold(block_);
        }

        ConstantTable::getInstance().remove();
    }

    void FuncDef::appendRetStmt() const {
        if (*retType_ == "void") {
            createReturnInst();
            return;
        }
        LOG_WARN("Non-void function ", Context::getInstance().getCurrentFunctionName(), "() does not return a value.");
        createReturnInst(getNullValue(*retType_));
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

    std::vector<Symbol> FuncDef::getParams() const {
        std::vector<Symbol> params;

        if (funcParams_ != nullptr) {
            funcParams_->readEach([&params](const auto& funcParam) {
                params.emplace_back(getPointerType(funcParam.getType(), funcParam.getIndices()), funcParam.getName());
            });
        }

        return std::move(params);
    }
}