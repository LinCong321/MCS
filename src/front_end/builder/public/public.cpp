#include "public.h"
#include "utils/logger.h"
#include "constant/constant.h"
#include "IR/context/context.h"
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
                LOG_ERROR("Unable to get casted type because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Type* getLLVMType(const std::string& str) {
        return getLLVMType(getTypeOf(str));
    }

    // ----------------------------------------get pointer type----------------------------------------

    llvm::PointerType* getPointerType(llvm::Type* type) {
        return llvm::PointerType::get(type, 0);
    }

    // ----------------------------------------get casted value----------------------------------------

    llvm::Instruction* compareWithInt(llvm::Value* lhs, llvm::Value* rhs) {
        const auto block = Context::getInstance().getCurrentBlock();
        if (block == nullptr) {
            LOG_ERROR("Cannot be compared with int because block is nullptr.");
            return nullptr;
        }
        return new llvm::ICmpInst(*block, llvm::ICmpInst::ICMP_NE, lhs, rhs, "");
    }

    llvm::Instruction* compareWithFloat(llvm::Value* lhs, llvm::Value* rhs) {
        const auto block = Context::getInstance().getCurrentBlock();
        if (block == nullptr) {
            LOG_ERROR("Cannot be compared with float because block is nullptr.");
            return nullptr;
        }
        return new llvm::FCmpInst(*block, llvm::FCmpInst::FCMP_UNE, lhs, rhs, "");
    }

    llvm::Value* castToBool(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return value;
            case Type::INT:
                return compareWithInt(value, getInt32(0));
            case Type::FLOAT:
                return compareWithFloat(value, getFloat(0));
            default:
                LOG_ERROR("Cannot cast to bool because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToInt(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return llvm::CastInst::Create(llvm::CastInst::ZExt, value, getLLVMType(Type::INT), "",
                                              Context::getInstance().getCurrentBlock());
            case Type::INT:
                return value;
            case Type::FLOAT:
                return llvm::CastInst::Create(llvm::CastInst::FPToSI, value, getLLVMType(Type::INT), "",
                                              Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Cannot cast to int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* castToFloat(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::BOOL:
                return llvm::CastInst::Create(llvm::CastInst::UIToFP, value, getLLVMType(Type::FLOAT), "",
                                              Context::getInstance().getCurrentBlock());
            case Type::INT:
                return llvm::CastInst::Create(llvm::CastInst::SIToFP, value, getLLVMType(Type::FLOAT), "",
                                              Context::getInstance().getCurrentBlock());
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
            LOG_ERROR("Unable to get casted value because the target type (aka ", type,
                      ") is not in the type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    llvm::Value* getCastedValue(llvm::Value* value, llvm::Type* type) {
        return getCastedValue(value, getTypeOf(type));
    }
}