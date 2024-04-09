#include "var_def_list.h"
#include "utils/logger.h"
#include "code_gen/var/var.h"

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
            if (!declareVariable(*type_, def->getId(), def->getValue())) {
                LOG_ERROR("Unable to generate code because the variable cannot be declared.");
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
}