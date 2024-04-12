set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        exp/binary_exp/binary_exp.cpp
        exp/unary_exp/unary_exp.cpp
        exp/var_exp/var_exp.cpp
        func/func_def.cpp
        lvalue/lvalue.cpp
        number/number.cpp
        start/start.cpp
        stmt/assign_stmt/assign_stmt.cpp
        stmt/block_stmt/block_stmt.cpp
        stmt/if_else_stmt/if_else_stmt.cpp
        stmt/null_stmt/null_stmt.cpp
        stmt/ret_stmt/ret_stmt.cpp
        var/var_def.cpp
        var/var_def_list.cpp
)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_link_libraries(ast builder)