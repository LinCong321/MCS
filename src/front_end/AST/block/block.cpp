#include "block.h"
#include "utils/logger.h"
#include "IR/context/context.h"

namespace mcs {
    BlockItem::BlockItem(Node* node) : items_() {
        pushBack(node);
    }

    llvm::Value* BlockItem::codeGen() const {
        for (const auto& item : items_) {
            if (item == nullptr) {
                LOG_ERROR("Unable to generate code because there is a nullptr in items_.");
                return nullptr;
            }
            if (Context::getInstance().getInsertBlock() == nullptr) {
                LOG_WARN("This item is discarded because the function has returned.");
                continue;
            }
            item->codeGen();
        }
        return nullptr;
    }

    void BlockItem::pushBack(Node* node) {
        items_.emplace_back(node);
    }
}