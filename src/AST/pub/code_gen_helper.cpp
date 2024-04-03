#include "code_gen_helper.h"

#include "utils/logger.h"
#include "IR/context/context.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------string to type----------------------------------------

    llvm::Type* strToType(const std::string& type) {
        switch (getType(type)) {
            case Type::INT:
                return llvm::Type::getInt32Ty(Context::getInstance().getContext());
            case Type::FLOAT:
                return llvm::Type::getFloatTy(Context::getInstance().getContext());
            case Type::VOID:
                return llvm::Type::getVoidTy(Context::getInstance().getContext());
            default:
                LOG_ERROR("Unable to get casted type because there are not enough cases in switch.");
                return nullptr;
        }
    }

    // ----------------------------------------get casted value----------------------------------------

    llvm::Value* getIntValue(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, strToType("int"), "",
                                              Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Unable to get int value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getFloatValue(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, strToType("float"), "",
                                              Context::getInstance().getCurrentBlock());
            case Type::FLOAT:
                return value;
            default:
                LOG_ERROR("Unable to get float value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getCastedValue(llvm::Value* value, Type to) {
        static const std::unordered_map<Type, std::function<llvm::Value*(llvm::Value*)>> type2Func = {
            {Type::INT,     getIntValue},
            {Type::FLOAT,   getFloatValue},
        };

        const auto it = type2Func.find(to);
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get casted value because the target type (aka ", to, ") is not in the type list.");
            return nullptr;
        }

        return it->second(value);
    }

    // ----------------------------------------assign to variable----------------------------------------

    llvm::Value* assignToGlobalVariable(llvm::Value* variable, llvm::Value* value) {
        return nullptr;
    }

    llvm::Value* assignToLocalVariable(llvm::Value* variable, llvm::Value* value) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getCurrentBlock());
    }

    llvm::Value* assignToVariable(llvm::Value* variable, llvm::Value* value, Scope scope) {
        static const std::unordered_map<Scope, std::function<llvm::Value*(llvm::Value*, llvm::Value*)>> scope2Func = {
            {Scope::GLOBAL, assignToGlobalVariable},
            {Scope::LOCAL,  assignToLocalVariable},
        };

        const auto it = scope2Func.find(scope);
        if (it == scope2Func.end()) {
            LOG_ERROR("Unable to assign to variable because the scope (aka ", scope, ") is not in the scope list.");
            return nullptr;
        }

        return it->second(variable, value);
    }
}