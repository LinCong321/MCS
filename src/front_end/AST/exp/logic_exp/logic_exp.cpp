#include "logic_exp.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/public/public.h"
#include "builder/branch/branch.h"
#include "builder/constant/constant.h"

namespace mcs {
    llvm::Value* LogicExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto branchBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto mergeBlock  = llvm::BasicBlock::Create(Context::getInstance().getContext());

        std::vector<PhiNode> nodes;
        nodes.emplace_back(getLhsNode(branchBlock, mergeBlock));
        nodes.emplace_back(getRhsNode(branchBlock, mergeBlock));

        Context::getInstance().setInsertPoint(mergeBlock);
        return createPHINode(nodes);
    }

    bool LogicExp::checkAllMemberPointers() const {
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

    LogicExp::PhiNode LogicExp::getLhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const {
        switch (op_) {
            case '|':
                createBranchInst(mergeBlock, branchBlock, lhs_->codeGen());
                return std::make_pair(getConstantBool(true), Context::getInstance().getInsertBlock());
            case '&':
                createBranchInst(branchBlock, mergeBlock, lhs_->codeGen());
                return std::make_pair(getConstantBool(false), Context::getInstance().getInsertBlock());
            default:
                LOG_ERROR("Unable to get lhs node because there are not enough cases in switch.");
                return {};
        }
    }

    LogicExp::PhiNode LogicExp::getRhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().setInsertPoint(branchBlock);
        const auto rhs = getCastedValue(rhs_->codeGen(), Type::BOOL);
        createJumpInst(mergeBlock);
        return std::make_pair(rhs, Context::getInstance().getInsertBlock());
    }
}