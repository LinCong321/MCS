#include <iostream>
#include <filesystem>
#include "lexer_parser/parser.hpp"

int main() {
    freopen("../../test/test.cpp", "r", stdin);
    std::unique_ptr<mcs::Node> ast;
    yyparse(ast);
    ast->codeGen();
    return 0;
}