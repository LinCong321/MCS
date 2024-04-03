#include "var_def_list.h"

#include "utils/logger.h"
#include "IR/context/context.h"
#include "pub/code_gen_helper.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    VarDefList::VarDefList(VarDef* varDef) {
        pushBack(varDef);
    }

    llvm::Value* VarDefList::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        for (const auto& def : defList_) {
            if (def == nullptr) {
                LOG_ERROR("Unable to generate code because there is a nullptr in defList_.");
                return nullptr;
            }

            const auto variable = declareVariable(def->getId());
            if (variable == nullptr) {
                LOG_ERROR("Unable to generate code because the variable cannot be declared.");
                return nullptr;
            }

            const auto result = assign(variable, def->getValue());
            if (result == nullptr) {
                LOG_ERROR("Unable to generate code because the variable cannot be assigned.");
                return nullptr;
            }
        }

        return nullptr;
    }

    void VarDefList::pushBack(VarDef* varDef) {
        defList_.emplace_back(varDef);
    }

    void VarDefList::setType(std::string* type) {
        type_ = std::unique_ptr<std::string>(type);
    }

    bool VarDefList::checkAllMemberPointers() const {
        if (type_ == nullptr) {
            LOG_ERROR("type_ is nullptr.");
            return false;
        }
        return true;
    }

    llvm::Value* VarDefList::declareVariable(const std::string& id) const {
        if (Context::getInstance().checkLocalSymbol(id)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id, "\") already exists in local symbol table.");
            return nullptr;
        }

        const auto variable = new llvm::AllocaInst(strToType(*type_), 0, id, Context::getInstance().getCurrentBlock());
        if (!mcs::Context::getInstance().insertLocalSymbol(id, variable)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id,
                      "\") cannot be inserted into local symbol table.");
            return nullptr;
        }

        return variable;
    }

    llvm::Value* VarDefList::assign(llvm::Value* variable, llvm::Value* value) const {
        return assignToVariable(variable, getCastedValue(value, getType(*type_)), Scope::LOCAL);
    }
}