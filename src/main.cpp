#include <iostream>
#include "utils/logger.h"
#include "IR/context/context.h"
#include "LAP/parser/parser.hpp"

void printIR() {
    mcs::Context::getInstance().getModule().print(llvm::outs(), nullptr);
}

int main() {
    freopen("../../test/test.cpp", "r", stdin);
    std::unique_ptr<mcs::Node> ast;
    yyparse(ast);
    if (ast == nullptr) {
        LOG_ERROR("ast is nullptr.");
        return 0;
    }
    ast->codeGen();
    printIR();
    return 0;
}