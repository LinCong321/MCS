#include "var_def.h"
#include "utils/logger.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    std::string VarDef::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get ID because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    llvm::Value* VarDef::getValue() const {
        if (initVal_ == nullptr) {
            LOG_ERROR("Unable to get value because initVal_ is nullptr.");
            return nullptr;
        }

        const auto value = initVal_->getValue();
        if (value == nullptr) {
            LOG_ERROR("Unable to get value because initVal_->getValue() is nullptr.");
            return nullptr;
        }

        return value->codeGen();
    }

    void VarDef::constFold(const std::string& type) {
        if (initVal_ == nullptr) {
            LOG_ERROR("Unable to fold constant because initVal_ is nullptr.");
            return;
        }
        initVal_->constFold();
        ConstantTable::getInstance().insert(getId(), getNumber(initVal_->getValue(), type));
    }
}