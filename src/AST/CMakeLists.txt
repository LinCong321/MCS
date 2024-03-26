set(
        SOURCE_FILES
        exp/exp.cpp
        stmt/stmt.cpp
        block/block.cpp
        func/func_def.cpp
        number/number.cpp
        ast_utils/utils.cpp
        comp_unit/comp_unit.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_include_directories(ast PRIVATE ${IR_DIR})

target_link_libraries(ast ir)