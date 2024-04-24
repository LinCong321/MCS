#include "number.h"
#include "number/int_num/int_num.h"
#include "number/float_num/float_num.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    Type getTypeOf(Node* node) {
        const auto number = dynamic_cast<Number*>(node);
        return (number != nullptr) ? number->getType() : Type::UNKNOWN;
    }

    int getValueOfIntNum(Node* node) {
        const auto intNum = dynamic_cast<IntNum*>(node);
        return (intNum != nullptr) ? intNum->getValue() : -1;
    }

    std::unique_ptr<Number> getNumber(char op, Node* node) {
        switch (getTypeOf(node)) {
            case Type::INT:
                return std::make_unique<IntNum>(op, node);
            case Type::FLOAT:
                return std::make_unique<FloatNum>(op, node);
            default:
                return nullptr;
        }
    }

    std::unique_ptr<Number> getNumber(const std::string& name) {
        const auto number = ConstantTable::getInstance().get(name);
        if (number != nullptr) {
            return getNumber(number, number->getType());
        }
        return nullptr;
    }

    std::unique_ptr<Number> getNumber(Node* lhs, char op, Node* rhs) {
        switch (std::max(getTypeOf(lhs), getTypeOf(rhs))) {
            case Type::INT:
                return std::make_unique<IntNum>(lhs, op, rhs);
            case Type::FLOAT:
                return std::make_unique<FloatNum>(lhs, op, rhs);
            default:
                return nullptr;
        }
    }

    std::unique_ptr<Number> getNumber(Node* node, Type type) {
        switch (type) {
            case Type::INT:
                return std::make_unique<IntNum>(node);
            case Type::FLOAT:
                return std::make_unique<FloatNum>(node);
            default:
                return nullptr;
        }
    }

    std::unique_ptr<Number> getNumber(Node* node, const std::string& str) {
        return getNumber(node, getTypeOf(str));
    }
}