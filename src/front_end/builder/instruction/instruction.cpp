#include "instruction.h"
#include "utils/logger.h"
#include "public/public.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create return inst----------------------------------------

    llvm::ReturnInst* createVoidReturnInst(llvm::Value* value) {
        if (value != nullptr) {
            LOG_ERROR("Void function ", Context::getInstance().getCurrentFunctionName(),
                      "() should not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), Context::getInstance().getInsertBlock());
    }

    llvm::ReturnInst* createNonVoidReturnInst(llvm::Value* value, llvm::Type* type) {
        if (value == nullptr) {
            LOG_ERROR("Non-void function ", Context::getInstance().getCurrentFunctionName(),
                      "() does not return a value.");
            return nullptr;
        }
        return llvm::ReturnInst::Create(Context::getInstance().getContext(), getCastedValue(value, type),
                                        Context::getInstance().getInsertBlock());
    }

    llvm::Instruction* createReturnInst(llvm::Value* value) {
        const auto type = Context::getInstance().getReturnTypeOfCurrentFunction();
        if (type == nullptr) {
            LOG_ERROR("Unable to create return instruction because type is nullptr.");
            return nullptr;
        }
        return type->isVoidTy() ? createVoidReturnInst(value) : createNonVoidReturnInst(value, type);
    }

    // ----------------------------------------create call inst----------------------------------------

    llvm::Value* getValue(const std::vector<llvm::Value*>& values, size_t& pos, llvm::Type* type) {
        if (pos >= values.size()) {
            LOG_ERROR("Unable to get value because pos = ", pos, " exceeds number of values = ", values.size(), ".");
            return nullptr;
        }

        if (type == nullptr) {
            LOG_ERROR("Unable to get value because type is nullptr.");
            return nullptr;
        }

        return type->isPointerTy() ? values[pos++] : getCastedValue(values[pos++], type);
    }

    std::vector<llvm::Value*> getCastedArgs(const llvm::iterator_range<llvm::Function::arg_iterator>& args,
                                            const std::vector<llvm::Value*>& values) {
        std::vector<llvm::Value*> castedValues;
        size_t pos = 0;
        for (const auto& arg : args) {
            castedValues.emplace_back(getValue(values, pos, arg.getType()));
        }
        return std::move(castedValues);
    }

    llvm::Instruction* createCallInst(const std::string& id, const std::vector<llvm::Value*>& values) {
        const auto function = Context::getInstance().getModule().getFunction(id);
        if (function == nullptr) {
            LOG_ERROR("The call instruction cannot be created because the function ", id, "() does not exist.");
            return nullptr;
        }

        if (function->arg_size() != values.size()) {
            LOG_ERROR("The call instruction cannot be created because the number of actual arguments = ", values.size(),
                      " is not equal to the number of formal parameters of the function ", id, "() = ",
                      function->arg_size(), ".");
            return nullptr;
        }

        return llvm::CallInst::Create(function, getCastedArgs(function->args(), values), "",
                                      Context::getInstance().getInsertBlock());
    }
}