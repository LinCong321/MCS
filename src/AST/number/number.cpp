#include "number.h"
#include "ast_utils/utils.h"
#include "llvm/IR/Constants.h"
#include "IR/context/context.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context::getInstance().getContext()), val_, true);
    }

    llvm::Value* FloatNum::codeGen() {
        return llvm::ConstantFP::get(llvm::Type::getFloatTy(Context::getInstance().getContext()), val_);
    }
}