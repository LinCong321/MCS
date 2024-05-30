#include "parameter.h"

namespace mcs {
    const std::string& Parameter::getType() const {
        return type_;
    }

    const std::string& Parameter::getName() const {
        return name_;
    }

    const std::optional<std::vector<int>>& Parameter::getArraySize() const {
        return arraySize_;
    }
}