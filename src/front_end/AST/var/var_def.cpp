#include "var_def.h"
#include "utils/logger.h"

namespace mcs {
    std::string VarDef::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get id because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    llvm::Value* VarDef::getValue() const {
        if (value_ == nullptr) {
            return nullptr;
        }
        return value_->codeGen();
    }
}