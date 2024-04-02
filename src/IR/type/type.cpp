#include "type.h"
#include "utils/logger.h"
#include "llvm/IR/Type.h"

namespace {
    std::unordered_map<std::string, mcs::Type> str2Type = {
        {"int",     mcs::Type::INT},
        {"float",   mcs::Type::FLOAT},
        {"void",    mcs::Type::VOID},
    };

    std::unordered_map<llvm::Type::TypeID, mcs::Type> id2Type = {
        {llvm::Type::TypeID::IntegerTyID,   mcs::Type::INT},
        {llvm::Type::TypeID::FloatTyID,     mcs::Type::FLOAT},
        {llvm::Type::TypeID::VoidTyID,      mcs::Type::VOID},
    };
}

namespace mcs {
    Type strToType(const std::string& str) {
        const auto it = str2Type.find(str);
        if (it == str2Type.end()) {
            LOG_ERROR("Cannot cast str to type because the given str (aka ", str, ") is not in the type list.");
            return Type::UNKNOWN;
        }
        return it->second;
    }

    Type getTypeOfValue(const llvm::Value* value) {
        if (value == nullptr) {
            LOG_ERROR("Cannot get type of value because value is nullptr.");
            return Type::UNKNOWN;
        }

        const auto type = value->getType();
        if (type == nullptr) {
            LOG_ERROR("Cannot get type of value because value->getType() is nullptr.");
            return Type::UNKNOWN;
        }

        const auto it = id2Type.find(type->getTypeID());
        if (it == id2Type.end()) {
            LOG_ERROR("Cannot get type of value because the type id: ", type->getTypeID(), " is not in the id list.");
            return Type::UNKNOWN;
        }

        return it->second;
    }

    std::ostream& operator<<(std::ostream& out, Type type) {
        switch (type) {
            case Type::INT:
                out << "Type::INT";
            case Type::FLOAT:
                out << "Type::FLOAT";
            case Type::VOID:
                out << "Type::VOID";
            default:
                out << "Type::UNKNOWN";
        }
        return out;
    }
}