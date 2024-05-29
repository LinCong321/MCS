#include "var_def.h"
#include "utils/logger.h"
#include "number/number.h"
#include "IR/context/context.h"
#include "builder/public/public.h"
#include "builder/memory/memory.h"
#include "builder/variable/variable.h"
#include "builder/constant/constant.h"
#include "number/constant_table/constant_table.h"

namespace mcs {
    void VarDef::constFold(bool isConstant, const std::string& type) {
        constFold();
        if (isConstant && !isArray()) {
            ConstantTable::getInstance().insert(getId(), getNumber(getNode(), type));
        }
    }

    bool VarDef::declare(bool isConstant, const std::string& type) const {
//        if (isArray()) {
//            return declare(isConstant, getLLVMType(type, getArraySize()));
//        } else {
//            return declareVariable(isConstant, type, getId(), getValue());
//        }
        return isConstant ? constDecl(type) : varDecl(type);
    }

    void VarDef::constFold() {
        if (isArray() && arraySize_.value() != nullptr) {
            arraySize_.value()->constFold();
        }
        if (initVal_ != nullptr) {
            initVal_->constFold();
        }
    }

    bool VarDef::isArray() const {
        return arraySize_.has_value();
    }

    bool VarDef::initialize(llvm::Type* type) const {
        if (initVal_ == nullptr) {
            if (Context::getInstance().getCurrentScope() == Scope::LOCAL) {
                LOG_WARN("The local variable \"", getId(), "\" is not assigned an initial value.");
            }
            return true;
        }

        if (!isArray()) {
            createStoreInst(getCastedValue(getValue(), type), getId());
            return true;
        }

        std::vector<size_t> index;
        return initializeArray(type, index, initVal_.get());
    }

    bool VarDef::declare(bool isConstant, llvm::Type* type) const {
        if (isConstant) {
            return declareArray(isConstant, type, getId(), getInitializer(type, initVal_.get()));
        } else {
            return declareArray(isConstant, type, getId()) && initialize(type);
        }
    }

    Node* VarDef::getNode() const {
        return initVal_ != nullptr ? initVal_->getNode() : nullptr;
    }

    std::string VarDef::getId() const {
        if (id_ == nullptr) {
            LOG_ERROR("Unable to get ID because id_ is nullptr.");
            return {};
        }
        return *id_;
    }

    llvm::Value* VarDef::getValue() const {
        const auto node = getNode();
        if (node == nullptr) {
            return nullptr;
        }
        return node->codeGen();
    }

    std::vector<int> VarDef::getArraySize() const {
        std::vector<int> size;

        if (isArray() && arraySize_.value() != nullptr) {
            arraySize_.value()->readEach([&size](Node& node) {
                size.emplace_back(getValueOfIntNum(&node));
            });
        }

        return std::move(size);
    }

    bool VarDef::varDecl(const std::string& str) const {
        if (Context::getInstance().getCurrentScope() == Scope::LOCAL) {
            const auto type = isArray() ? getLLVMType(str, getArraySize()) : getLLVMType(str);
            const auto var = createAllocaInst(type);
            Context::getInstance().insertSymbol(getId(), Symbol(false, type, var));
            return initialize(type);
        }

        const auto type = isArray() ? getLLVMType(str, getArraySize()) : getLLVMType(str);
        const auto var = new llvm::GlobalVariable(Context::getInstance().getModule(), type, true,
                                                  llvm::GlobalValue::LinkageTypes::InternalLinkage,
                                                  getNullValue(type), getId());

        Context::getInstance().insertSymbol(getId(), Symbol(false, type, var));
        return initialize(type);
    }

    bool VarDef::constDecl(const std::string& str) const {
        if (Context::getInstance().getCurrentScope() == Scope::LOCAL) {
            const auto type = isArray() ? getLLVMType(str, getArraySize()) : getLLVMType(str);
            const auto var = createAllocaInst(type);
            Context::getInstance().insertSymbol(getId(), Symbol(true, type, var));
            return true;
        }

        const auto type = isArray() ? getLLVMType(str, getArraySize()) : getLLVMType(str);
        const auto var = new llvm::GlobalVariable(Context::getInstance().getModule(), type, true,
                                                  llvm::GlobalValue::LinkageTypes::InternalLinkage,
                                                  getInitializer(type, initVal_.get()), getId());

        Context::getInstance().insertSymbol(getId(), Symbol(false, type, var));
        return true;
    }

    llvm::Constant* VarDef::getInitializer(llvm::Type* type, const Node* node) {
        if (node == nullptr) {
            LOG_ERROR("Unable to get initializer because node is nullptr.");
            return nullptr;
        }
        return llvm::cast<llvm::Constant>(node->codeGen());
    }

    llvm::Constant* VarDef::getInitializer(llvm::Type* type, const InitVal* initVal) {
        if (initVal == nullptr) {
            LOG_ERROR("Unable to get initializer because initVal is nullptr.");
            return nullptr;
        }
        return initVal->isNode() ? getInitializer(type, initVal->getNode())
                                 : getInitializer(type, initVal->getInitValList());
    }

    llvm::Constant* VarDef::getInitializer(llvm::Type* type, const InitValList* initValList) {
        std::vector<llvm::Constant*> initializer;

        if (type == nullptr || initValList == nullptr) {
            LOG_ERROR("Unable to initialize array because type is nullptr or initValList is nullptr.");
            return nullptr;
        }

        const auto arrayElementType = type->getArrayElementType();
        initValList->readEach([&](const InitVal* initVal) {
            initializer.emplace_back(getInitializer(arrayElementType, initVal));
        });

        return getConstantArray(std::move(initializer), type);
    }

    bool VarDef::initializeArray(llvm::Type* type, std::vector<size_t>& index, const Node* node) const {
        if (node == nullptr) {
            LOG_ERROR("Unable to initialize array because node is nullptr.");
            return false;
        }
        return createStoreInst(getCastedValue(node->codeGen(), type), createGetElementPtrInst(getId(), index));
    }

    bool VarDef::initializeArray(llvm::Type* type, std::vector<size_t>& index, const InitVal* initVal) const {
        if (initVal == nullptr) {
            LOG_ERROR("Unable to initialize array because initVal is nullptr.");
            return false;
        }
        return initVal->isNode() ? initializeArray(type, index, initVal->getNode())
                                 : initializeArray(type, index, initVal->getInitValList());
    }

    bool VarDef::initializeArray(llvm::Type* type, std::vector<size_t>& index, const InitValList* initValList) const {
        if (type == nullptr || initValList == nullptr) {
            LOG_ERROR("Unable to initialize array because type is nullptr or initValList is nullptr.");
            return false;
        }

        const auto arrayElementType = type->getArrayElementType();
        initValList->readEach([&](size_t pos, const InitVal* initVal) {
            index.emplace_back(pos);
            initializeArray(arrayElementType, index, initVal);
            index.pop_back();
        });

        return true;
    }
}