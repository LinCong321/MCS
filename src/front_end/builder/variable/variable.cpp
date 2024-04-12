#include "variable.h"
#include "utils/logger.h"
#include "public/public.h"
#include "memory/memory.h"
#include "constant/constant.h"
#include "IR/context/context.h"

namespace mcs {
    // --------------------------------------------declare variable--------------------------------------------

    llvm::Value* getLocalVariable(llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = createAllocaInst(type);

        if (value == nullptr) {
            LOG_WARN("The local variable \"", id, "\" in function ", Context::getInstance().getCurrentFunctionName(),
                     "() is not assigned an initial value.");
            return variable;
        }

        createStoreInst(variable, getCastedValue(value, type));
        return variable;
    }

    llvm::Value* getGlobalVariable(llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = new llvm::GlobalVariable(Context::getInstance().getModule(), type, false,
                                                       llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                                       getConstant(value, type), id);

        if (value != nullptr && !llvm::isa<llvm::Constant>(value)) {
            createStoreInst(variable, getCastedValue(value, type));
        }

        return variable;
    }

    Symbol getVariable(llvm::Type* type, const std::string& id, llvm::Value* value, bool isConstant) {
        using Function = std::function<llvm::Value*(llvm::Type*, const std::string& id, llvm::Value*)>;
        static const std::unordered_map<Scope, Function> scope2Func = {
            {Scope::LOCAL,  getLocalVariable},
            {Scope::GLOBAL, getGlobalVariable},
        };

        const auto it = scope2Func.find(Context::getInstance().getCurrentScope());
        if (it == scope2Func.end()) {
            LOG_ERROR("Unable to get variable because the scope type is unknown.");
            return Symbol();
        }

        return Symbol(type, it->second(type, id, value), isConstant);
    }

    bool declareVariable(llvm::Type* type, const std::string& id, llvm::Value* value, bool isConstant) {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().checkSymbol(id)) {
            LOG_ERROR("Unable to declare ", scope, " variable. Because its id (aka \"", id,
                      "\") already exists in the ", scope, " symbol table.");
            return false;
        }

        const auto variable = getVariable(type, id, value, isConstant);
        if (!Context::getInstance().insertSymbol(id, variable)) {
            LOG_ERROR("Unable to declare ", scope, " variable. Because it cannot be inserted into the ", scope,
                      " symbol table and its id is \"", id, "\".");
            return false;
        }

        return true;
    }

    bool declareVariable(const std::string& type, const std::string& id, llvm::Value* value, bool isConstant) {
        return declareVariable(getLLVMType(type), id, value, isConstant);
    }
}