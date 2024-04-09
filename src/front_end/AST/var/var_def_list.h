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

    private:
        std::unique_ptr<std::string>         type_;
        std::vector<std::unique_ptr<VarDef>> defList_;
    };
}