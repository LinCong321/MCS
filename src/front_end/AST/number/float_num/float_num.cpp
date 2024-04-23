#include "float_num.h"
#include "utils/logger.h"
#include "number/int_num/int_num.h"
#include "builder/constant/constant.h"

namespace {
    template <typename TypeName>
    float toFloat(mcs::Node* node) {
        const auto number = dynamic_cast<TypeName>(node);
        if (number == nullptr) {
            LOG_ERROR("Cannot cast to float because number is nullptr");
            return 0;
        }
        return number->getValue();
    }
}

namespace mcs {
    Type FloatNum::getType() const {
        return Type::FLOAT;
    }

    llvm::Value* FloatNum::codeGen() const {
        return getConstantFloat(val_);
    }

    float FloatNum::getValue() const {
        return val_;
    }

    float FloatNum::getFloatVal(Node* node) {
        switch (getTypeOf(node)) {
            case Type::INT:
                return toFloat<IntNum*>(node);
            case Type::FLOAT:
                return toFloat<FloatNum*>(node);
            default:
                LOG_ERROR("Unable to get float val because there are not enough cases in switch.");
                return 0;
        }
    }

    float FloatNum::getInitVal(char op, Node* val) {
        switch (op) {
            case '+':
                return +getFloatVal(val);
            case '-':
                return -getFloatVal(val);
            case '!':
                return !static_cast<bool>(getFloatVal(val));
            default:
                LOG_ERROR("Unable to get init val because there are not enough cases in switch.");
                return 0;
        }
    }

    float FloatNum::getInitVal(Node* lhs, char op, Node* rhs) {
        switch (op) {
            case '+':
                return getFloatVal(lhs) + getFloatVal(rhs);
            case '-':
                return getFloatVal(lhs) - getFloatVal(rhs);
            case '*':
                return getFloatVal(lhs) * getFloatVal(rhs);
            case '/':
                return getFloatVal(lhs) / getFloatVal(rhs);
            default:
                LOG_ERROR("Unable to get init val because there are not enough cases in switch.");
                return 0;
        }
    }
}