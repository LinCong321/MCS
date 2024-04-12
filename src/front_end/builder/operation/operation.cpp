#include "operation.h"

#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "IR/operator/operator.h"

#include "llvm/IR/InstrTypes.h"

namespace {
    constexpr std::string_view emptyString;

    const std::unordered_map<std::string, llvm::Instruction::BinaryOps> str2SOp = {
        {"+",   llvm::Instruction::Add},
        {"-",   llvm::Instruction::Sub},
        {"*",   llvm::Instruction::Mul},
        {"/",   llvm::Instruction::SDiv},
        {"%",   llvm::Instruction::SRem},
    };

    const std::unordered_map<std::string, llvm::Instruction::BinaryOps> str2FOp = {
        {"+",   llvm::Instruction::FAdd},
        {"-",   llvm::Instruction::FSub},
        {"*",   llvm::Instruction::FMul},
        {"/",   llvm::Instruction::FDiv},
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
                return getArithmeticOperation(getNullValue(value), "-", value);
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
                      "\') is not in char2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    // ----------------------------------------get binary operation----------------------------------------

    llvm::Value* getBinaryOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        using Function = std::function<llvm::Value*(llvm::Value*, const std::string&, llvm::Value*)>;
        static const std::unordered_map<Operator, Function> type2Func = {
            {Operator::ARITHMETIC,    getArithmeticOperation},
            {Operator::LOGICAL,       getLogicalOperation},
            {Operator::RELATIONAL,    getRelationalOperation},
        };

        const auto it = type2Func.find(strToOp(op));
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to get binary operator because ", strToOp(op), " is not in type2Func table.");
            return nullptr;
        }

        return it->second(lhs, op, rhs);
    }

    // ----------------------------------------get arithmetic operation----------------------------------------

    llvm::Instruction::BinaryOps getArithmeticOperator(const std::string& op, Type type) {
        using Map = std::unordered_map<std::string, llvm::Instruction::BinaryOps>;
        static const std::unordered_map<Type, Map> type2Map = {
            {Type::INT,     str2SOp},
            {Type::FLOAT,   str2FOp},
        };

        const auto opMap = type2Map.find(type);
        if (opMap == type2Map.end()) {
            LOG_ERROR("Unable to get operation because the given type (aka ", type, ") is not in type2Map table.");
            return {};
        }

        const auto it = opMap->second.find(op);
        if (it == opMap->second.end()) {
            LOG_ERROR("Unable to get operation because operator \"", op, "\" does not apply to ", type, ".");
            return {};
        }

        return it->second;
    }

    llvm::Value* getArithmeticOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        const auto targetType = std::max(getTypeOf(lhs), getTypeOf(rhs));

        return llvm::BinaryOperator::Create(getArithmeticOperator(op, targetType),
                                            getCastedValue(lhs, targetType),
                                            getCastedValue(rhs, targetType),
                                            emptyString,
                                            Context::getInstance().getCurrentBlock());
    }

    // ----------------------------------------get logical operation----------------------------------------

    llvm::Value* getLogicalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {

    }

    // ----------------------------------------get relational operation----------------------------------------

    llvm::Value* getRelationalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {

    }
}