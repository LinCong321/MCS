set(
        SOURCE_FILES
        block/block.cpp
        comp_unit/comp_unit.cpp
        exp/arith_exp/arith_exp.cpp
        exp/func_args_exp/func_args_exp.cpp
        exp/func_call_exp/func_call_exp.cpp
        exp/logic_exp/logic_exp.cpp
        exp/rel_exp/rel_exp.cpp
        exp/unary_exp/unary_exp.cpp
        exp/var_exp/var_exp.cpp
        func/func_def.cpp
        func/func_params.cpp
        lvalue/lvalue.cpp
        number/constant_table/constant_table.cpp
        number/float_num/float_num.cpp
        number/int_num/int_num.cpp
        number/number.cpp
        start/start.cpp
        stmt/assign_stmt/assign_stmt.cpp
        stmt/block_stmt/block_stmt.cpp
        stmt/break_stmt/break_stmt.cpp
        stmt/continue_stmt/continue_stmt.cpp
        stmt/if_else_stmt/if_else_stmt.cpp
        stmt/null_stmt/null_stmt.cpp
        stmt/ret_stmt/ret_stmt.cpp
        stmt/while_stmt/while_stmt.cpp
        var/array_size/array_size.cpp
        var/init_val/init_val.cpp
        var/var_def/var_def.cpp
        var/var_def/var_def_list.cpp

)

include_directories(${AST_DIR})

add_library(ast ${SOURCE_FILES})

target_link_libraries(ast builder)