#include "comp_unit.h"
#include "utils/logger.h"

namespace mcs {
    CompUnit::CompUnit(Node* node) : units_() {
        pushBack(node);
    }

    llvm::Value* CompUnit::codeGen() {
        for (const auto& unit : units_) {
            if (unit == nullptr) {
                LOG_ERROR("There is a nullptr in units_.");
                break;
            }
            unit->codeGen();
        }
        return nullptr;
    }

    void CompUnit::pushBack(Node* node) {
        units_.push_back(std::unique_ptr<Node>(node));
    }
}