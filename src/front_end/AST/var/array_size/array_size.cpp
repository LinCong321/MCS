#include "array_size.h"

namespace mcs {
    ArraySize::ArraySize(Node* node) {
        pushBack(node);
    }

    void ArraySize::pushBack(Node* node) {
        arraySize_.emplace_back(node);
    }
}