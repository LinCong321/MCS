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
}