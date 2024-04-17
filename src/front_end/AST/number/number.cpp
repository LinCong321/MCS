#include "number.h"
#include "builder/constant/constant.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return getConstantInt32(val_);
    }

    llvm::Value* FloatNum::codeGen() const {
        return getConstantFloat(val_);
    }
}