#pragma once

#include "IR/symbol/symbol.h"
#include "AST/var/init_val/init_val.h"
#include "AST/var/array_size/array_size.h"

namespace mcs {
    class VarDef {
    public:
        explicit VarDef(std::string* id, InitVal* initVal = nullptr)
            : id_(id), arraySize_(), initVal_(initVal) {}

        VarDef(std::string* id, ArraySize* arraySize, InitVal* initVal = nullptr)
            : id_(id), arraySize_(arraySize), initVal_(initVal) {}

        ~VarDef() = default;

    public:
        void constFold(bool isConstant, const std::string& type);
        bool declare(bool isConstant, const std::string& str) const;

    private:
        void constFold();
        bool isArray() const;
        Node* getNode() const;
        std::string getId() const;
        llvm::Value* getValue() const;
        std::vector<int> getArraySize() const;

    private:
        static llvm::Constant* getInitializer(llvm::Type* type, const Node* node);
        static llvm::Constant* getInitializer(llvm::Type* type, const InitVal* initVal);
        static llvm::Constant* getInitializer(llvm::Type* type, const InitValList* initValList);

    private:
        bool initializeArray(llvm::Type* type) const;
        bool initializeArray(llvm::Type* type, std::vector<size_t>& index, const Node* node) const;
        bool initializeArray(llvm::Type* type, std::vector<size_t>& index, const InitVal* initVal) const;
        bool initializeArray(llvm::Type* type, std::vector<size_t>& index, const InitValList* initValList) const;

    private:
        std::unique_ptr<std::string>                id_;
        std::optional<std::unique_ptr<ArraySize>>   arraySize_;
        std::unique_ptr<InitVal>                    initVal_;
    };
}