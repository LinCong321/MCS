#include "var_def_list.h"
#include "utils/logger.h"
#include "IR/context/context.h"
#include "code_gen/pub/pub.h"

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
            if (!declareVariable(def->getId(), def->getValue())) {
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

    llvm::Value* VarDefList::getLocalVariable(const std::string& id, llvm::Value* value) const {
        const auto variable = new llvm::AllocaInst(getLLVMType(*type_), 0, "",
                                                   Context::getInstance().getCurrentBlock());

        if (value == nullptr) {
            LOG_WARN("The local variable \"", id, "\" has no initial value assigned.");
        } else {
            new llvm::StoreInst(getCastedValue(value, *type_), variable, false,
                                Context::getInstance().getCurrentBlock());
        }

        return variable;
    }

    bool VarDefList::declareVariable(const std::string& id, llvm::Value* value) const {
        const auto scope = Context::getInstance().getCurrentScope();
        if (Context::getInstance().checkSymbol(id)) {
            LOG_ERROR("The ", scope, " variable cannot be declared. Because its id (aka \"", id,
                      "\") already exists in the ", scope, " symbol table.");
            return false;
        }

        const auto variable = declareVariable(id, value, scope);
        if (!Context::getInstance().insertSymbol(id, variable)) {
            LOG_ERROR("The ", scope, " variable cannot be declared. Because it cannot be inserted into the ", scope,
                      " symbol table and its id is \"", id, "\".");
            return false;
        }

        return true;
    }

    Symbol VarDefList::declareVariable(const std::string& id, llvm::Value* value, Scope scope) const {
        switch (scope) {
            case Scope::GLOBAL:
                return Symbol(getLLVMType(*type_), getGlobalVariable(id, value));
            case Scope::LOCAL:
                return Symbol(getLLVMType(*type_), getLocalVariable(id, value));
            default:
                LOG_ERROR("Unable to declare variable because the scope type is unknown.");
                return Symbol();
        }
    }

    llvm::Value* VarDefList::getGlobalVariable(const std::string& id, llvm::Value* value) const {
        const auto variable = new llvm::GlobalVariable(Context::getInstance().getModule(), getLLVMType(*type_), false,
                                                       llvm::GlobalVariable::LinkageTypes::InternalLinkage,
                                                       getConstantValue(value, *type_), id);
        if (value != nullptr && !llvm::isa<llvm::Constant>(value)) {
            new llvm::StoreInst(getCastedValue(value, *type_), variable, false,
                                Context::getInstance().getCurrentBlock());
        }
        return variable;
    }
}