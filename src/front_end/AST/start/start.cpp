#include "start.h"
#include "utils/logger.h"
#include "llvm/IR/Constants.h"
#include "IR/context/context.h"
#include "builder/public/public.h"
#include "builder/constant/constant.h"
#include "builder/function/function.h"
#include "builder/instruction/instruction.h"
#include "number/constant_table/constant_table.h"

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

        const auto initFunc = getFunction(Type::VOID, INIT_GLOBAL_VAR);
        if (!createLLVMGlobalCtors(initFunc)) {
            LOG_ERROR("Unable to generate code because llvm.global_ctors cannot be created.");
            return nullptr;
        }

        const auto value = compUnit_->codeGen();
        if (createReturnInst() == nullptr) {
            LOG_ERROR("Unable to generate code because the return instruction is nullptr.");
            return nullptr;
        }

        Context::getInstance().popBlock();
        return value;
    }

    void Start::constFold(std::unique_ptr<Node>&) {
        ConstantTable::getInstance().create();
        if (compUnit_ != nullptr) {
            compUnit_->constFold(compUnit_);
        }
        ConstantTable::getInstance().remove();
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

        const auto elements       = std::vector<llvm::Type*>({getLLVMType("int"), getPointerType(function->getType())});
        const auto structType     = llvm::StructType::get(Context::getInstance().getContext(), elements);
        const auto arrayType      = llvm::ArrayType::get(structType, 1);
        const auto constantStruct = llvm::ConstantStruct::get(structType, getConstantInt32(MAX_PRIORITY), function);
        const auto constantArray  = llvm::ConstantArray::get(arrayType, {constantStruct});

        new llvm::GlobalVariable(Context::getInstance().getModule(), arrayType, true,
                                 llvm::GlobalValue::AppendingLinkage, constantArray, LLVM_GLOBAL_CTORS);
        return true;
    }
}