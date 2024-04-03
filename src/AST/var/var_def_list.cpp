#include "var_def_list.h"

#include "utils/logger.h"
#include "IR/context/context.h"
#include "pub/code_gen_helper.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"

namespace mcs {
    VarDefList::VarDefList(VarDef* varDef) {
        pushBack(varDef);
    }

    llvm::Value* VarDefList::codeGen() const {
        if (!checkAllMemberPointers()) {
            LOG_ERROR("Unable to generate code because there is a nullptr in member pointers.");
            return nullptr;
        }

        for (const auto& def : defList_) {
            if (def == nullptr) {
                LOG_ERROR("Unable to generate code because there is a nullptr in defList_.");
                return nullptr;
            }
            const auto result = declareVariable(def->getId(), def->getValue());
            if (result == nullptr) {
                LOG_ERROR("Unable to generate code because the variable cannot be declared.");
                return nullptr;
            }
        }

        return nullptr;
    }

    void VarDefList::pushBack(VarDef* varDef) {
        defList_.emplace_back(varDef);
    }

    void VarDefList::setType(std::string* type) {
        type_ = std::unique_ptr<std::string>(type);
    }

    bool VarDefList::checkAllMemberPointers() const {
        if (type_ == nullptr) {
            LOG_ERROR("type_ is nullptr.");
            return false;
        }
        return true;
    }

    llvm::Value* VarDefList::declareVariable(const std::string& id, llvm::Value* value) const {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().checkSymbol(id)) {
            LOG_ERROR("The ", scope, " variable cannot be declared because its id (aka \"", id,
                      "\") already exists in the ", scope, " symbol table.");
            return nullptr;
        }

        const auto variable = declareVariable(id, value, scope);
        if (!Context::getInstance().insertSymbol(id, variable)) {
            LOG_ERROR("The ", scope, " variable cannot be declared because it cannot be inserted into the ", scope,
                      " symbol table and its id is \"", id, "\".");
            return nullptr;
        }

        return variable;
    }

    llvm::Value* VarDefList::declareLocalVariable(const std::string& id, llvm::Value* value) const {
        const auto variable = new llvm::AllocaInst(getLLVMType(*type_), 0, id,
                                                   Context::getInstance().getCurrentBlock());
        new llvm::StoreInst(getCastedValue(value, *type_), variable, false, Context::getInstance().getCurrentBlock());
        return variable;
    }

    llvm::Value* VarDefList::declareGlobalVariable(const std::string& id, llvm::Value* value) const {
        return new llvm::GlobalVariable(Context::getInstance().getModule(), getLLVMType(*type_), false,
                                        llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                        getConstantValue(value, *type_), id);
    }

    llvm::Value* VarDefList::declareVariable(const std::string& id, llvm::Value* value, Scope scope) const {
        switch (scope) {
            case Scope::GLOBAL:
                return declareGlobalVariable(id, value);
            case Scope::LOCAL:
                return declareLocalVariable(id, value);
            default:
                LOG_ERROR("Unable to declare variable because the scope type is unknown.");
                return nullptr;
        }
    }
}