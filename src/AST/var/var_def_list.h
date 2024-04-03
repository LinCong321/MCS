#pragma once

#include "var_def.h"

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
        llvm::Value* declareVariable(const std::string& id) const;
        llvm::Value* assign(llvm::Value* variable, llvm::Value* value) const;

    private:
        std::unique_ptr<std::string>         type_;
        std::vector<std::unique_ptr<VarDef>> defList_;
    };
}