#include "branch.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create break inst----------------------------------------

    llvm::Instruction* createBreakInst() {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to create break instruction because getting loop information failed.");
            return nullptr;
        }
        return createJumpInst(loopInfo.getBreakBlock());
    }

    // ----------------------------------------create continue inst----------------------------------------

    llvm::Instruction* createContinueInst() {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to create continue instruction because getting loop information failed.");
            return nullptr;
        }
        return createJumpInst(loopInfo.getContinueBlock());
    }

    // ----------------------------------------create jump inst----------------------------------------

    llvm::Instruction* createJumpInst(llvm::BasicBlock* basicBlock) {
        if (Context::getInstance().getInsertBlock() == nullptr) {
            return nullptr;
        }
        return llvm::BranchInst::Create(basicBlock, Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create phi node----------------------------------------

    llvm::PHINode* getPHINode(size_t size) {
        return llvm::PHINode::Create(getLLVMType(Type::BOOL), size, "", Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createPHINode(const std::vector<std::pair<llvm::Value*, llvm::BasicBlock*>>& nodes) {
        const auto phiNode = getPHINode(nodes.size());
        if (phiNode == nullptr) {
            LOG_ERROR("Unable to create PHINode because phiNode is nullptr.");
            return nullptr;
        }
        for (const auto& node : nodes) {
            phiNode->addIncoming(node.first, node.second);
        }
        return phiNode;
    }

    // ----------------------------------------create branch inst----------------------------------------

    llvm::Instruction* createBranchInst(llvm::BasicBlock* ifTrue, llvm::BasicBlock* ifFalse, llvm::Value* cond) {
        return llvm::BranchInst::Create(ifTrue, ifFalse, getCastedValue(cond, Type::BOOL),
                                        Context::getInstance().getInsertBlock());
    }
}