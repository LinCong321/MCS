#include "var_def_list.h"
#include "utils/logger.h"
#include "builder/variable/variable.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    VarDefList::VarDefList(VarDef* varDef) : isConstant_(false), type_(nullptr), defList_() {
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
            if (!declareVariable(isConstant_, *type_, def->getId(), def->getArraySize(), def->getValue())) {
                LOG_ERROR("Unable to generate code because variable \"", def->getId(), "\" cannot be declared.");
                return nullptr;
            }
        }

        return nullptr;
    }

    void VarDefList::constFold(std::unique_ptr<Node>& node) {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to fold constant because there is a nullptr in member pointers.");
            return;
        }
        for (auto& def : defList_) {
            if (def != nullptr) {
                constFold(*def);
            }
        }
    }

    void VarDefList::pushBack(VarDef* varDef) {
        defList_.emplace_back(varDef);
    }

    void VarDefList::setAttribute(std::string* type, bool isConstant) {
        type_ = std::unique_ptr<std::string>(type);
        isConstant_ = isConstant;
    }

    bool VarDefList::checkAllMemberPointers() const {
        if (type_ == nullptr) {
            LOG_ERROR("type_ is nullptr.");
            return false;
        }
        return true;
    }

    void VarDefList::constFold(VarDef& varDef) const {
        varDef.constFold();
        if (isConstant_) {
            ConstantTable::getInstance().insert(varDef.getId(), getNumber(varDef.getInitVal(), *type_));
        }
    }
}