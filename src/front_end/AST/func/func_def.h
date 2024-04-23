#pragma once

#include "func_params.h"
#include "AST/node/node.h"
#include "IR/symbol/symbol.h"

namespace mcs {
    class FuncDef : public Node {
    public:
        FuncDef(std::string* retType, std::string* name, Node* block)
            : retType_(retType), name_(name), funcParams_(nullptr), block_(block) {}

        FuncDef(std::string* retType, std::string* name, FuncParams* funcParams, Node* block)
            : retType_(retType), name_(name), funcParams_(funcParams), block_(block) {}

        ~FuncDef() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        bool checkAllMemberPointers() const;
        std::vector<Symbol> getParams() const;

    private:
        std::unique_ptr<std::string>    retType_;
        std::unique_ptr<std::string>    name_;
        std::unique_ptr<FuncParams>     funcParams_;
        std::unique_ptr<Node>           block_;
    };
}