#include <iostream>
#include "IR/context.h"
#include "lexer_parser/parser.hpp"

int main() {
    freopen("../../test/test.cpp", "r", stdin);
    std::unique_ptr<mcs::Node> ast;
    yyparse(ast);
    ast->codeGen();
    const auto module = mcs::Context::getInstance().getModule();
    if (module == nullptr) {
        std::cout << "The module is nullptr!\n";
    } else {
        module->print(llvm::outs(), nullptr);
    }
    return 0;
}