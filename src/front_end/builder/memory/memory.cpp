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

    llvm::Type* getActualType(const Symbol& symbol) {
        const auto type = symbol.getType();
        if (type == nullptr) {
            LOG_ERROR("Unable to get actual type because type is nullptr.");
            return nullptr;
        }
        return type->isPointerTy() ? symbol.getPointerElementType() : type;
    }

    llvm::Type* getCurrentType(const Symbol& symbol, size_t size) {
        const auto type = symbol.getType();
        if (type == nullptr) {
            LOG_ERROR("Unable to get current type because type is nullptr.");
            return nullptr;
        }
        if (!type->isPointerTy()) {
            return getLLVMType(type, size);
        }
        return size ? getLLVMType(symbol.getPointerElementType(), size - 1) : type;
    }

    llvm::Instruction* createLoadInst(const std::string& id, const std::vector<llvm::Value*>& indices) {
        Symbol symbol;

        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }

        auto variable = symbol.getValue();
        if (!indices.empty()) {
            variable = createGetElementPtrInst(getActualType(symbol), symbol.getValue(), indices);
        }

        const auto type = getCurrentType(symbol, indices.size());
        if (!type->isArrayTy()) {
            return new llvm::LoadInst(type, variable, "", Context::getInstance().getInsertBlock());
        } else {
            return createGetElementPtrInst(type, variable, std::vector<llvm::Value*>(1, getConstantInt32(0)));
        }
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

        auto variable = symbol.getValue();
        if (!indices.empty()) {
            variable = createGetElementPtrInst(getActualType(symbol), symbol.getValue(), indices);
        }

        return createStoreInst(getCastedValue(value, getCurrentType(symbol, indices.size())), variable);
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
        if (type == nullptr) {
            LOG_ERROR("Unable to create get element ptr instruction because type is nullptr.");
            return nullptr;
        }

        if (type->isArrayTy()) {
            indices.insert(indices.begin(), getConstantInt32(0));
        }

        return llvm::GetElementPtrInst::CreateInBounds(type, value, indices, "",
                                                       Context::getInstance().getInsertBlock());
    }
}