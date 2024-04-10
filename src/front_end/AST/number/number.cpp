#include "number.h"
#include "code_gen/public/public.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return getConstantInt(val_);
    }

    llvm::Value* FloatNum::codeGen() const {
        return getConstantFloat(val_);
    }
}