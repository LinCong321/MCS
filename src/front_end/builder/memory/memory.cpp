#include "memory.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
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
}