#pragma once

#include "func_param.h"

namespace mcs {
    class FuncParams {
    public:
        explicit FuncParams(FuncParam* funcParam);
        ~FuncParams() = default;

    public:
        void constFold() const;
        void pushBack(FuncParam* funcParam);
        bool readEach(const std::function<void(const FuncParam&)>& function) const;

    private:
        std::vector<std::unique_ptr<FuncParam>> funcParams_;
    };
}