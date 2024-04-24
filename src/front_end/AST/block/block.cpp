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
                LOG_WARN("Since the function has returned, all subsequent items in the block are discarded.");
                return nullptr;
            }
            item->codeGen();
        }
        return nullptr;
    }

    void BlockItem::constFold(std::unique_ptr<Node>&) {
        for (auto& item : items_) {
            if (item != nullptr) {
                item->constFold(item);
            }
        }
    }

    void BlockItem::pushBack(Node* node) {
        items_.emplace_back(node);
    }
}