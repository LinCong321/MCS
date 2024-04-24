#include "var_def.h"
#include "utils/logger.h"
#include "number/number.h"

namespace mcs {
    void VarDef::constFold() {
        if (arraySize_ != nullptr) {
            arraySize_->constFold();
        }
        if (initVal_ != nullptr) {
            initVal_->constFold();
        }
    }

    Node* VarDef::getInitVal() const {
        return initVal_ != nullptr ? initVal_->getValue() : nullptr;
    }

    std::string VarDef::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get ID because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    llvm::Value* VarDef::getValue() const {
        if (initVal_ == nullptr) {
            return nullptr;
        }

        const auto value = initVal_->getValue();
        if (value == nullptr) {
            LOG_ERROR("Unable to get value because initVal_->getValue() is nullptr.");
            return nullptr;
        }

        return value->codeGen();
    }

    std::vector<int> VarDef::getArraySize() const {
        std::vector<int> size;

        if (arraySize_ != nullptr) {
            arraySize_->readEach([&size](Node& node) {
                size.emplace_back(getValueOfIntNum(&node));
            });
        }

        return std::move(size);
    }
}