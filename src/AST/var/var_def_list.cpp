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
        switch (Context::getInstance().getCurrentScope()) {
            case Scope::GLOBAL:
                return declareGlobalVariable(id, value);
            case Scope::LOCAL:
                return declareLocalVariable(id, value);
            default:
                LOG_ERROR("Unable to declare variable because the scope type is unknown.");
                return nullptr;
        }
    }

    llvm::Value* VarDefList::declareLocalVariable(const std::string& id, llvm::Value* value) const {
        if (Context::getInstance().checkSymbol(id, Scope::LOCAL)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id, "\") already exists in local symbol table.");
            return nullptr;
        }

        const auto variable = new llvm::AllocaInst(getLLVMType(*type_), 0, id,
                                                   Context::getInstance().getCurrentBlock());

        if (!Context::getInstance().insertSymbol(id, variable, Scope::LOCAL)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id,
                      "\") cannot be inserted into local symbol table.");
            return nullptr;
        }

        return new llvm::StoreInst(value, variable, false, Context::getInstance().getCurrentBlock());
    }

    llvm::Value* VarDefList::declareGlobalVariable(const std::string& id, llvm::Value* value) const {
        if (Context::getInstance().checkSymbol(id, Scope::GLOBAL)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id,
                      "\") already exists in global symbol table.");
            return nullptr;
        }

        const auto variable = new llvm::GlobalVariable(Context::getInstance().getModule(), getLLVMType(*type_),
                                                       false, llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                                       getConstantValue(value, *type_), id);

        if (!Context::getInstance().insertSymbol(id, variable, Scope::GLOBAL)) {
            LOG_ERROR("Unable to declare variable because id (aka \"", id,
                      "\") cannot be inserted into global symbol table.");
            return nullptr;
        }

        return variable;
    }
}