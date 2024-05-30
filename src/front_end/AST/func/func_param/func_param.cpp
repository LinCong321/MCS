#include "func_param.h"
#include "utils/logger.h"
#include "number/number.h"

namespace mcs {
    void FuncParamArray::constFold() {
        for (auto& size : size_) {
            if (size != nullptr) {
                size->constFold(size);
            }
        }
    }

    void FuncParamArray::pushBack(Node* node) {
        size_.emplace_back(node);
    }

    std::vector<int> FuncParamArray::getSize() const {
        std::vector<int> result;
        for (const auto& size : size_) {
            result.emplace_back(getValueOfIntNum(size.get()));
        }
        return std::move(result);
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

    std::optional<std::vector<int>> FuncParam::getArraySize() const {
        return array_ != nullptr ? std::optional<std::vector<int>>(array_->getSize()) : std::nullopt;
    }
}