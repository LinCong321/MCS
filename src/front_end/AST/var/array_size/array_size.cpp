#include "array_size.h"
#include "utils/logger.h"
#include "number/number.h"

namespace mcs {
    ArraySize::ArraySize(Node* node) {
        pushBack(node);
    }

    void ArraySize::constFold() {
        for (auto& size : arraySize_) {
            if (size != nullptr) {
                size->constFold(size);
            }
        }
    }

    void ArraySize::pushBack(Node* node) {
        arraySize_.emplace_back(node);
    }

    bool ArraySize::readEach(const std::function<void(Node&)>& function) const {
        for (const auto& size : arraySize_) {
            if (size == nullptr) {
                LOG_ERROR("Unable to read each because size is nullptr.");
                return false;
            }
            function(*size);
        }
        return true;
    }
}