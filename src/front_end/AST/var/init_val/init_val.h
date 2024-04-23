#pragma once

#include "AST/node/node.h"

namespace mcs {
    class InitValList;

    class InitVal {
    public:
        InitVal() : initVal_(std::make_unique<InitValList>()) {}
        ~InitVal() = default;

    public:
        explicit InitVal(Node* initVal) : initVal_(std::unique_ptr<Node>(initVal)) {}
        explicit InitVal(InitValList* initVal) : initVal_(std::unique_ptr<InitValList>(initVal)) {}

    public:
        void constFold();
        Node* getValue() const;

    private:
        std::variant<std::unique_ptr<Node>, std::unique_ptr<InitValList>> initVal_;
    };

    class InitValList {
    public:
        InitValList() : initValList_() {}
        ~InitValList() = default;

    public:
        explicit InitValList(InitVal* initVal);

    public:
        void pushBack(InitVal* initVal);

    private:
        std::vector<std::unique_ptr<InitVal>> initValList_;
    };
}