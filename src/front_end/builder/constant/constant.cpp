#include "constant.h"
#include "utils/logger.h"
#include "public/public.h"
#include "llvm/IR/Constants.h"

namespace mcs {
    // ----------------------------------------get basic type----------------------------------------

    llvm::Constant* getConstantInt32(int value) {
        return llvm::ConstantInt::get(getLLVMType(Type::INT), value, true);
    }

    llvm::Constant* getConstantBool(bool value) {
        return llvm::ConstantInt::get(getLLVMType(Type::BOOL), value);
    }

    llvm::Constant* getConstantFloat(float value) {
        return llvm::ConstantFP::get(getLLVMType(Type::FLOAT), value);
    }

    // ----------------------------------------get null value----------------------------------------

    llvm::Constant* getNullValue(llvm::Type* type) {
        return llvm::Constant::getNullValue(type);
    }

    llvm::Constant* getNullValue(const std::string& type) {
        return getNullValue(getLLVMType(type));
    }

    llvm::Constant* getNullValue(const llvm::Value* value) {
        if (value == nullptr) {
            LOG_ERROR("Unable to get null value because the source value is nullptr.");
            return nullptr;
        }
        return getNullValue(value->getType());
    }

    // ----------------------------------------get constant value----------------------------------------

    int getIntValue(const llvm::Constant* value) {
        const auto constantInt = llvm::dyn_cast<llvm::ConstantInt>(value);
        if (constantInt == nullptr) {
            LOG_ERROR("Unable to get int value because the source value is not a constant int.");
            return 0;
        }
        return static_cast<int>(constantInt->getValue().getSExtValue());
    }

    float getFloatValue(const llvm::Constant* value) {
        const auto constantFP = llvm::dyn_cast<llvm::ConstantFP>(value);
        if (constantFP == nullptr) {
            LOG_ERROR("Unable to get float value because the source value is not a constant float.");
            return 0;
        }
        return constantFP->getValue().convertToFloat();
    }

    llvm::Constant* castToConstantInt(const llvm::Constant* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getConstantInt32(getIntValue(value));
            case Type::FLOAT:
                return getConstantInt32(static_cast<int>(getFloatValue(value)));
            default:
                LOG_ERROR("Cannot cast to constant int because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* castToConstantFloat(const llvm::Constant* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getConstantFloat(static_cast<float>(getIntValue(value)));
            case Type::FLOAT:
                return getConstantFloat(getFloatValue(value));
            default:
                LOG_ERROR("Cannot cast to constant float because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Constant* getConstantValue(const llvm::Constant* value, llvm::Type* type) {
        static const std::unordered_map<Type, std::function<llvm::Constant*(const llvm::Constant*)>> type2Func = {
            {Type::INT,     castToConstantInt},
            {Type::FLOAT,   castToConstantFloat},
        };

        if (value == nullptr) {
            LOG_ERROR("Unable to get constant value because the source value is nullptr.");
            return nullptr;
        }

        const auto it = type2Func.find(getTypeOf(type));
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get constant value because the target type (aka ", getTypeOf(type),
                      ") is not in type2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    llvm::Constant* getConstantValue(const llvm::Value* value, llvm::Type* type) {
        if (llvm::isa<llvm::Constant>(value)) {
            return getConstantValue(llvm::dyn_cast<llvm::Constant>(value), type);
        }
        return nullptr;
    }

    // ----------------------------------------get constant array----------------------------------------

    llvm::Constant* getConstantArray(std::vector<llvm::Constant*> constants, llvm::Type* type) {
        if (type == nullptr) {
            LOG_ERROR("Unable to get constant array because type is nullptr.");
            return nullptr;
        }

        const auto size = type->getArrayNumElements();
        if (constants.size() > size) {
            LOG_ERROR("Unable to get constant array because number of constants = ", constants.size(),
                      " exceeds array size = ", size, ".");
            return nullptr;
        }

        const auto nullValue = getNullValue(type->getArrayElementType());
        while (constants.size() < size) {
            constants.emplace_back(nullValue);
        }

        for (const auto& constant : constants) {
            if (constant == nullptr) {
                LOG_ERROR("Unable to get constant array because there is a nullptr in constants.");
                return nullptr;
            }
        }

        return llvm::ConstantArray::get(llvm::dyn_cast<llvm::ArrayType>(type), constants);
    }
}