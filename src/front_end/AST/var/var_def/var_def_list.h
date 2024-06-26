#pragma once

#include "var_def.h"
#include "IR/scope/scope.h"
#include "IR/symbol/symbol.h"

namespace mcs {
    class VarDefList : public Node {
    public:
        explicit VarDefList(VarDef* varDef);
        ~VarDefList() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    public:
        void pushBack(VarDef* varDef);
        void setAttribute(std::string* type, bool isConstant = false);

    private:
        bool checkAllMemberPointers() const;

    private:
        bool isConstant_;
        std::unique_ptr<std::string> type_;
        std::vector<std::unique_ptr<VarDef>> defList_;
    };
}