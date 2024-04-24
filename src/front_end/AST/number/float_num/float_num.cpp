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

    float FloatNum::getFloatVal(char op, Node* node) {
        switch (op) {
            case '+':
                return +getFloatVal(node);
            case '-':
                return -getFloatVal(node);
            case '!':
                return !static_cast<bool>(getFloatVal(node));
            default:
                LOG_ERROR("Unable to get float val because there are not enough cases in switch.");
                return 0;
        }
    }

    float FloatNum::getFloatVal(Node* lhs, char op, Node* rhs) {
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
                LOG_ERROR("Unable to get float val because there are not enough cases in switch.");
                return 0;
        }
    }
}