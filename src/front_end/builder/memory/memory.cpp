#include "memory.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create alloca inst----------------------------------------

    llvm::Instruction* createAllocaInst(llvm::Type* type) {
        return new llvm::AllocaInst(type, 0, "", Context::getInstance().getCurrentBlock());
    }

    // ----------------------------------------create load inst----------------------------------------

    llvm::Instruction* createLoadInst(const std::string& id) {
        const auto symbol = Context::getInstance().getSymbol(id);
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getCurrentBlock());
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(const std::string& id, llvm::Value* value) {
        const auto symbol = Context::getInstance().getSymbol(id);
        if (symbol.isConstant()) {
            LOG_ERROR("Unable to create store inst because symbol \"", id, "\" is a constant.");
            return nullptr;
        }
        return createStoreInst(symbol.getValue(), getCastedValue(value, symbol.getType()));
    }

    llvm::Instruction* createStoreInst(llvm::Value* variable, llvm::Value* value) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getCurrentBlock());
    }
}