find_package(FLEX)
find_package(BISON)

flex_target(lexer lexer.l ${LAP_DIR}/lexer.cpp)
bison_target(parser parser.y ${LAP_DIR}/parser.cpp COMPILE_FLAGS "-d")
add_flex_bison_dependency(lexer parser)

add_library(lexer_parser ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})

target_link_libraries(lexer_parser AST)