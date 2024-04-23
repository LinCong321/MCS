#include "constant_table.h"
#include "utils/logger.h"

namespace mcs {
    ConstantTable &ConstantTable::getInstance() {
        static ConstantTable self;
        return self;
    }

    void ConstantTable::create() {
        tables_.emplace_back();
    }

    bool ConstantTable::remove() {
        if (tables_.empty()) {
            LOG_ERROR("Unable to remove constant table because tables is empty.");
            return false;
        }
        tables_.pop_back();
        return true;
    }

    Number* ConstantTable::get(const std::string& name) const {
        for (auto table = tables_.crbegin(); table != tables_.crend(); table++) {
            const auto it = table->find(name);
            if (it != table->end()) {
                return it->second.get();
            }
        }
        return nullptr;
    }

    bool ConstantTable::insert(const std::string& name, std::unique_ptr<Number> number) {
        if (tables_.empty()) {
            LOG_ERROR("Unable to insert constant because tables_ is empty.");
            return false;
        }
        tables_.back()[name] = std::move(number);
        return true;
    }
}