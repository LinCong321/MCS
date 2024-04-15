#include "logic_exp.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"
#include "builder/public/public.h"
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

    llvm::PHINode* LogicExp::createPHINode(const std::vector<PhiNode>& nodes) {
        const auto phiNode = llvm::PHINode::Create(getLLVMType(Type::BOOL), nodes.size(), "",
                                                   Context::getInstance().getInsertBlock());
        if (phiNode == nullptr) {
            LOG_ERROR("Unable to create PHINode because phiNode is nullptr.");
            return nullptr;
        }
        for (const auto& node : nodes) {
            phiNode->addIncoming(node.first, node.second);
        }
        return phiNode;
    }

    LogicExp::PhiNode LogicExp::getLhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const {
        const auto lhs = getCastedValue(lhs_->codeGen(), Type::BOOL);
        switch (op_) {
            case '|':
                llvm::BranchInst::Create(mergeBlock, branchBlock, lhs, Context::getInstance().getInsertBlock());
                return std::make_pair(getBool(true), Context::getInstance().getInsertBlock());
            case '&':
                llvm::BranchInst::Create(branchBlock, mergeBlock, lhs, Context::getInstance().getInsertBlock());
                return std::make_pair(getBool(false), Context::getInstance().getInsertBlock());
            default:
                LOG_ERROR("Unable to get lhs node because there are not enough cases in switch.");
                return {};
        }
    }

    LogicExp::PhiNode LogicExp::getRhsNode(llvm::BasicBlock* branchBlock, llvm::BasicBlock* mergeBlock) const {
        Context::getInstance().setInsertPoint(branchBlock);
        const auto rhs = getCastedValue(rhs_->codeGen(), Type::BOOL);
        llvm::BranchInst::Create(mergeBlock, Context::getInstance().getInsertBlock());
        return std::make_pair(rhs, Context::getInstance().getInsertBlock());
    }
}