#include "init_val.h"

namespace mcs {
    void InitVal::constFold() {
        auto& initVal = std::get<std::unique_ptr<Node>>(initVal_);
        if (initVal != nullptr) {
            initVal->constFold(initVal);
        }
    }

    Node* InitVal::getValue() const {
        return std::get<std::unique_ptr<Node>>(initVal_).get();
    }

    InitValList::InitValList(InitVal* initVal) : initValList_() {
        pushBack(initVal);
    }

    void InitValList::pushBack(InitVal* initVal) {
        initValList_.emplace_back(initVal);
    }
}