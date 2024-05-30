#include <llvm/IR/PassManager.h>
#include "log.h"
#include "pass_manager.h"

using namespace llvm;

PreservedAnalyses HelloWorldPass::run(Function &F, FunctionAnalysisManager &AM) {
    log("hello pass") << F.getName().str() << std::endl;
    return PreservedAnalyses::all();
}
