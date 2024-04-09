#include "start.h"
#include "utils/logger.h"
#include "func/function.h"
#include "IR/context/context.h"
#include "pub/code_gen_helper.h"

namespace {
    const auto MAX_PRIORITY = 65535;
    const auto INIT_GLOBAL_VAR = "initGlobalVar";
    const auto LLVM_GLOBAL_CTORS = "llvm.global_ctors";
}

namespace mcs {
    llvm::Value* Start::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        const auto initFunc = createFunction(Type::VOID, INIT_GLOBAL_VAR);
        if (!createLLVMGlobalCtors(initFunc)) {
            LOG_ERROR("Failed to create llvm.global_ctors.");
            return nullptr;
        }

        const auto value = compUnit_->codeGen();
        createFunctionReturnValue();
        return value;
    }

    bool Start::checkAllMemberPointers() const {
        if (compUnit_ == nullptr) {
            LOG_ERROR("compUnit_ is nullptr.");
            return false;
        }
        return true;
    }

    bool Start::createLLVMGlobalCtors(llvm::Function* function) {
        if (function == nullptr) {
            LOG_ERROR("Unable to create llvm.global_ctors because function is nullptr.");
            return false;
        }

        const auto elements = std::vector<llvm::Type*>({getLLVMType(Type::INT), getPointerType(function->getType())});
        const auto structType = llvm::StructType::get(Context::getInstance().getContext(), elements);

        const auto arrayType = llvm::ArrayType::get(structType, 1);
        const auto ctor = llvm::ConstantStruct::get(structType, getConstantInt(MAX_PRIORITY), function);
        const auto constantArray = llvm::ConstantArray::get(arrayType, {ctor});

        new llvm::GlobalVariable(Context::getInstance().getModule(), arrayType, true,
                                 llvm::GlobalValue::AppendingLinkage, constantArray, LLVM_GLOBAL_CTORS);
        return true;
    }
}