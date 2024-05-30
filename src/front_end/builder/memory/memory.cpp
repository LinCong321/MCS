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

    std::pair<llvm::Type*, llvm::Value*> handlePointer(const Symbol& symbol, std::vector<llvm::Value*>& indices) {
        auto type = symbol.getType();
        if (type == nullptr) {
            LOG_ERROR("Unable to handle pointer because type is nullptr.");
            return std::make_pair(nullptr, nullptr);
        }

        auto value = symbol.getValue();
        if (type->isPointerTy()) {
            type = symbol.getPointerElementType();
            value = createGetElementPtrInst(type, symbol.getValue(), {indices.front()});
            indices.erase(indices.begin());
        }

        return std::make_pair(type, value);
    }

    std::pair<llvm::Type*, llvm::Value*> getTypeAndVariable(const Symbol& symbol, std::vector<llvm::Value*> indices) {
        if (indices.empty()) {
            return std::make_pair(symbol.getType(), symbol.getValue());
        }

        const auto [type, variable] = handlePointer(symbol, indices);
        if (indices.empty()) {
            return std::make_pair(type, variable);
        }

        indices.insert(indices.begin(), getConstantInt32(0));
        return std::make_pair(getLLVMType(type, indices.size() - 1), createGetElementPtrInst(type, variable, indices));
    }

    llvm::Instruction* createLoadInst(const std::string& id, const std::vector<llvm::Value*>& indices) {
        Symbol symbol;

        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Use of undeclared identifier \"", id, "\".");
            return nullptr;
        }

        const auto [type, variable] = getTypeAndVariable(symbol, indices);

        if (!type->isArrayTy()) {
            return new llvm::LoadInst(type, variable, "", Context::getInstance().getInsertBlock());
        } else {
            return createGetElementPtrInst(type, variable, std::vector<llvm::Value*>(2, getConstantInt32(0)));
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

        const auto [type, variable] = getTypeAndVariable(symbol, indices);

        return createStoreInst(getCastedValue(value, type), variable);
    }

    // ------------------------------------create get element ptr inst------------------------------------

    llvm::Instruction* createGetElementPtrInst(const std::string& id, const std::vector<size_t>& index) {
        Symbol symbol;
        if (!Context::getInstance().getSymbol(id, symbol)) {
            LOG_ERROR("Unable to create get element pointer instruction because getting symbol \"", id, "\" failed.");
            return nullptr;
        }

        std::vector<llvm::Value*> indices(1, getConstantInt32(0));
        for (const auto& idx : index) {
            indices.emplace_back(getConstantInt32(static_cast<int>(idx)));
        }

        return createGetElementPtrInst(symbol.getType(), symbol.getValue(), indices);
    }

    llvm::Instruction* createGetElementPtrInst(llvm::Type* type, llvm::Value* value,
                                               const std::vector<llvm::Value*>& indices) {
        return llvm::GetElementPtrInst::CreateInBounds(type, value, indices, "",
                                                       Context::getInstance().getInsertBlock());
    }
}