#include "constant.h"
#include "utils/logger.h"
#include "public/public.h"
#include "llvm/IR/Constants.h"

namespace mcs {
    // --------------------------------------------get basic type--------------------------------------------

    llvm::Constant* getInt32(int value) {
        return llvm::ConstantInt::get(getLLVMType(Type::INT), value, true);
    }

    llvm::Constant* getBool(bool value) {
        return llvm::ConstantInt::get(getLLVMType(Type::BOOL), value);
    }

    llvm::Constant* getFloat(float value) {
        return llvm::ConstantFP::get(getLLVMType(Type::FLOAT), value);
    }

    // --------------------------------------------get null value--------------------------------------------

    llvm::Constant* getNullValue(llvm::Type* type) {
        return llvm::Constant::getNullValue(type);
    }

    llvm::Constant* getNullValue(const llvm::Value* value) {
        if (value == nullptr) {
            LOG_ERROR("Unable to get null value because the source value is nullptr.");
            return nullptr;
        }
        return getNullValue(value->getType());
    }

    // --------------------------------------------get constant--------------------------------------------

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
                return getInt32(getIntValue(value));
            case Type::FLOAT:
                return getInt32(static_cast<int>(getFloatValue(value)));
            default:
                LOG_ERROR("Cannot cast to constant int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* castToConstantFloat(const llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getFloat(static_cast<float>(getIntValue(value)));
            case Type::FLOAT:
                return getFloat(getFloatValue(value));
            default:
                LOG_ERROR("Cannot cast to constant float because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* getConstantValue(const llvm::Value* value, llvm::Type* type) {
        static const std::unordered_map<Type, std::function<llvm::Constant*(const llvm::Value*)>> type2Func = {
            {Type::INT,     castToConstantInt},
            {Type::FLOAT,   castToConstantFloat},
        };

        if (value == nullptr || !llvm::isa<llvm::Constant>(value)) {
            LOG_INFO("Returns a null value because the source value is nullptr or is not a constant.");
            return getNullValue(type);
        }

        const auto it = type2Func.find(getTypeOf(type));
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get constant value because the target type (aka ", getTypeOf(type),
                      ") is not in type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }
}