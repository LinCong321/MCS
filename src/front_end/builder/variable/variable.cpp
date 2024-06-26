#include "variable.h"
#include "utils/logger.h"
#include "public/public.h"
#include "memory/memory.h"
#include "constant/constant.h"
#include "IR/context/context.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    // ----------------------------------------declare function param----------------------------------------

    bool declareFunctionParam(const Parameter& parameter, llvm::Value* value) {
        if (Context::getInstance().findSymbol(parameter.getName())) {
            LOG_ERROR("Unable to declare the function parameter. Because its id (aka \"", parameter.getName(),
                      "\") already exists in local symbol table.");
            return false;
        }

        const auto type = getPointerType(parameter.getType(), parameter.getArraySize());
        const auto param = createAllocaInst(type);
        createStoreInst(value, param);

        const auto symbol = Symbol(false, type, param, getLLVMType(parameter.getType(), parameter.getArraySize()));
        return Context::getInstance().insertSymbol(parameter.getName(), symbol);
    }

    // --------------------------------------------get variable--------------------------------------------

    llvm::Constant* getInitializer(llvm::Value* value, llvm::Type* type) {
        if (value == nullptr || !llvm::isa<llvm::Constant>(value)) {
            return getNullValue(type);
        }
        return getConstantValue(value, type);
    }

    llvm::Value* getGlobalVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = new llvm::GlobalVariable(Context::getInstance().getModule(), type, isConstant,
                                                       llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                                       getInitializer(value, type), id);

        if (value != nullptr && !llvm::isa<llvm::Constant>(value)) {
            createStoreInst(getCastedValue(value, type), variable);
        }

        return variable;
    }

    llvm::Value* getLocalVariable(bool, llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto variable = createAllocaInst(type);

        if (value == nullptr) {
            LOG_INFO("The local variable \"", id, "\" in function ", Context::getInstance().getCurrentFunctionName(),
                     "() is not assigned an initial value.");
        } else {
            createStoreInst(getCastedValue(value, type), variable);
        }

        return variable;
    }

    Symbol getVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value) {
        using Function = std::function<llvm::Value*(bool, llvm::Type*, const std::string&, llvm::Value*)>;
        static const std::unordered_map<Scope, Function> scope2Func = {
            {Scope::GLOBAL, getGlobalVariable},
            {Scope::LOCAL,  getLocalVariable},
        };

        const auto it = scope2Func.find(Context::getInstance().getCurrentScope());
        if (it == scope2Func.end()) {
            LOG_ERROR("Unable to get variable because the scope type is unknown.");
            return {};
        }

        return {isConstant, type, it->second(isConstant, type, id, value)};
    }

    // ----------------------------------------declare variable----------------------------------------

    bool declareVariable(bool isConstant, llvm::Type* type, const std::string& id, llvm::Value* value) {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().findSymbol(id)) {
            LOG_ERROR("Unable to declare ", scope, " variable. ",
                      "Because its id (aka \"", id, "\") already exists in ", scope, " symbol table.");
            return false;
        }

        const auto variable = getVariable(isConstant, type, id, value);
        if (!Context::getInstance().insertSymbol(id, variable)) {
            LOG_ERROR("Unable to declare ", scope, " variable. ",
                      "Because it cannot be inserted into ", scope, " symbol table and its id is \"", id, "\".");
            return false;
        }

        return true;
    }

    bool declareVariable(bool isConstant, const std::string& type, const std::string& id, llvm::Value* value) {
        return declareVariable(isConstant, getLLVMType(type), id, value);
    }

    // --------------------------------------------get array--------------------------------------------

    llvm::Value* getGlobalArray(bool isConstant, llvm::Type* type, const std::string& id, llvm::Constant* constant) {
        return new llvm::GlobalVariable(Context::getInstance().getModule(), type, isConstant,
                                        llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                        (constant != nullptr) ? constant : getNullValue(type), id);
    }

    Symbol getArray(bool isConstant, llvm::Type* type, const std::string& id, llvm::Constant* constant) {
        switch (Context::getInstance().getCurrentScope()) {
            case Scope::GLOBAL:
                return {isConstant, type, getGlobalArray(isConstant, type, id, constant)};
            case Scope::LOCAL:
                return {isConstant, type, createAllocaInst(type)};
            default:
                LOG_ERROR("Unable to get variable because the scope type is unknown.");
                return {};
        }
    }

    // --------------------------------------------declare array--------------------------------------------

    bool declareArray(bool isConstant, llvm::Type* type, const std::string& id, llvm::Constant* initializer) {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().findSymbol(id)) {
            LOG_ERROR("Unable to declare ", scope, " array. ",
                      "Because its id (aka \"", id, "\") already exists in ", scope, " symbol table.");
            return false;
        }

        const auto array = getArray(isConstant, type, id, initializer);
        if (!Context::getInstance().insertSymbol(id, array)) {
            LOG_ERROR("Unable to declare ", scope, " array. ",
                      "Because it cannot be inserted into ", scope, " symbol table and its id is \"", id, "\".");
            return false;
        }

        return true;
    }
}