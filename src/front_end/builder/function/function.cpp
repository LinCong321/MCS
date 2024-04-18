#include "function.h"
#include "utils/logger.h"
#include "public/public.h"
#include "variable/variable.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // --------------------------------------------get function--------------------------------------------

    std::vector<llvm::Type*> getTypes(const Params& params) {
        std::vector<llvm::Type*> types;
        for (const auto& param : params) {
            types.emplace_back(param.first);
        }
        return types;
    }

    llvm::Function::LinkageTypes getLinkageType(const std::string& name) {
        return (name == "main") ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
    }

    std::string getId(const Params& params, size_t pos) {
        if (pos > params.size()) {
            LOG_ERROR("Unable to get ID because pos is ", pos, " which exceeds params' size of ", params.size(), ".");
            return {};
        }
        return params[pos].second;
    }

    bool createFunctionParams(llvm::Function* function, const Params& params) {
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

    llvm::Function* getFunction(Type retType, const std::string& name, const Params& params) {
        return getFunction(getLLVMType(retType), name, params);
    }

    llvm::Function* getFunction(llvm::Type* retType, const std::string& name, const Params& params) {
        const auto function = llvm::Function::Create(llvm::FunctionType::get(retType, getTypes(params), false),
                                                     getLinkageType(name), name, Context::getInstance().getModule());
        Context::getInstance().pushBlock(llvm::BasicBlock::Create(Context::getInstance().getContext(), "", function));
        createFunctionParams(function, params);
        return function;
    }

    // --------------------------------------------create function--------------------------------------------

    llvm::Function* createFunction(llvm::Type* retType, const std::string& name, const Params& params) {
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

    llvm::Function* createFunction(const std::string& retType, const std::string& name, const Params& params) {
        return createFunction(getLLVMType(retType), name, params);
    }
}