#pragma once

#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace mcs {
    class Parameter {
    public:
        explicit Parameter(const std::string& type = "", const std::string& name = "",
                           const std::optional<std::vector<int>>& arraySize = {})
            : type_(type), name_(name), arraySize_(arraySize) {}
        ~Parameter() = default;

    public:
        const std::string& getType() const;
        const std::string& getName() const;
        const std::optional<std::vector<int>>& getArraySize() const;

    private:
        const std::string                       type_;
        const std::string                       name_;
        const std::optional<std::vector<int>>   arraySize_;
    };
}