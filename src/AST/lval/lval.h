#pragma once

#include "pub/node.h"

namespace mcs {
    class LVal : public Node {
    public:
        explicit LVal(std::string* id) : id_(id) {}
        ~LVal() override = default;

    public:
        llvm::Value* codeGen() const override;

    private:
        bool checkAllMemberPointers() const;

    private:
        std::unique_ptr<std::string> id_;
    };
}