set(
        SOURCE_FILES
        ast_utils/utils.cpp
        block/block.cpp
        comp_unit/comp_unit.cpp
        func/func_def.cpp
        stmt/stmt.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_include_directories(ast PRIVATE ${IR_DIR})

target_link_libraries(ast ir)