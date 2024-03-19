#include <unordered_map>
#include "utils/logger.h"
#include "ast_utils/utils.h"
#include "IR/context/context.h"

namespace {
    enum class TypeList : uint {
        INT = 1,
        FLOAT = 2,
        VOID = 3,
    };

    std::unordered_map<std::string, TypeList> str2Type = {
            {"int",     TypeList::INT},
            {"float",   TypeList::FLOAT},
            {"void",    TypeList::VOID},
    };
}

namespace mcs {
    llvm::Type* getType(const std::string& type) {
        const auto it = str2Type.find(type);
        if (it == str2Type.end()) {
            LOG_ERROR("Cannot get LLVM type because the given type (aka ", type, ") is not in the type list.");
            return nullptr;
        }
        switch (it->second) {
            case TypeList::INT:
                return llvm::Type::getInt32Ty(Context::getInstance().getContext());
            case TypeList::FLOAT:
                return llvm::Type::getDoubleTy(Context::getInstance().getContext());
            case TypeList::VOID:
                return llvm::Type::getVoidTy(Context::getInstance().getContext());
            default:
                LOG_ERROR("Cannot get LLVM type because there are not enough cases in switch.");
                return nullptr;
        }
    }
}