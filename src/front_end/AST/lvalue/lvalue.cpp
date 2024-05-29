#include "lvalue.h"
#include "utils/logger.h"

namespace mcs {
    std::string LValue::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get ID because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    void LValue::pushBack(Node* node) {
        indices_.emplace_back(node);
    }

    std::vector<llvm::Value*> LValue::getIndices() const {
        std::vector<llvm::Value*> indices;

        for (const auto& index : indices_) {
            if (index == nullptr) {
                LOG_ERROR("Unable to get indices because index is nullptr.");
                return {};
            }
            indices.emplace_back(index->codeGen());
        }

        return std::move(indices);
    }
}