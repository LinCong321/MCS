#include "memory.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
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
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }
        return new llvm::LoadInst(symbol.getType(), symbol.getValue(), "", Context::getInstance().getInsertBlock());
    }

    // ------------------------------------create get element ptr inst------------------------------------

    llvm::Instruction* createGetElementPtrInst(llvm::Type* type, llvm::Value* value,
                                               const std::vector<size_t>& index) {
        std::vector<llvm::Value*> indices(1, getConstantInt32(0));
        for (const auto& idx : index) {
            indices.emplace_back(getConstantInt32(static_cast<int>(idx)));
        }
        return llvm::GetElementPtrInst::CreateInBounds(type, value, indices, "",
                                                       Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createGetElementPtrInst(const std::string& id, const std::vector<size_t>& index) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Unable to create get element pointer instruction because getting symbol \"", id, "\" failed.");
            return nullptr;
        }
        return createGetElementPtrInst(symbol.getType(), symbol.getValue(), index);
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id) {
        Symbol symbol;

        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }

        if (symbol.isConstant()) {
            LOG_ERROR("Cannot assign value to const variable \"", id, "\".");
            return nullptr;
        }

        return createStoreInst(getCastedValue(value, symbol.getType()), symbol.getValue());
    }

    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id, const std::vector<size_t>& index) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol) || symbol.isConstant()) {
            LOG_ERROR("The store instruction cannot be created because getting symbol \"", id,
                      "\" failed or it is a constant.");
            return nullptr;
        }
        return createStoreInst(value, createGetElementPtrInst(symbol.getType(), symbol.getValue(), index));
    }
}