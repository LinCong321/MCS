#include "public.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------get LLVM type----------------------------------------

    llvm::Type* getLLVMType(Type type) {
        switch (type) {
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

    llvm::Type* getLLVMType(const std::string& str) {
        return getLLVMType(strToType(str));
    }

    // ----------------------------------------get pointer type----------------------------------------

    llvm::PointerType* getPointerType(llvm::Type* type) {
        return llvm::PointerType::get(type, 0);
    }

    // ----------------------------------------get casted value----------------------------------------

    llvm::Value* castToInt(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, getLLVMType(Type::INT), "",
                                              Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Unable to get int value because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToFloat(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, getLLVMType(Type::FLOAT), "",
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

        if (value == nullptr) {
            LOG_ERROR("Unable to get casted value because value is nullptr.");
            return nullptr;
        }

        const auto it = type2Func.find(type);
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get casted value because the target type (aka ", type,
                      ") is not in the type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    llvm::Value* getCastedValue(llvm::Value* value, llvm::Type* type) {
        return getCastedValue(value, getTypeOf(type));
    }

    // ----------------------------------------get constant int----------------------------------------

    llvm::Constant* getConstantInt(int value) {
        return llvm::ConstantInt::get(getLLVMType(Type::INT), value, true);
    }

    // ----------------------------------------get constant float----------------------------------------

    llvm::Constant* getConstantFloat(float value) {
        return llvm::ConstantFP::get(getLLVMType(Type::FLOAT), value);
    }

    // ----------------------------------------get constant value----------------------------------------

    int getIntValue(const llvm::Value* value) {
        const auto constantInt = llvm::dyn_cast<llvm::ConstantInt>(value);
        if (constantInt == nullptr) {
            LOG_ERROR("Unable to get int value because the source value is not a constant int.");
            return 0;
        }
        return static_cast<int>(constantInt->getValue().getSExtValue());
    }

    float getFloatValue(const llvm::Value* value) {
        const auto constantFP = llvm::dyn_cast<llvm::ConstantFP>(value);
        if (constantFP == nullptr) {
            LOG_ERROR("Unable to get float value because the source value is not a constant float.");
            return 0;
        }
        return constantFP->getValue().convertToFloat();
    }
    
    llvm::Constant* castToConstantInt(const llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getConstantInt(getIntValue(value));
            case Type::FLOAT:
                return getConstantInt(static_cast<int>(getFloatValue(value)));
            default:
                LOG_ERROR("Unable to get constant int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* castToConstantFloat(const llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getConstantFloat(static_cast<float>(getIntValue(value)));
            case Type::FLOAT:
                return getConstantFloat(getFloatValue(value));
            default:
                LOG_ERROR("Unable to get constant float because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* getConstantValue(const llvm::Value* value, llvm::Type* type) {
        static const std::unordered_map<Type, std::function<llvm::Constant*(const llvm::Value*)>> type2Func = {
            {Type::INT,     castToConstantInt},
            {Type::FLOAT,   castToConstantFloat},
        };

        if (value == nullptr || !llvm::isa<llvm::Constant>(value)) {
            LOG_INFO("Return a null value from LLVM because the source value is nullptr or not a constant.");
            return llvm::Constant::getNullValue(type);
        }

        const auto it = type2Func.find(getTypeOf(type));
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get constant value because the target type (aka ", getTypeOf(type),
                      ") is not in the type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }
}