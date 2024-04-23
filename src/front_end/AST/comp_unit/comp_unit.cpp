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

    void CompUnit::constFold(std::unique_ptr<Node>&) {
        for (auto& unit : units_) {
            if (unit == nullptr) {
                LOG_ERROR("Unable to fold constant because there is a nullptr in units_.");
                return;
            }
            unit->constFold(unit);
        }
    }

    void CompUnit::pushBack(Node* node) {
        units_.emplace_back(node);
    }
}