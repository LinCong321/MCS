#include "number.h"
#include "pub/code_gen_helper.h"

#include "llvm/IR/Constants.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return getConstantInt(val_);
    }

    llvm::Value* FloatNum::codeGen() const {
        return getConstantFloat(val_);
    }
}