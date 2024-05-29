#include "func_param.h"
#include "utils/logger.h"
#include "number/number.h"

namespace mcs {
    void FuncParamArray::constFold() {
        for (auto& index : indices_) {
            if (index != nullptr) {
                index->constFold(index);
            }
        }
    }

    void FuncParamArray::pushBack(Node* node) {
        indices_.emplace_back(node);
    }

    std::vector<int> FuncParamArray::getIndices() const {
        std::vector<int> indices;
        for (const auto& index : indices_) {
            indices.emplace_back(getValueOfIntNum(index.get()));
        }
        return std::move(indices);
    }

    void FuncParam::constFold() const {
        if (array_ != nullptr) {
            array_->constFold();
        }
    }

    std::string FuncParam::getType() const {
        if (type_ == nullptr) {
            LOG_ERROR("Unable to get type because type_ is nullptr.");
            return {};
        }
        return *type_;
    }

    std::string FuncParam::getName() const {
        if (name_ == nullptr) {
            LOG_ERROR("Unable to get name because name_ is nullptr.");
            return {};
        }
        return *name_;
    }

    std::vector<int> FuncParam::getIndices() const {
        if (array_ == nullptr) {
            LOG_ERROR("Unable to get indices because array_ is nullptr.");
            return {};
        }
        return array_->getIndices();
    }
}