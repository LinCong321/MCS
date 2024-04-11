#include "null_stmt.h"

namespace mcs {
    llvm::Value* NullStmt::codeGen() const {
        return nullptr;
    }
}