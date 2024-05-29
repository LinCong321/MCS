#include "public.h"
#include "utils/logger.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "operation/operation.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------get LLVM type----------------------------------------

    llvm::Type* getLLVMType(Type type) {
        switch (type) {
            case Type::VOID:
                return llvm::Type::getVoidTy(Context::getInstance().getContext());
            case Type::BOOL:
                return llvm::Type::getInt1Ty(Context::getInstance().getContext());
            case Type::INT:
                return llvm::Type::getInt32Ty(Context::getInstance().getContext());
            case Type::FLOAT:
                return llvm::Type::getFloatTy(Context::getInstance().getContext());
            default:
                LOG_ERROR("Unable to get LLVM type because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Type* getLLVMType(llvm::Type* type) {
        do {
            if (type == nullptr) {
                LOG_ERROR("Unable to get LLVM type because type is nullptr.");
                return nullptr;
            }
            if (!type->isArrayTy()) {
                return type;
            }
            type = type->getArrayElementType();
        } while(true);
    }

    llvm::Type* getLLVMType(const std::string& str) {
        return getLLVMType(getTypeOf(str));
    }

    llvm::Type* getLLVMType(const llvm::Value* value) {
        if (value == nullptr) {
            LOG_ERROR("Unable to get LLVM type because value is nullptr.");
            return nullptr;
        }
        return value->getType();
    }

    llvm::Type* getLLVMType(llvm::Type* type, const std::vector<int>& arraySize) {
        llvm::ArrayType* arrayType = nullptr;

        for (auto it = arraySize.crbegin(); it != arraySize.crend(); it++) {
            if (*it < 0) {
                LOG_ERROR("Unable to get LLVM type because array dimensions are negative integers!");
                return nullptr;
            }
            arrayType = llvm::ArrayType::get(type, *it);
            type = arrayType;
        }

        return arrayType != nullptr ? arrayType : type;
    }

    llvm::Type* getLLVMType(const std::string& str, const std::vector<int>& arraySize) {
        return getLLVMType(getLLVMType(str), arraySize);
    }

    // ----------------------------------------get casted value----------------------------------------

    llvm::Value* castToBool(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return value;
            case Type::INT:
                return createBinaryOperation(value, "!=", getConstantInt32(0));
            case Type::FLOAT:
                return createBinaryOperation(value, "!=", getConstantFloat(0));
            default:
                LOG_ERROR("Cannot cast to bool because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToInt(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return llvm::CastInst::Create(llvm::CastInst::ZExt, value, getLLVMType(Type::INT), "",
                                              Context::getInstance().getInsertBlock());
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, getLLVMType(Type::INT), "",
                                              Context::getInstance().getInsertBlock());
            default:
                LOG_ERROR("Cannot cast to int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToFloat(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return llvm::CastInst::Create(llvm::CastInst::UIToFP, value, getLLVMType(Type::FLOAT), "",
                                              Context::getInstance().getInsertBlock());
            case Type::INT:
                return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, getLLVMType(Type::FLOAT), "",
                                              Context::getInstance().getInsertBlock());
            case Type::FLOAT:
                return value;
            default:
                LOG_ERROR("Cannot cast to float because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getCastedValue(llvm::Value* value, Type type) {
        static const std::unordered_map<Type, std::function<llvm::Value*(llvm::Value*)>> type2Func = {
            {Type::BOOL,    castToBool},
            {Type::INT,     castToInt},
            {Type::FLOAT,   castToFloat},
        };

        if (value == nullptr) {
            LOG_ERROR("Unable to get casted value because value is nullptr.");
            return nullptr;
        }

        const auto it = type2Func.find(type);
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get casted value because the target type (aka ", type, ") is not in type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    llvm::Value* getCastedValue(llvm::Value* value, llvm::Type* type) {
        return getCastedValue(value, getTypeOf(type));
    }
}