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
        bool isNode() const;
        Node* getNode() const;
        InitValList* getInitValList() const;

    private:
        void constFoldForNode();
        void constFoldForInitValList();

    private:
        std::variant<std::unique_ptr<Node>, std::unique_ptr<InitValList>> initVal_;
    };

    // ----------------------------------------------------------------------------------------------------

    class InitValList {
    public:
        InitValList() : initValList_() {}
        ~InitValList() = default;

    public:
        explicit InitValList(InitVal* initVal);

    public:
        void constFold();
        void pushBack(InitVal* initVal);
        void readEach(const std::function<void(const InitVal*)>& function) const;
        void readEach(const std::function<void(size_t, const InitVal*)>& function) const;

    private:
        std::vector<std::unique_ptr<InitVal>> initValList_;
    };
}