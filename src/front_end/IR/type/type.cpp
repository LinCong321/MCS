#include "type.h"
#include "utils/logger.h"

namespace {
    const std::unordered_map<std::string, mcs::Type> str2Type = {
        {"void",    mcs::Type::VOID},
        {"bool",    mcs::Type::BOOL},
        {"int",     mcs::Type::INT},
        {"float",   mcs::Type::FLOAT},
    };

    const std::unordered_map<llvm::Type::TypeID, mcs::Type> id2Type = {
        {llvm::Type::TypeID::IntegerTyID,   mcs::Type::INT},
        {llvm::Type::TypeID::FloatTyID,     mcs::Type::FLOAT},
        {llvm::Type::TypeID::VoidTyID,      mcs::Type::VOID},
    };
}

namespace mcs {
    Type getTypeOf(const std::string& str) {
        const auto it = str2Type.find(str);
        if (it == str2Type.end()) {
            LOG_ERROR("Cannot cast str to type because the given str (aka \"", str, "\") is not in str2Type table.");
            return Type::UNKNOWN;
        }
        return it->second;
    }

    Type getTypeOf(const llvm::Type* type) {
        if (type == nullptr) {
            LOG_ERROR("Unable to get type because LLVM type is nullptr.");
            return Type::UNKNOWN;
        }
        if (type->isIntegerTy(1)) {
            return Type::BOOL;
        }
        return getTypeOf(type->getTypeID());
    }

    Type getTypeOf(const llvm::Value* value) {
        if (value == nullptr) {
            LOG_ERROR("Unable to get type of value because value is nullptr.");
            return Type::UNKNOWN;
        }
        return getTypeOf(value->getType());
    }

    Type getTypeOf(llvm::Type::TypeID typeId) {
        const auto it = id2Type.find(typeId);
        if (it == id2Type.end()) {
            LOG_ERROR("Unable to get type because LLVM type id: ", typeId, " is not in id2Type table.");
            return Type::UNKNOWN;
        }
        return it->second;
    }

    std::ostream& operator<<(std::ostream& out, Type type) {
        switch (type) {
            case Type::VOID:
                out << "Type::VOID";
                return out;
            case Type::BOOL:
                out << "Type::BOOL";
                return out;
            case Type::INT:
                out << "Type::INT";
                return out;
            case Type::FLOAT:
                out << "Type::FLOAT";
                return out;
            default:
                out << "Type::UNKNOWN";
                return out;
        }
    }
}