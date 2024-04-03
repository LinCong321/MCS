#include "comp_unit.h"
#include "utils/logger.h"

namespace mcs {
    CompUnit::CompUnit(Node* node) : units_() {
        pushBack(node);
    }

    llvm::Value* CompUnit::codeGen() const {
        for (const auto& unit : units_) {
            if (unit == nullptr) {
                LOG_ERROR("Unable to generate code because there is a nullptr in units_.");
                break;
            }
            unit->codeGen();
        }
        return nullptr;
    }

    void CompUnit::pushBack(Node* node) {
        units_.emplace_back(node);
    }
}