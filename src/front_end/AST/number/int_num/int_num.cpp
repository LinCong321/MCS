#include "int_num.h"
#include "utils/logger.h"
#include "builder/constant/constant.h"
#include "number/float_num/float_num.h"

namespace {
    template <typename TypeName>
    int toInt(mcs::Node* node) {
        const auto number = dynamic_cast<TypeName>(node);
        if (number == nullptr) {
            LOG_ERROR("Cannot cast to int because number is nullptr");
            return 0;
        }
        return number->getValue();
    }
}

namespace mcs {
    Type IntNum::getType() const {
        return Type::INT;
    }

    llvm::Value* IntNum::codeGen() const {
        return getConstantInt32(val_);
    }

    int IntNum::getValue() const {
        return val_;
    }

    int IntNum::getIntVal(Node* node) {
        switch (getTypeOf(node)) {
            case Type::INT:
                return toInt<IntNum*>(node);
            case Type::FLOAT:
                return toInt<FloatNum*>(node);
            default:
                LOG_ERROR("Unable to get int val because there are not enough cases in switch.");
                return 0;
        }
    }

    int IntNum::getIntVal(char op, Node* node) {
        switch (op) {
            case '+':
                return +getIntVal(node);
            case '-':
                return -getIntVal(node);
            case '!':
                return !getIntVal(node);
            default:
                LOG_ERROR("Unable to get int val because there are not enough cases in switch.");
                return 0;
        }
    }

    int IntNum::getIntVal(Node* lhs, char op, Node* rhs) {
        switch (op) {
            case '+':
                return getIntVal(lhs) + getIntVal(rhs);
            case '-':
                return getIntVal(lhs) - getIntVal(rhs);
            case '*':
                return getIntVal(lhs) * getIntVal(rhs);
            case '/':
                return getIntVal(lhs) / getIntVal(rhs);
            case '%':
                return getIntVal(lhs) % getIntVal(rhs);
            default:
                LOG_ERROR("Unable to get int val because there are not enough cases in switch.");
                return 0;
        }
    }
}