#pragma once

#include "llvm/IR/Instruction.h"

namespace mcs {
    llvm::Instruction* createAllocaInst(llvm::Type* type);

    llvm::Instruction* createLoadInst(llvm::Type* type, llvm::Value* value);
    llvm::Instruction* createLoadInst(const std::string& id, const std::vector<llvm::Value*>& indices);

    llvm::Instruction* createGetElementPtrInst(const std::string& id, const std::vector<size_t>& index);
    llvm::Instruction* createGetElementPtrInst(llvm::Type* type, llvm::Value* value, std::vector<llvm::Value*> indices);

    llvm::Instruction* createStoreInst(llvm::Value* value, llvm::Value* variable);
    llvm::Instruction* createStoreInst(llvm::Value* value, const std::string& id,
                                       const std::vector<llvm::Value*>& indices);
}