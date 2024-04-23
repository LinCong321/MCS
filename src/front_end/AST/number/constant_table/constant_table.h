#pragma once

#include <list>
#include "AST/number/number.h"

namespace mcs {
    class ConstantTable {
    public:
        static ConstantTable& getInstance();

    public:
        void create();
        bool remove();
        Number* get(const std::string& name) const;
        bool insert(const std::string& name, std::unique_ptr<Number> number);

    private:
        ConstantTable() : tables_() {}
        ~ConstantTable() = default;

    private:
        std::list<std::unordered_map<std::string, std::unique_ptr<mcs::Number>>> tables_;
    };
}