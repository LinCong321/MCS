#include "const_def.h"
#include "utils/logger.h"

namespace mcs {
    std::string ConstDef::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get id because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    llvm::Value* ConstDef::getValue() const {
        if (value_ == nullptr) {
            LOG_ERROR("Unable to get value because value_ is nullptr.");
            return nullptr;
        }
        return value_->codeGen();
    }
}