#include <unordered_map>

#include "operator.h"
#include "utils/logger.h"

namespace {
    const std::unordered_map<std::string, mcs::Operator> str2Type = {
        {"+",   mcs::Operator::ARITHMETIC},
        {"-",   mcs::Operator::ARITHMETIC},
        {"*",   mcs::Operator::ARITHMETIC},
        {"/",   mcs::Operator::ARITHMETIC},
        {"%",   mcs::Operator::ARITHMETIC},
        {"||",  mcs::Operator::LOGICAL},
        {"&&",  mcs::Operator::LOGICAL},
        {"==",  mcs::Operator::RELATIONAL},
        {"!=",  mcs::Operator::RELATIONAL},
        {"<",   mcs::Operator::RELATIONAL},
        {">",   mcs::Operator::RELATIONAL},
        {"<=",  mcs::Operator::RELATIONAL},
        {">=",  mcs::Operator::RELATIONAL},
    };
}

namespace mcs {
    Operator strToOp(const std::string& str) {
        const auto it = str2Type.find(str);
        if (it == str2Type.end()) {
            LOG_ERROR("Unable to get type because the given str (aka \"", str, "\") is not in str2Type table.");
            return Operator::UNKNOWN;
        }
        return it->second;
    }

    std::ostream& operator<<(std::ostream& out, Operator type) {
        switch(type) {
            case Operator::ARITHMETIC:
                out << "arithmetic operator";
                return out;
            case Operator::LOGICAL:
                out << "logical operator";
                return out;
            case Operator::RELATIONAL:
                out << "relational operator";
                return out;
            default:
                out << "unknown operator";
                return out;
        }
    }
}