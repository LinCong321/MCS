#include <iostream>

#include "node.h"
#include "IR/context.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"

namespace {
    llvm::Type* getType(const std::unique_ptr<std::string>& type) {
        if (type == nullptr) {
            return nullptr;
        }
        if (*type == "int") {
	        return llvm::Type::getInt32Ty(mcs::Context::getInstance().getContext());
        }
        else if (*type == "float") {
	        return llvm::Type::getDoubleTy(mcs::Context::getInstance().getContext());
        }
        return llvm::Type::getVoidTy(mcs::Context::getInstance().getContext());
    }
}

namespace mcs {
    llvm::Value* CompUnit::codeGen() {
        std::cout << "CompUnit generating...\n";
        if (funcDef_ == nullptr) {
            return nullptr;
        }
        return funcDef_->codeGen();
    }

    llvm::Value* FuncDef::codeGen() {
        std::cout << "FuncDef generating...\n";
        std::vector<llvm::Type*> argTypes;
        
        const auto functionType = llvm::FunctionType::get(getType(funcType_),
                                                          llvm::ArrayRef(argTypes),
                                                          false);
                                                          
        const auto function = llvm::Function::Create(functionType,
                                                     llvm::Function::InternalLinkage,
                                                     getId(),
                                                     Context::getInstance().getModule());
                                                     
        const auto basicBlock = llvm::BasicBlock::Create(Context::getInstance().getContext(),
                                                         "entry",
                                                         function);
        Context::getInstance().pushBlock(basicBlock);

        if (block_ == nullptr) {
            return nullptr;
        }
        block_->codeGen();
        
        llvm::ReturnInst::Create(Context::getInstance().getContext(),
                                 Context::getInstance().getCurrentReturnValue(),
                                 basicBlock);
                                 
        Context::getInstance().popBlock();

        return function;
    }

    llvm::Value* Block::codeGen() {
        std::cout << "Block generating...\n";
        if (stmt_ == nullptr) {
            return nullptr;
        }
        return stmt_->codeGen();
    }

    llvm::Value* RetStmt::codeGen() {
        std::cout << "RetStmt generating...\n";
        const auto returnValue = llvm::ConstantInt::get(getType(std::make_unique<std::string>("int")),
                                                        retVal_,
                                                        true);
        Context::getInstance().setCurrentReturnValue(returnValue);
        return returnValue;
    }
}