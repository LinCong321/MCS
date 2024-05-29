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

    llvm::Instruction* createLoadInst(llvm::Type* type, llvm::Value* value) {
        return new llvm::LoadInst(type, value, "", Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createLoadInst(const std::string& id, const std::vector<llvm::Value*>& indices) {
        Symbol symbol;

        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }

        if (indices.empty()) {
            return createLoadInst(symbol.getType(), symbol.getValue());
        } else {
            return createLoadInst(getLLVMType(symbol.getType()),
                                  createGetElementPtrInst(symbol.getType(), symbol.getValue(), indices));
        }
    }

    // ------------------------------------create get element ptr inst------------------------------------

    llvm::Instruction* createGetElementPtrInst(const std::string& id, const std::vector<size_t>& index) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Unable to create get element pointer instruction because getting symbol \"", id, "\" failed.");
            return nullptr;
        }

        std::vector<llvm::Value*> indices;
        for (const auto& idx : index) {
            indices.emplace_back(getConstantInt32(static_cast<int>(idx)));
        }

        return createGetElementPtrInst(symbol.getType(), symbol.getValue(), indices);
    }

    llvm::Instruction* createGetElementPtrInst(llvm::Type* type, llvm::Value* value,
                                               std::vector<llvm::Value*> indices) {
        indices.insert(indices.begin(), getConstantInt32(0));
        return llvm::GetElementPtrInst::CreateInBounds(type, value, indices, "",
                                                       Context::getInstance().getInsertBlock());
    }

    // ----------------------------------------create store inst----------------------------------------

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable) {
        return new llvm::StoreInst(value, variable, false, Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id,
                                       const std::vector<llvm::Value*>& indices) {
        Symbol symbol;

        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }

        if (symbol.isConstant()) {
            LOG_ERROR("Cannot assign value to const variable \"", id, "\".");
            return nullptr;
        }

        if (indices.empty()) {
            return createStoreInst(getCastedValue(value, symbol.getType()), symbol.getValue());
        } else {
            return createStoreInst(getCastedValue(value, getLLVMType(symbol.getType())),
                                   createGetElementPtrInst(symbol.getType(), symbol.getValue(), indices));
        }
    }
}