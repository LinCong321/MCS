set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        exp/binary_exp/binary_exp.cpp
        exp/unary_exp/unary_exp.cpp
        func/func_def.cpp
        lval/lval.cpp
        number/number.cpp
        start/start.cpp
        stmt/stmt.cpp
        stmts/block_stmt/block_stmt.cpp
        stmts/ret_stmt/ret_stmt.cpp
        var/var_def.cpp
        var/var_def_list.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_link_libraries(ast builder)