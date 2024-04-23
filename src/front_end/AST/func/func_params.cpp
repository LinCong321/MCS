#include "func_params.h"
#include "utils/logger.h"

namespace mcs {
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

    FuncParams::FuncParams(FuncParam* funcParam) : funcParams_() {
        pushBack(funcParam);
    }

    void FuncParams::pushBack(FuncParam* funcParam) {
        funcParams_.emplace_back(funcParam);
    }

    bool FuncParams::readEach(const std::function<void(const FuncParam&)>& function) const {
        for (const auto& funcParam: funcParams_) {
            if (funcParam == nullptr) {
                LOG_ERROR("Unable to read each because funcParam is nullptr.");
                return false;
            }
            function(*funcParam);
        }
        return true;
    }
}