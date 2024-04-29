#include "init_val.h"

namespace mcs {
    void InitVal::constFold() {
        isNode() ? constFoldForNode() : constFoldForInitValList();
    }

    bool InitVal::isNode() const {
        return std::holds_alternative<std::unique_ptr<Node>>(initVal_);
    }

    Node* InitVal::getNode() const {
        return std::get<std::unique_ptr<Node>>(initVal_).get();
    }

    InitValList* InitVal::getInitValList() const {
        return std::get<std::unique_ptr<InitValList>>(initVal_).get();
    }

    void InitVal::constFoldForNode() {
        auto& initVal = std::get<std::unique_ptr<Node>>(initVal_);
        if (initVal != nullptr) {
            initVal->constFold(initVal);
        }
    }

    void InitVal::constFoldForInitValList() {
        auto& initVal = std::get<std::unique_ptr<InitValList>>(initVal_);
        if (initVal != nullptr) {
            initVal->constFold();
        }
    }

    // ----------------------------------------------------------------------------------------------------

    InitValList::InitValList(InitVal* initVal) : initValList_() {
        pushBack(initVal);
    }

    void InitValList::constFold() {
        for (const auto& initVal : initValList_) {
            if (initVal != nullptr) {
                initVal->constFold();
            }
        }
    }

    void InitValList::pushBack(InitVal* initVal) {
        initValList_.emplace_back(initVal);
    }

    void InitValList::readEach(const std::function<void(const InitVal*)>& function) const {
        for (const auto& initVal : initValList_) {
            function(initVal.get());
        }
    }

    void InitValList::readEach(const std::function<void(size_t, const InitVal*)>& function) const {
        for (size_t pos = 0; pos < initValList_.size(); pos++) {
            function(pos, initValList_[pos].get());
        }
    }
}