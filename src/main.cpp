#include "utils/logger.h"
#include "IR/context/context.h"
#include "analyzer/parser/parser.hpp"

void codeGen(const std::unique_ptr<mcs::Node>& ast) {
    if (ast == nullptr) {
        LOG_ERROR("ast is nullptr.");
        return;
    }
    ast->codeGen();
    mcs::Context::getInstance().getModule().print(llvm::outs(), nullptr);
}

int main() {
    freopen("../../test/test.cpp", "r", stdin);
    std::unique_ptr<mcs::Node> ast;
    yyparse(ast);
    codeGen(ast);
    return 0;
}