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

    const std::unordered_map<std::string, llvm::CmpInst::Predicate> str2IPred = {
        {"==",  llvm::CmpInst::ICMP_EQ},
        {"!=",  llvm::CmpInst::ICMP_NE},
        {"<",   llvm::CmpInst::ICMP_SLT},
        {">",   llvm::CmpInst::ICMP_SGT},
        {"<=",  llvm::CmpInst::ICMP_SLE},
        {">=",  llvm::CmpInst::ICMP_SGE},
    };

    const std::unordered_map<std::string, llvm::CmpInst::Predicate> str2FPred = {
        {"==",  llvm::CmpInst::FCMP_OEQ},
        {"!=",  llvm::CmpInst::FCMP_UNE},
        {"<",   llvm::CmpInst::FCMP_OLT},
        {">",   llvm::CmpInst::FCMP_OGT},
        {"<=",  llvm::CmpInst::FCMP_OLE},
        {">=",  llvm::CmpInst::FCMP_OGE},
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
                return createBinaryOperation(getNullValue(value), '-', value);
            case Type::FLOAT:
                return llvm::UnaryOperator::Create(llvm::Instruction::FNeg, value, emptyString,
                                                   Context::getInstance().getInsertBlock());
            default:
                LOG_ERROR("Unable to create negative operation because there are not enough cases in switch.");
                return nullptr;
        }
    }

    llvm::Value* createNotOperation(llvm::Value* value) {
        return llvm::BinaryOperator::CreateXor(getCastedValue(value, Type::BOOL), getConstantBool(true), emptyString,
                                               Context::getInstance().getInsertBlock());
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

    // ----------------------------------------create binary operation----------------------------------------

    llvm::Instruction::BinaryOps getBinaryOperator(char op, Type type) {
        static const std::unordered_map<Type, std::unordered_map<char, llvm::Instruction::BinaryOps>> type2Map = {
            {Type::INT,     char2SOp},
            {Type::FLOAT,   char2FOp},
        };

        const auto opMap = type2Map.find(type);
        if (opMap == type2Map.end()) {
            LOG_ERROR("Unable to get binary operator because the given type (aka ", type,
                      ") is not in type2Map table.");
            return {};
        }

        const auto it = opMap->second.find(op);
        if (it == opMap->second.end()) {
            LOG_ERROR("Unable to get binary operator because operator \"", op, "\" does not work with ", type, ".");
            return {};
        }

        return it->second;
    }

    llvm::Value* createICmpInst(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        const auto insertBlock = Context::getInstance().getInsertBlock();
        if (insertBlock == nullptr) {
            LOG_ERROR("Unable to create ICmp inst because insertBlock is nullptr.");
            return nullptr;
        }

        const auto it = str2IPred.find(op);
        if (it == str2IPred.end()) {
            LOG_ERROR("Unable to create ICmp inst because the given op (aka \"", op, "\") is not in str2IPred table.");
            return nullptr;
        }

        return new llvm::ICmpInst(*insertBlock, it->second, lhs, rhs);
    }

    llvm::Value* createFCmpInst(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        const auto insertBlock = Context::getInstance().getInsertBlock();
        if (insertBlock == nullptr) {
            LOG_ERROR("Unable to create FCmp inst because insertBlock is nullptr.");
            return nullptr;
        }

        const auto it = str2FPred.find(op);
        if (it == str2FPred.end()) {
            LOG_ERROR("Unable to create FCmp inst because the given op (aka \"", op, "\") is not in str2FPred table.");
            return nullptr;
        }

        return new llvm::FCmpInst(*insertBlock, it->second, lhs, rhs);
    }

    llvm::Value* createBinaryOperation(llvm::Value* lhs, char op, llvm::Value* rhs) {
        const auto targetType = std::max(std::max(getTypeOf(lhs), getTypeOf(rhs)), Type::INT);

        return llvm::BinaryOperator::Create(getBinaryOperator(op, targetType),
                                            getCastedValue(lhs, targetType),
                                            getCastedValue(rhs, targetType),
                                            emptyString,
                                            Context::getInstance().getInsertBlock());
    }

    llvm::Value* createBinaryOperation(llvm::Value* lhs, const std::string& op, llvm::Value* rhs) {
        using Function = std::function<llvm::Value*(llvm::Value*, const std::string&, llvm::Value*)>;
        static const std::unordered_map<Type, Function> type2Func = {
            {Type::INT,     createICmpInst},
            {Type::FLOAT,   createFCmpInst},
        };

        const auto targetType = std::max(std::max(getTypeOf(lhs), getTypeOf(rhs)), Type::INT);
        const auto it = type2Func.find(targetType);
        if (it == type2Func.end()) {
            LOG_ERROR("Unable to create binary operation because the target type (aka ", targetType,
                      ") is not in type2Func table.");
            return nullptr;
        }

        return it->second(getCastedValue(lhs, targetType), op, getCastedValue(rhs, targetType));
    }
}