set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        exp/binary_exp.cpp
        func/func_def.cpp
        number/number.cpp
        stmt/stmt.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_include_directories(ast PRIVATE ${IR_DIR})

target_link_libraries(ast ir)