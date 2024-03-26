#include <unordered_map>

#include "exp.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace {
    std::unordered_map<char, llvm::Instruction::BinaryOps> char2Ops = {
        {'+',   llvm::Instruction::Add},
        {'-',   llvm::Instruction::Sub},
        {'*',   llvm::Instruction::Mul},
        {'/',   llvm::Instruction::SDiv},
        {'%',   llvm::Instruction::SRem},
    };
}

namespace mcs {
    llvm::Value* BinaryExp::codeGen() {
        const auto it = char2Ops.find(op_);
        if (it == char2Ops.end()) {
            LOG_ERROR("Cannot gen code because the given op (aka \'", op_ , "\') is not in the Ops list.");
            return nullptr;
        }
        return llvm::BinaryOperator::Create(it->second, lhs_->codeGen(), rhs_->codeGen(), "",
                                            Context::getInstance().getCurrentBlock());
    }
}