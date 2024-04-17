#include "insertion_point.h"

#include "utils/logger.h"
#include "llvm/IR/Function.h"

namespace mcs {
    void InsertionPoint::clearFunction() {
        function_ = nullptr;
    }

    bool InsertionPoint::clearBlock(mcs::Scope scope) {
        return resetBlock(nullptr, scope);
    }

    bool InsertionPoint::setBlock(llvm::BasicBlock* basicBlock, Scope scope) {
        switch (scope) {
            case Scope::GLOBAL:
                globalBlock_ = basicBlock;
                return true;
            case Scope::LOCAL:
                localBlock_ = basicBlock;
                return setFunction(basicBlock);
            default:
                LOG_ERROR("Unable to set block because scope is unknown.");
                return false;
        }
    }

    bool InsertionPoint::insertBlock(llvm::BasicBlock* basicBlock, Scope scope) {
        const auto function = getFunction(scope);
        if (function == nullptr) {
            LOG_ERROR("Unable to insert block because function is nullptr.");
            return false;
        }
        function->insert(function->end(), basicBlock);
        return resetBlock(basicBlock, scope);
    }

    llvm::BasicBlock* InsertionPoint::getBlock(Scope scope) const {
        switch (scope) {
            case Scope::GLOBAL:
                return globalBlock_;
            case Scope::LOCAL:
                return localBlock_;
            default:
                LOG_ERROR("Unable to get block because scope is unknown.");
                return nullptr;
        }
    }

    std::string InsertionPoint::getFunctionName(Scope scope) const {
        const auto function = getFunction(scope);
        if (function == nullptr) {
            LOG_ERROR("Unable to get function name because function is nullptr.");
            return {};
        }
        return function->getName().str();
    }

    llvm::Type* InsertionPoint::getFunctionReturnType(Scope scope) const {
        const auto function = getFunction(scope);
        if (function == nullptr) {
            LOG_ERROR("Unable to get function return type because function is nullptr.");
            return nullptr;
        }
        return function->getReturnType();
    }

    llvm::Function* InsertionPoint::getGlobalFunction() const {
        if (globalBlock_ == nullptr) {
            LOG_ERROR("Unable to get global function because globalBlock_ is nullptr.");
            return nullptr;
        }
        return globalBlock_->getParent();
    }

    llvm::Function* InsertionPoint::getFunction(Scope scope) const {
        switch (scope) {
            case Scope::GLOBAL:
                return getGlobalFunction();
            case Scope::LOCAL:
                return function_;
            default:
                LOG_ERROR("Unable to get function because scope is unknown.");
                return nullptr;
        }
    }

    bool InsertionPoint::setFunction(llvm::BasicBlock* basicBlock) {
        if (basicBlock == nullptr) {
            LOG_ERROR("Unable to set function because basicBlock is nullptr.");
            return false;
        }
        function_ = basicBlock->getParent();
        return true;
    }

    bool InsertionPoint::resetBlock(llvm::BasicBlock* basicBlock, Scope scope) {
        switch (scope) {
            case Scope::GLOBAL:
                globalBlock_ = basicBlock;
                return true;
            case Scope::LOCAL:
                localBlock_ = basicBlock;
                return true;
            default:
                LOG_ERROR("Unable to reset block because scope is unknown.");
                return false;
        }
    }
}