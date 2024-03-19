find_package(FLEX)
find_package(BISON)

include_directories(${LAP_DIR})

flex_target(lexer lexer/lexer.l ${LAP_DIR}/lexer/lexer.cpp)
bison_target(parser parser/parser.y ${LAP_DIR}/parser/parser.cpp COMPILE_FLAGS "-d")
add_flex_bison_dependency(lexer parser)

add_library(lexer_parser ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})

target_include_directories(lexer_parser PRIVATE ${AST_DIR})

target_link_libraries(lexer_parser ast)