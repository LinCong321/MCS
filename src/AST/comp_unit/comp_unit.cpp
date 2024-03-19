#include "comp_unit.h"
#include "utils/logger.h"

namespace mcs {
    CompUnit::CompUnit(Node *node) : units_() {
        pushBack(node);
    }

    void CompUnit::pushBack(Node* node) {
        units_.push_back(std::unique_ptr<Node>(node));
    }

    llvm::Value* CompUnit::codeGen() {
        if (!checkAllMemberPtr()) {
            LOG_ERROR("There is a nullptr in member pointers.");
            return nullptr;
        }
        for (const auto& unit : units_) {
            if (unit == nullptr) {
                LOG_ERROR("There is a nullptr in units_.");
                break;
            }
            unit->codeGen();
        }
        return nullptr;
    }

    bool CompUnit::checkAllMemberPtr() const {
        return true;
    }
}