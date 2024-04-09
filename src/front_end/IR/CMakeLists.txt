find_package(LLVM REQUIRED CONFIG)

set(
        SOURCE_FILES
        code_block/code_block.cpp
        context/context.cpp
        scope/scope.cpp
        symbol/symbol.cpp
        symbol_table/symbol_table.cpp
        type/type.cpp
)

include_directories(${IR_DIR})

add_library(ir ${SOURCE_FILES})

target_include_directories(ir PRIVATE ${LLVM_INCLUDE_DIRS})

llvm_map_components_to_libnames(
        LLVM_LIBS
        support
        core
        irreader
)

target_link_libraries(ir ${LLVM_LIBS} utils)