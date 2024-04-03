#include "number.h"
#include "pub/code_gen_helper.h"

#include "llvm/IR/Constants.h"

namespace mcs {
    llvm::Value* IntNum::codeGen() const {
        return llvm::ConstantInt::get(getLLVMType("int"), val_, true);
    }

    llvm::Value* FloatNum::codeGen() const {
        return llvm::ConstantFP::get(getLLVMType("float"), val_);
    }
}