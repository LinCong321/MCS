#include "IR/symbol_table/symbol_table.h"

namespace mcs {
    class CodeBlock {
    public:
        explicit CodeBlock(llvm::BasicBlock* basicBlock) : basicBlock_(basicBlock), symbolTable_(new SymbolTable()) {}
        ~CodeBlock() = default;

    public:
        void setBasicBlock(llvm::BasicBlock* basicBlock);
        bool insertSymbol(const std::string& name, const Symbol& symbol);

    public:
        llvm::Function* getFunction() const;
        llvm::BasicBlock* getBasicBlock() const;
        bool checkExist(const std::string& name) const;
        Symbol getSymbol(const std::string& name) const;

    private:
        llvm::BasicBlock*               basicBlock_;
        std::unique_ptr<SymbolTable>    symbolTable_;
    };
}
