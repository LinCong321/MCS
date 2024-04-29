#include "var_def_list.h"
#include "utils/logger.h"

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
                LOG_ERROR("Unable to declare variables because there is a nullptr in defList_.");
                return nullptr;
            }
            def->declare(isConstant_, *type_);
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
                def->constFold(isConstant_, *type_);
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
}