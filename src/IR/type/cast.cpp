#include "cast.h"

#include "utils/logger.h"
#include "llvm/IR/Type.h"
#include "context/context.h"
#include "llvm/IR/InstrTypes.h"

namespace mcs {
    llvm::Type* getCastedType(const std::string& type) {
        switch (strToType(type)) {
            case Type::INT:
                return llvm::Type::getInt32Ty(Context::getInstance().getContext());
            case Type::FLOAT:
                return llvm::Type::getFloatTy(Context::getInstance().getContext());
            case Type::VOID:
                return llvm::Type::getVoidTy(Context::getInstance().getContext());
            default:
                LOG_ERROR("Cannot get casted type because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getIntValue(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, getCastedType("int"), "");
            default:
                LOG_ERROR("Cannot get int value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getFloatValue(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return value;
                //return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, getCastedType("float"), "");
            case Type::FLOAT:
                return value;
            default:
                LOG_ERROR("Cannot get float value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getCastedValue(llvm::Value* value, Type to) {
        switch (to) {
            case Type::INT:
                return getIntValue(value);
            case Type::FLOAT:
                return getFloatValue(value);
            default:
                LOG_ERROR("Cannot get casted value because there are not enough cases in switch.");
                return nullptr;
        }
    }
}