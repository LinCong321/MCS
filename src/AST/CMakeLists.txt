set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        func/func_def.cpp
        pub/utils.cpp
        stmt/stmt.cpp
)

add_library(AST ${SOURCE_FILES})

target_link_libraries(AST IR)