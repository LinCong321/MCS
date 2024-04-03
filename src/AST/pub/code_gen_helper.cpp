#include "code_gen_helper.h"

#include "utils/logger.h"
#include "IR/context/context.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------string to type----------------------------------------

    llvm::Type* getLLVMType(const std::string& str) {
        switch (getType(str)) {
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

    llvm::Value* castToInt(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, getLLVMType("int"), "",
                                              Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Unable to get int value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToFloat(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, getLLVMType("float"), "",
                                              Context::getInstance().getCurrentBlock());
            case Type::FLOAT:
                return value;
            default:
                LOG_ERROR("Unable to get float value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getCastedValue(llvm::Value* value, Type type) {
        static const std::unordered_map<Type, std::function<llvm::Value*(llvm::Value*)>> type2Func = {
            {Type::INT,     castToInt},
            {Type::FLOAT,   castToFloat},
        };

        const auto it = type2Func.find(type);
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get casted value because the target type (aka ", type,
                      ") is not in the type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    // ----------------------------------------get constant value----------------------------------------

    int64_t getIntValue(llvm::Value* value) {
        const auto constantInt = llvm::dyn_cast<llvm::ConstantInt>(value);
        if (constantInt == nullptr) {
            LOG_ERROR("Unable to get int value because constantInt is nullptr.");
            return 0;
        }
        return constantInt->getValue().getSExtValue();
    }

    float getFloatValue(llvm::Value* value) {
        const auto constantFP = llvm::dyn_cast<llvm::ConstantFP>(value);
        if (constantFP == nullptr) {
            LOG_ERROR("Unable to get float value because constantFp is nullptr.");
            return 0;
        }
        return constantFP->getValue().convertToFloat();
    }
    
    llvm::Constant* getConstantInt(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return llvm::dyn_cast<llvm::ConstantInt>(value);
            case Type::FLOAT:
                return llvm::ConstantInt::get(getLLVMType("int"), static_cast<int>(getFloatValue(value)), true);
            default:
                LOG_ERROR("Unable to get constant int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* getConstantFloat(llvm::Value* value) {
        switch (getTypeOfValue(value)) {
            case Type::INT:
                return llvm::ConstantFP::get(getLLVMType("float"), static_cast<float>(getIntValue(value)));
            case Type::FLOAT:
                return llvm::dyn_cast<llvm::ConstantFP>(value);
            default:
                LOG_ERROR("Unable to get constant int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* getConstantValue(llvm::Value* value, const std::string& str) {
        static const std::unordered_map<Type, std::function<llvm::Constant*(llvm::Value*)>> type2Func = {
            {Type::INT,     getConstantInt},
            {Type::FLOAT,   getConstantFloat},
        };

        const auto it = type2Func.find(getType(str));
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get constant value because the target type (aka \"", str,
                      "\") is not in the type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }
}