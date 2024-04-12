#include "operation.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"

namespace {
    constexpr std::string_view emptyString;

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
    // ----------------------------------------create unary operation----------------------------------------

    llvm::Value* createPositiveOperation(llvm::Value* value) {
        return value;
    }

    llvm::Value* createNegativeOperation(llvm::Value* value) {
        switch (getTypeOf(value)) {
            case Type::INT:
                return createArithmeticOperation(getNullValue(value), '-', value);
            case Type::FLOAT:
                return llvm::UnaryOperator::Create(llvm::Instruction::FNeg, value, "",
                                                   Context::getInstance().getCurrentBlock());
            default:
                LOG_ERROR("Unable to create negative operation because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* createNotOperation(llvm::Value* value) {
        return llvm::BinaryOperator::CreateXor(getCastedValue(value, Type::BOOL), getBool(true), "",
                                               Context::getInstance().getCurrentBlock());
    }

    llvm::Value* createUnaryOperation(char op, llvm::Value* value) {
        static const std::unordered_map<char, std::function<llvm::Value*(llvm::Value*)>> char2Func = {
            {'+',   createPositiveOperation},
            {'-',   createNegativeOperation},
            {'!',   createNotOperation},
        };

        const auto it = char2Func.find(op);
        if (it == char2Func.end()) {
            LOG_ERROR("Unable to create unary operation because the given op (aka \'", op,
                      "\') is not in char2Func table.");
            return nullptr;
        }

        return it->second(value);
    }

    // ----------------------------------------create logical operation----------------------------------------

    llvm::Value* createOrOperation(llvm::Value* lhs, llvm::Value* rhs) {
        const auto function = Context::getInstance().getCurrentFunction();
        const auto orBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function);
        const auto mergeBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function);
        llvm::BranchInst::Create(mergeBlock, orBlock, getCastedValue(lhs, Type::BOOL),
                                 Context::getInstance().getCurrentBlock());
    }

    llvm::Value* createAndOperation(llvm::Value* lhs, llvm::Value* rhs) {

    }

    llvm::Value* createLogicalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        using Function = std::function<llvm::Value*(llvm::Value*, llvm::Value*)>;
        static const std::unordered_map<std::string, Function> str2Func = {
            {"||",  createOrOperation},
            {"&&",  createAndOperation},
        };

        const auto it = str2Func.find(op);
        if (it == str2Func.end()) {
            LOG_ERROR("Unable to create logical operation because the given op (aka \"", op,
                      "\") is not in str2Func table.");
            return nullptr;
        }

        return it->second(lhs, rhs);
    }

    // ----------------------------------------create arithmetic operation----------------------------------------

    llvm::Instruction::BinaryOps getOperator(char op, Type type) {
        static const std::unordered_map<Type, std::unordered_map<char, llvm::Instruction::BinaryOps>> type2Map = {
            {Type::INT,     char2SOp},
            {Type::FLOAT,   char2FOp},
        };

        const auto opMap = type2Map.find(type);
        if (opMap == type2Map.end()) {
            LOG_ERROR("Unable to create operation because the given type (aka ", type, ") is not in type2Map table.");
            return {};
        }

        const auto it = opMap->second.find(op);
        if (it == opMap->second.end()) {
            LOG_ERROR("Unable to create operation because operator \"", op, "\" does not apply to ", type, ".");
            return {};
        }

        return it->second;
    }

    llvm::Value* createArithmeticOperation(llvm::Value* lhs, char op, llvm::Value* rhs) {
        const auto targetType = std::max(getTypeOf(lhs), getTypeOf(rhs));

        return llvm::BinaryOperator::Create(getOperator(op, targetType),
                                            getCastedValue(lhs, targetType),
                                            getCastedValue(rhs, targetType),
                                            emptyString,
                                            Context::getInstance().getCurrentBlock());
    }

    // ----------------------------------------create relational operation----------------------------------------

    llvm::Value* createRelationalOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {

    }
}