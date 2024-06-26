#pragma once

#include "AST/comp_unit/comp_unit.h"

namespace mcs {
    class Start : public Node {
    public:
        explicit Start(CompUnit* compUnit) : compUnit_(compUnit) {}
        ~Start() override = default;

    public:
        llvm::Value* codeGen() const override;
        void constFold(std::unique_ptr<Node>& node) override;

    private:
        bool checkAllMemberPointers() const;
        static bool createLLVMGlobalCtors(llvm::Function* function);

    private:
        std::unique_ptr<Node> compUnit_;
    };
}