#include "instruction.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create break inst----------------------------------------

    llvm::Instruction* createBreakInst() {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to generate code because getting loop information failed.");
            return nullptr;
        }
        return createJumpInst(loopInfo.getBreakBlock());
    }

    // ----------------------------------------create continue inst----------------------------------------

    llvm::Instruction* createContinueInst() {
        LoopInfo loopInfo;
        if (!Context::getInstance().getCurrentLoopInfo(loopInfo)) {
            LOG_ERROR("Unable to generate code because getting loop information failed.");
            return nullptr;
        }
        return createJumpInst(loopInfo.getContinueBlock());
    }

    // ----------------------------------------create alloca inst----------------------------------------

    llvm::Instruction* createAllocaInst(llvm::Type* type) {
        return new llvm::AllocaInst(type, 0, "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create load inst----------------------------------------

    llvm::Instruction* createLoadInst(const std::string& id) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("The load instruction cannot be created because getting symbol \"", id, "\" failed.");
            return nullptr;
        }
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create call inst----------------------------------------

    llvm::Instruction* createCallInst(const std::string& id) {
        const auto function = Context::getInstance().getModule().getFunction(id);
        if (function == nullptr) {
            LOG_ERROR("Unable to generate code because function \"", id, "() does not exist.");
            return nullptr;
        }
        return llvm::CallInst::Create(function, "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create return inst----------------------------------------

    llvm::ReturnInst* createVoidReturnInst(llvm::Value* value) {
        if (value != nullptr) {
            LOG_ERROR("Void function ", Context::getInstance().getCurrentFunctionName(),
                      "() should not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), Context::getInstance().getInsertBlock());
    }

    llvm::ReturnInst* createNonVoidReturnInst(llvm::Value* value, llvm::Type* type) {
        if (value == nullptr) {
            LOG_ERROR("Non-void function ", Context::getInstance().getCurrentFunctionName(),
                      "() does not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), getCastedValue(value, type),
                                        Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createReturnInst(llvm::Value* value) {
        const auto type = Context::getInstance().getReturnTypeOfCurrentFunction();
        if (type == nullptr) {
            LOG_ERROR("Cannot create return instruction because type is nullptr.");
            return nullptr;
        }
        const auto returnInst = type->isVoidTy() ? createVoidReturnInst(value) : createNonVoidReturnInst(value, type);
        Context::getInstance().clearInsertionPoint();
        return returnInst;
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol) || symbol.isConstant()) {
            LOG_ERROR("The store instruction cannot be created because getting symbol \"", id,
                      "\" failed or it is a constant.");
            return nullptr;
        }
        return createStoreInst(getCastedValue(value, symbol.getType()), symbol.getValue());
    }

    // ----------------------------------------create phi node----------------------------------------

    llvm::PHINode* getPHINode(size_t size) {
        return llvm::PHINode::Create(getLLVMType(Type::BOOL), size, "",Context::getInstance().getInsertBlock());
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

    // ----------------------------------------create jump inst----------------------------------------

    llvm::Instruction* createJumpInst(llvm::BasicBlock* basicBlock) {
        if (Context::getInstance().getInsertBlock() == nullptr) {
            LOG_INFO("The current basic block has been terminated, so there is no need to create a jump instruction.");
            return nullptr;
        }
        return llvm::BranchInst::Create(basicBlock, Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create branch inst----------------------------------------

    llvm::Instruction* createBranchInst(llvm::BasicBlock* ifTrue, llvm::BasicBlock* ifFalse, llvm::Value* cond) {
        return llvm::BranchInst::Create(ifTrue, ifFalse, getCastedValue(cond, Type::BOOL),
                                        Context::getInstance().getInsertBlock());
    }
}