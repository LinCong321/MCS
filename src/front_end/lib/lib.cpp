#include "lib.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "IR/context/context.h"
#include "builder/public/public.h"

namespace mcs {
    // int getint()
    static void addGetintPrototype() {
        std::vector<llvm::Type*> argTypes;
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::INT), argTypes, false);
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "getint", Context::getInstance().getModule());
    }
    
    // int getch()
    static void addGetchPrototype() {
        std::vector<llvm::Type*> argTypes;
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::INT), argTypes, false);
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "getch", Context::getInstance().getModule());
    }
    
    // int getarray(int a[])
    static void addGetarrayPrototype() {
        std::vector<llvm::Type*> argTypes{llvm::Type::getInt32PtrTy(Context::getInstance().getContext())};
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::INT), argTypes, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "getarray",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("a");
    }
    
    // float getfloat()
    static void addGetfloatPrototype() {
        std::vector<llvm::Type*> argTypes;
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::FLOAT), argTypes, false);
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "getfloat",
                               Context::getInstance().getModule());
    }
    
    // int getfarray(float a[])
    static void addGetfarrayPrototype() {
        std::vector<llvm::Type *> argTypes{llvm::Type::getFloatPtrTy(Context::getInstance().getContext())};
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::INT), argTypes, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "getfarray",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("a");
    }
    
    // void putint(int a)
    static void addPutintPrototype() {
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), {getLLVMType(Type::INT)}, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "putint",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("a");
    }
    
    // void putch(int a)
    static void addPutchPrototype() {
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), {getLLVMType(Type::INT)}, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "putch",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("a");
    }
    
    // void putarray(int n, int a[])
    static void addPutarrayPrototype() {
        std::vector<llvm::Type*> argTypes{getLLVMType(Type::INT),
                                          llvm::Type::getInt32PtrTy(Context::getInstance().getContext())};
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), argTypes, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "putarray",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("n");
        func->getArg(1)->setName("a");
    }
    
    // void putfloat(float a)
    static void addPutfloatPrototype() {
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), {getLLVMType(Type::FLOAT)}, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "putfloat",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("a");
    }
    
    // void putfarray(int n, float a[])
    static void addPutfarrayPrototype() {
        std::vector<llvm::Type*> argTypes{getLLVMType(Type::INT),
                                          llvm::Type::getFloatPtrTy(Context::getInstance().getContext())};
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), argTypes, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "putfarray",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("n");
        func->getArg(1)->setName("a");
    }
    
    // void _sysy_starttime(int lineno)
    static void addSysyStarttimePrototype() {
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), {getLLVMType(Type::INT)}, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "_sysy_starttime",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("lineno");
    }
    
    // void _sysy_stoptime(int lineno)
    static void addSysyStoptimePrototype() {
        const auto funcType = llvm::FunctionType::get(getLLVMType(Type::VOID), {getLLVMType(Type::INT)}, false);
        const auto func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "_sysy_stoptime",
                                                 Context::getInstance().getModule());
        func->getArg(0)->setName("lineno");
    }
    
    void addLibraryPrototype() {
        addGetintPrototype();
        addGetchPrototype();
        addGetarrayPrototype();
        addGetfloatPrototype();
        addGetfarrayPrototype();
        addPutintPrototype();
        addPutchPrototype();
        addPutarrayPrototype();
        addPutfloatPrototype();
        addPutfarrayPrototype();
        addSysyStarttimePrototype();
        addSysyStoptimePrototype();
    }
}