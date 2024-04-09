#pragma once

#include "var_def.h"
#include "IR/scope/scope.h"
#include "IR/symbol/symbol.h"

namespace mcs {
    class VarDefList : public Node{
    public:
        explicit VarDefList(VarDef* node);
        ~VarDefList() override = default;

    public:
        llvm::Value* codeGen() const override;

    public:
        void pushBack(VarDef* node);
        void setType(std::string* type);

    private:
        bool checkAllMemberPointers() const;
        bool declareVariable(const std::string& id, llvm::Value* value) const;
        llvm::Value* getLocalVariable(const std::string& id, llvm::Value* value) const;
        llvm::Value* getGlobalVariable(const std::string& id, llvm::Value* value) const;
        Symbol declareVariable(const std::string& id, llvm::Value* value, Scope scope) const;

    private:
        std::unique_ptr<std::string>         type_;
        std::vector<std::unique_ptr<VarDef>> defList_;
    };
}