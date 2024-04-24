#include "variable.h"
#include "utils/logger.h"
#include "public/public.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "instruction/instruction.h"

namespace mcs {
    // ----------------------------------------get variable----------------------------------------

    llvm::Value* getLocalVariable(llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = createAllocaInst(type);

        if (value == nullptr) {
            LOG_WARN("The local variable \"", id, "\" in function ", Context::getInstance().getCurrentFunctionName(),
                     "() is not assigned an initial value.");
        } else {
            createStoreInst(getCastedValue(value, type), variable);
        }

        return variable;
    }

    llvm::Value* getGlobalVariable(llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = new llvm::GlobalVariable(Context::getInstance().getModule(), type, false,
                                                       llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                                       getConstantValue(value, type), id);

        if (value != nullptr && !llvm::isa<llvm::Constant>(value)) {
            createStoreInst(getCastedValue(value, type), variable);
        }

        return variable;
    }

    Symbol getVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value) {
        using Function = std::function<llvm::Value*(llvm::Type*, const std::string& id, llvm::Value*)>;
        static const std::unordered_map<Scope, Function> scope2Func = {
            {Scope::LOCAL,  getLocalVariable},
            {Scope::GLOBAL, getGlobalVariable},
        };

        const auto it = scope2Func.find(Context::getInstance().getCurrentScope());
        if (it == scope2Func.end()) {
            LOG_ERROR("Unable to get variable because the scope type is unknown.");
            return {};
        }

        return {isConstant, type, it->second(type, id, value)};
    }

    // ----------------------------------------declare variable----------------------------------------

    bool declareVariable(llvm::Type* type, const std::string& id, llvm::Value* value) {
        return declareVariable(false, type, id, value);
    }

    bool declareVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().findSymbol(id)) {
            LOG_ERROR("Unable to declare ", scope, " variable. Because its id (aka \"", id,
                      "\") already exists in ", scope, " symbol table.");
            return false;
        }

        const auto variable = getVariable(isConstant, type, id, value);
        if (!Context::getInstance().insertSymbol(id, variable)) {
            LOG_ERROR("Unable to declare ", scope, " variable. Because it cannot be inserted into ", scope,
                      " symbol table and its id is \"", id, "\".");
            return false;
        }

        return true;
    }

    bool declareVariable(bool isConstant, const std::string& type, const std::string& id,
                         const std::vector<int>& arraySize, llvm::Value* value) {
        return declareVariable(isConstant, getLLVMType(type, arraySize), id, value);
    }
}