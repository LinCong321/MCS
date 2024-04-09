#include "const_def_list.h"
#include "utils/logger.h"

namespace mcs {
    ConstDefList::ConstDefList(ConstDef* constDef) {
        pushBack(constDef);
    }

    llvm::Value *ConstDefList::codeGen() const {
        return nullptr;
    }

    void ConstDefList::setType(std::string* type) {
        type_ = std::unique_ptr<std::string>(type);
    }

    void ConstDefList::pushBack(ConstDef* constDef) {
        defList_.emplace_back(constDef);
    }

    bool ConstDefList::checkAllMemberPointers() const {
        if (type_ == nullptr) {
            LOG_ERROR("type_ is nullptr.");
            return false;
        }
        return true;
    }
}