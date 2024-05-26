#include "generator.h"

#include "utils/logger.h"
#include "front_end/IR/context/context.h"

#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/IR/LegacyPassManager.h"

namespace {
    const auto triple   = "armv7-none-linux-gnueabihf";
    const auto cpu      = "generic";
    const auto features = "";
}

namespace mcs {
    void initializer() {
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();
    }

    llvm::TargetMachine* getTargetMachine() {
        std::string         error;
        llvm::TargetOptions options;

        const auto target = llvm::TargetRegistry::lookupTarget(triple, error);
        if (target == nullptr) {
            LOG_ERROR("Unable to get target machine because target is nullptr.");
            return nullptr;
        }

        return target->createTargetMachine(triple, cpu, features, options, {});
    }

    bool addPasses(llvm::legacy::PassManager& codeGenPass, llvm::raw_fd_ostream& file) {
        const auto targetMachine = getTargetMachine();
        if (targetMachine == nullptr) {
            LOG_ERROR("Unable to add passes because targetMachine is nullptr.");
            return false;
        }

        Context::getInstance().getModule().setDataLayout(targetMachine->createDataLayout());
        Context::getInstance().getModule().setTargetTriple(triple);

        if (targetMachine->addPassesToEmitFile(codeGenPass, file, nullptr, llvm::CGFT_AssemblyFile)) {
            LOG_ERROR("TargetMachine can't emit a file of this type");
            return false;
        }

        return true;
    }

    bool generate(const std::string& fileName) {
        initializer();

        std::error_code EC;
        llvm::raw_fd_ostream file(fileName, EC, llvm::sys::fs::OF_None);
        if (EC) {
            LOG_ERROR("Could not open file: ", EC.message());
            return false;
        }

        llvm::legacy::PassManager codeGenPass;
        if (!addPasses(codeGenPass, file)) {
            LOG_ERROR("The object code cannot be generated because add passes failed.");
            return false;
        }

        return codeGenPass.run(Context::getInstance().getModule());
    }
}