#include "binary_exp.h"

#include "utils/logger.h"
#include "IR/context/context.h"
#include "pub/code_gen_helper.h"

#include "llvm/IR/InstrTypes.h"

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

    const std::unordered_map<mcs::Type, std::unordered_map<char, llvm::Instruction::BinaryOps>> type2Map = {
        {mcs::Type::INT,    char2SOp},
        {mcs::Type::FLOAT,  char2FOp},
    };
}

namespace mcs {
    llvm::Value* BinaryExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto lhs = lhs_->codeGen();
        const auto rhs = rhs_->codeGen();
        const auto targetType = getMaxType(lhs, rhs);

        return llvm::BinaryOperator::Create(getOperation(targetType),
                                            getCastedValue(lhs, targetType),
                                            getCastedValue(rhs, targetType),
                                            emptyString,
                                            Context::getInstance().getCurrentBlock());
    }

    bool BinaryExp::checkAllMemberPointers() const {
        if (lhs_ == nullptr) {
            LOG_ERROR("lhs_ is nullptr.");
            return false;
        }
        if (rhs_ == nullptr) {
            LOG_ERROR("rhs_ is nullptr.");
            return false;
        }
        return true;
    }

    llvm::Instruction::BinaryOps BinaryExp::getOperation(Type type) const {
        const auto opMap = type2Map.find(type);
        if (opMap == type2Map.end()) {
            LOG_ERROR("Unable to get operation because the given type (aka ", type, ") is not in the type2Map table.");
            return {};
        }

        const auto it = opMap->second.find(op_);
        if (it == opMap->second.end()) {
            LOG_ERROR("Unable to get operation because the given op (aka \'", op_, "\') is not in the opMap.");
            return {};
        }

        return it->second;
    }
}