#include "symbol_table.h"
#include "utils/logger.h"

namespace mcs {
    bool SymbolTable::checkExist(const std::string& name) const {
        return name2Symbol_.find(name) != name2Symbol_.end();
    }

    Symbol SymbolTable::getSymbol(const std::string& name) const {
        const auto it = name2Symbol_.find(name);
        if (it == name2Symbol_.end()) {
            LOG_ERROR("Unable to get symbol because its name (aka ", name, ") is not in the symbol table.");
            return {};
        }
        return it->second;
    }

    void SymbolTable::insertSymbol(const std::string& name, const Symbol& symbol) {
        name2Symbol_[name] = symbol;
    }
}