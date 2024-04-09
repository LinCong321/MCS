#pragma once

#include "const_def.h"

namespace mcs {
    class ConstDefList : public Node {
    public:
        explicit ConstDefList(ConstDef* constDef);
        ~ConstDefList() override = default;

    public:
        llvm::Value* codeGen() const override;

    public:
        void setType(std::string* type);
        void pushBack(ConstDef* constDef);

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<std::string>            type_;
        std::vector<std::unique_ptr<ConstDef>>  defList_;
    };
}