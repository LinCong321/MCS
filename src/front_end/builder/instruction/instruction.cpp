#include "instruction.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "function/function.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create alloca inst----------------------------------------

    llvm::Instruction* createAllocaInst(llvm::Type* type) {
        return new llvm::AllocaInst(type, 0, "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create load inst----------------------------------------

    llvm::Instruction* createLoadInst(const std::string& id) {
        const auto symbol = Context::getInstance().getSymbol(id);
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create return inst----------------------------------------

    llvm::ReturnInst* getVoidReturnInst(llvm::Value* value) {
        if (value != nullptr) {
            LOG_ERROR("Void function ", Context::getInstance().getCurrentFunctionName(),
                      "() should not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), Context::getInstance().getInsertBlock());
    }

    llvm::ReturnInst* getNonVoidReturnInst(llvm::Value* value, llvm::Type* type) {
        if (value == nullptr) {
            LOG_WARN("Non-void function ", Context::getInstance().getCurrentFunctionName(),
                     "() does not return a value.");
            value = getNullValue(type);
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), getCastedValue(value, type),
                                        Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createReturnInst(llvm::Value* value) {
        const auto type = Context::getInstance().getReturnTypeOfCurrentFunction();
        if (type == nullptr) {
            LOG_ERROR("Unable to create return inst because type is nullptr.");
            return nullptr;
        }
        return type->isVoidTy() ? getVoidReturnInst(value) : getNonVoidReturnInst(value, type);
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(llvm::Value* variable, llvm::Value* value) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createStoreInst(const std::string& id, llvm::Value* value) {
        const auto symbol = Context::getInstance().getSymbol(id);
        if (symbol.isConstant()) {
            LOG_ERROR("Unable to create store inst because symbol \"", id, "\" is a constant.");
            return nullptr;
        }
        return createStoreInst(symbol.getValue(), getCastedValue(value, symbol.getType()));
    }
}