#include "logic_exp.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "builder/public/public.h"
#include "builder/constant/constant.h"

#include "llvm/IR/Instructions.h"

namespace mcs {
    llvm::Value* LogicExp::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }
        return createLogicalOperation();
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

    llvm::Value* LogicExp::createOrOperation() const {
        const auto function = Context::getInstance().getCurrentFunction();
        const auto orBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto mergeBlock = llvm::BasicBlock::Create(Context::getInstance().getContext());
        const auto currentBlock = Context::getInstance().getInsertBlock();
        llvm::BranchInst::Create(mergeBlock, orBlock, getCastedValue(lhs_->codeGen(), Type::BOOL), currentBlock);
        Context::getInstance().pushBlock(orBlock);
        function->insert(function->end(), orBlock);
        const auto rhs = getCastedValue(rhs_->codeGen(), Type::BOOL);
        llvm::BranchInst::Create(mergeBlock, orBlock);
        Context::getInstance().pushBlock(mergeBlock);
        function->insert(function->end(), mergeBlock);
        const auto phiNode = llvm::PHINode::Create(getLLVMType(Type::BOOL), 2, "", mergeBlock);
        phiNode->addIncoming(getBool(true), currentBlock);
        phiNode->addIncoming(rhs, orBlock);
        return phiNode;
    }

    llvm::Value* LogicExp::createAndOperation() const {
        return nullptr;
    }

    llvm::Value* LogicExp::createLogicalOperation() const {
        switch (op_) {
            case '|':
                return createOrOperation();
            case '&':
                return createAndOperation();
            default:
                LOG_ERROR("Unable to generate code because there are not enough cases in switch.");
                return nullptr;
        }
    }
}