#include "pass_manager.h"
#include "IR/context/context.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

namespace mcs {
    PassManager& PassManager::getInstance() {
        static PassManager self;
        return self;
    }

    void PassManager::run() {
        llvm::legacy::PassManager passManager;
        llvm::PassManagerBuilder passManagerBuilder;
        passManagerBuilder.OptLevel = 3;
        passManagerBuilder.populateModulePassManager(passManager);
        passManager.run(Context::getInstance().getModule());
    }
}