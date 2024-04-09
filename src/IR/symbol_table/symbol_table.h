#pragma once

#include "symbol/symbol.h"

namespace mcs {
    class SymbolTable {
    public:
        SymbolTable() = default;
        ~SymbolTable() = default;

    public:
        bool checkExist(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;
        void insertSymbol(const std::string& name, const Symbol& symbol);

    private:
        std::unordered_map<std::string, Symbol> name2Symbol_;
    };
}