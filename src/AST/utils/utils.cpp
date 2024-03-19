#include "AST/utils/utils.h"
#include "IR/context.h"

namespace mcs {
    llvm::Type* getType(const std::string& type) {
        if (type == "int") {
            return llvm::Type::getInt32Ty(Context::getInstance().getContext());
        }
        else if (type == "float") {
            return llvm::Type::getDoubleTy(Context::getInstance().getContext());
        }
        return llvm::Type::getVoidTy(Context::getInstance().getContext());
    }
}