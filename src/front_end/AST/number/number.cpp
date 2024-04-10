#include "number.h"
#include "code_gen/constant/constant.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return getInt32(val_);
    }

    llvm::Value* FloatNum::codeGen() const {
        return getFloat(val_);
    }
}