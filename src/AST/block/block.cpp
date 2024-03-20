#include "block.h"
#include "utils/logger.h"

namespace mcs {
    BlockItem::BlockItem(Node* node) : items_() {
        pushBack(node);
    }

    llvm::Value* BlockItem::codeGen() {
        for (const auto& item : items_) {
            if (item == nullptr) {
                LOG_ERROR("There is a nullptr in items_");
                return nullptr;
            }
            item->codeGen();
        }
        return nullptr;
    }

    void BlockItem::pushBack(Node* node) {
        items_.push_back(std::unique_ptr<Node>(node));
    }
}