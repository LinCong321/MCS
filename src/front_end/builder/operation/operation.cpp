#include "operation.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "llvm/IR/InstrTypes.h"

namespace {
    const std::unordered_map<char, llvm::Instruction::BinaryOps> char2SOp = {
        {'+',   llvm::Instruction::Add},
        {'-',   llvm::Instruction::Sub},
        {'*',   llvm::Instruction::Mul},
        {'/',   llvm::Instruction::SDiv},
        {'%',   llvm::Instruction::SRem},
    };

    const std::unordered_map<char, llvm::Instruction::BinaryOps> char2FOp = {
        {'+',   llvm::Instruction::FAdd},
        {'-',   llvm::Instruction::FSub},
        {'*',   llvm::Instruction::FMul},
        {'/',   llvm::Instruction::FDiv},
    };
}

namespace mcs {
    // ----------------------------------------get unary operation----------------------------------------

    llvm::Value* getPositiveOperation(llvm::Value* value) {
        return value;
    }

    llvm::Value* getNegativeOperation(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return getBinaryOperation(getNullValue(value), '-', value);
            case Type::FLOAT:
                return llvm::UnaryOperator::Create(llvm::Instruction::FNeg, value, "",
                                                   Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Unable to get negative operation because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* getNotOperation(llvm::Value* value) {
        return llvm::BinaryOperator::CreateXor(getCastedValue(value, Type::BOOL), getBool(true), "",
                                               Context::getInstance().getCurrentBlock());
    }

    llvm::Value* getUnaryOperation(char op, llvm::Value* value) {
        static const std::unordered_map<char, std::function<llvm::Value*(llvm::Value*)>> char2Func = {
            {'+',   getPositiveOperation},
            {'-',   getNegativeOperation},
            {'!',   getNotOperation},
        };

        const auto it = char2Func.find(op);
        if (it == char2Func.end()) {
            LOG_ERROR("Unable to get unary operation because the given op (aka \'", op,
                      "\') is not in the char2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    // ----------------------------------------get binary operation----------------------------------------

    llvm::Instruction::BinaryOps getBinaryOperator(char op, Type type) {
        static const std::unordered_map<Type, std::unordered_map<char, llvm::Instruction::BinaryOps>> type2Map = {
            {Type::INT,     char2SOp},
            {Type::FLOAT,   char2FOp},
        };

        const auto opMap = type2Map.find(type);
        if (opMap == type2Map.end()) {
            LOG_ERROR("Unable to get operation because the given type (aka ", type, ") is not in the type2Map table.");
            return {};
        }

        const auto it = opMap->second.find(op);
        if (it == opMap->second.end()) {
            LOG_ERROR("Unable to get operation because binary operator \'", op, "\' does not work with ", type, ".");
            return {};
        }

        return it->second;
    }

    llvm::Value* getBinaryOperation(llvm::Value* lhs, char op, llvm::Value* rhs) {
        const auto targetType = std::max(getTypeOf(lhs), getTypeOf(rhs));

        return llvm::BinaryOperator::Create(getBinaryOperator(op, targetType),
                                            getCastedValue(lhs, targetType),
                                            getCastedValue(rhs, targetType),
                                            "",
                                            Context::getInstance().getCurrentBlock());
    }
}