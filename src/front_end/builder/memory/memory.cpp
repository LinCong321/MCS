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
        const auto symbol = Context::getInstance().getSymbol(id);
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id) {
        const auto symbol = Context::getInstance().getSymbol(id);
        if (symbol.isConstant()) {
            LOG_ERROR("Unable to create store inst because symbol \"", id, "\" is a constant.");
            return nullptr;
        }
        return createStoreInst(getCastedValue(value, symbol.getType()), symbol.getValue());
    }
}