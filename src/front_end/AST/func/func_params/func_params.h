#pragma once

#include <memory>
#include <functional>

namespace mcs {
    class FuncParam {
    public:
        FuncParam(std::string* type, std::string* name) : type_(type), name_(name) {}
        ~FuncParam() = default;

    public:
        std::string getType() const;
        std::string getName() const;

    private:
        std::unique_ptr<std::string> type_;
        std::unique_ptr<std::string> name_;
    };

    class FuncParams {
    public:
        explicit FuncParams(FuncParam* funcParam);
        ~FuncParams() = default;

    public:
        void pushBack(FuncParam* funcParam);
        bool readEach(const std::function<void(const FuncParam&)>& function) const;

    private:
        std::vector<std::unique_ptr<FuncParam>> funcParams_;
    };
}