#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "variable/variable.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------create function params----------------------------------------

    std::string getId(const std::vector<Symbol>& params, size_t pos) {
        if (pos >= params.size()) {
            LOG_ERROR("Unable to get ID because pos is ", pos, " which exceeds params' size of ", params.size(), ".");
            return {};
        }
        return params[pos].getName();
    }

    bool createFunctionParams(llvm::Function* function, const std::vector<Symbol>& params) {
        if (function == nullptr) {
            LOG_ERROR("Unable to create function params because function is nullptr.");
            return false;
        }

        size_t pos = 0;
        for (auto& arg : function->args()) {
            if (!declareVariable(arg.getType(), getId(params, pos++), &arg)) {
                LOG_ERROR("Unable to create function params because the variable cannot be declared.");
                return false;
            }
        }

        return true;
    }

    // --------------------------------------------get function--------------------------------------------

    std::vector<llvm::Type*> getTypesOf(const std::vector<Symbol>& params) {
        std::vector<llvm::Type*> types;
        for (const auto& param : params) {
            types.emplace_back(param.getType());
        }
        return types;
    }

    llvm::Function::LinkageTypes getLinkage(const std::string& name) {
        return (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
    }

    llvm::Function* getFunction(Type retType, const std::string& name, const std::vector<Symbol>& params) {
        return getFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, const std::vector<Symbol>& params) {
        const auto function = llvm::Function::Create(llvm::FunctionType::get(retType, getTypesOf(params), false),
                                                     getLinkage(name), name, Context::getInstance().getModule());
        Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function));
        createFunctionParams(function, params);
        return function;
    }

    // --------------------------------------------create function--------------------------------------------

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name, const std::vector<Symbol>& params) {
        if (Context::getInstance().findSymbol(name)) {
            LOG_ERROR("Cannot create function because its name (aka \"", name,
                      "\") already exists in the symbol table.");
            return nullptr;
        }

        const auto function = getFunction(retType, name, params);
        if (!Context::getInstance().insertSymbol(name, Symbol())) {
            LOG_ERROR("Cannot create function because it cannot be inserted to the symbol table.");
            return nullptr;
        }

        return function;
    }

    llvm::Function* createFunction(const std::string& retType, const std::string& name,
                                   const std::vector<Symbol>& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}