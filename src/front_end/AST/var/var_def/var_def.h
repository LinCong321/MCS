#pragma once

#include "AST/var/init_val/init_val.h"
#include "AST/var/array_size/array_size.h"

namespace mcs {
    class VarDef {
    public:
        explicit VarDef(std::string* id, InitVal* initVal = nullptr)
            : id_(id), arraySize_(nullptr), initVal_(initVal) {}

        VarDef(std::string* id, ArraySize* arraySize, InitVal* initVal = nullptr)
            : id_(id), arraySize_(arraySize), initVal_(initVal) {}

        ~VarDef() = default;

    public:
        std::string getId() const;
        llvm::Value* getValue() const;
        void constFold(const std::string& type);

    private:
        std::unique_ptr<std::string>    id_;
        std::unique_ptr<ArraySize>      arraySize_;
        std::unique_ptr<InitVal>        initVal_;
    };
}