set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        exp/binary_exp.cpp
        exp/unary_exp.cpp
        func/func_def.cpp
        lval/lval.cpp
        number/number.cpp
        start/start.cpp
        stmt/block_stmt.cpp
        stmt/ret_stmt.cpp
        stmt/stmt.cpp
        var/var_def.cpp
        var/var_def_list.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_link_libraries(ast code_gen)