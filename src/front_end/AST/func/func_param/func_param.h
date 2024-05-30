#pragma once

#include "AST/node/node.h"

namespace mcs {
    class FuncParamArray {
    public:
        FuncParamArray() = default;
        ~FuncParamArray() = default;

    public:
        void constFold();
        void pushBack(Node* node);
        std::vector<int> getSize() const;

    private:
        std::vector<std::unique_ptr<Node>> size_;
    };

    class FuncParam {
    public:
        FuncParam(std::string* type, std::string* name, FuncParamArray* array = nullptr)
            : type_(type), name_(name), array_(array) {}
        ~FuncParam() = default;

    public:
        void constFold() const;
        std::string getType() const;
        std::string getName() const;
        std::optional<std::vector<int>> getArraySize() const;

    private:
        std::unique_ptr<std::string> type_;
        std::unique_ptr<std::string> name_;
        std::unique_ptr<FuncParamArray> array_;
    };
}