#include "func_args_exp.h"
#include "utils/logger.h"

namespace mcs {
    FuncArgsExp::FuncArgsExp(Node* node) : funcArgs_() {
        pushBack(node);
    }

    void FuncArgsExp::pushBack(Node* node) {
        funcArgs_.emplace_back(node);
    }

    bool FuncArgsExp::readEach(const std::function<void(const Node&)>& function) {
        for (const auto& funcArg : funcArgs_) {
            if (funcArg == nullptr) {
                LOG_ERROR("Unable to read each because funcArg is nullptr.");
                return false;
            }
            function(*funcArg);
        }
        return true;
    }
}