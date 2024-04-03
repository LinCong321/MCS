#include "number.h"
#include "IR/context/context.h"

#include "llvm/IR/Constants.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context::getInstance().getContext()), val_, true);
    }

    llvm::Value* FloatNum::codeGen() const {
        return llvm::ConstantFP::get(llvm::Type::getFloatTy(Context::getInstance().getContext()), val_);
    }
}