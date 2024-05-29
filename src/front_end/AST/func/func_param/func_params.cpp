#include "func_params.h"
#include "utils/logger.h"

namespace mcs {
    FuncParams::FuncParams(FuncParam* funcParam) : funcParams_() {
        pushBack(funcParam);
    }

    void FuncParams::constFold() const {
        for (const auto& funcParam: funcParams_) {
            if (funcParam != nullptr) {
                funcParam->constFold();
            }
        }
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