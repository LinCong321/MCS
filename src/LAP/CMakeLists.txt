find_package(FLEX)
find_package(BISON)

set(LEXER_L     ${LAP_DIR}/lexer/lexer.l)
set(LEXER_CPP   ${LAP_DIR}/lexer/lexer.cpp)
set(PARSER_Y    ${LAP_DIR}/parser/parser.y)
set(PARSER_CPP  ${LAP_DIR}/parser/parser.cpp)
set(
        SOURCE_FILES
        ${LEXER_CPP}
        ${PARSER_CPP}
)

include_directories(${LAP_DIR})

flex_target(lexer ${LEXER_L} ${LEXER_CPP})
bison_target(parser ${PARSER_Y} ${PARSER_CPP} COMPILE_FLAGS -d)
add_flex_bison_dependency(lexer parser)

add_library(lexer_parser ${SOURCE_FILES})

target_include_directories(lexer_parser PRIVATE ${AST_DIR})

target_link_libraries(lexer_parser ast)