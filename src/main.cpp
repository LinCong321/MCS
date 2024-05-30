#include "utils/logger.h"
#include "IR/context/context.h"
#include "analyzer/parser/parser.hpp"
#include "back_end/generator/generator.h"
#include "middle_end/pass_manager/pass_manager.h"

void codeGen(std::unique_ptr<mcs::Node>& ast) {
    if (ast == nullptr) {
        LOG_ERROR("ast is nullptr.");
        return;
    }
    ast->constFold(ast);
    ast->codeGen();
    mcs::Context::getInstance().getModule().print(llvm::outs(), nullptr);
}

void optimizeAndGenerate() {
    mcs::PassManager::getInstance().run();
    std::cout << "********************************************************************************\n";
    mcs::Context::getInstance().getModule().print(llvm::outs(), nullptr);
    mcs::generate("../../result.s");
}

int main() {
    freopen("../../test/test.cpp", "r", stdin);
    std::unique_ptr<mcs::Node> ast;
    yyparse(ast);
    codeGen(ast);
    optimizeAndGenerate();
    return 0;
}