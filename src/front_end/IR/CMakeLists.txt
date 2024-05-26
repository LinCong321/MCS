find_package(LLVM REQUIRED CONFIG)

set(
        SOURCE_FILES
        context/context.cpp
        insertion_point/insertion_point.cpp
        loop_info/loop_info.cpp
        scope/scope.cpp
        symbol/symbol.cpp
        symbol_table/symbol_table.cpp
        type/type.cpp
)

include_directories(${IR_DIR})

add_library(ir ${SOURCE_FILES})

llvm_map_components_to_libnames(
        LLVM_LIBS
        ${LLVM_TARGETS_TO_BUILD}
        support
        core
        irreader
        passes
        codegen
        mc
        mcparser
        option
)

target_link_libraries(ir ${LLVM_LIBS} utils)