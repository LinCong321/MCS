find_package(FLEX)
find_package(BISON)

set(LEXER_L     ${ANALYZER_DIR}/lexer/lexer.l)
set(LEXER_CPP   ${ANALYZER_DIR}/lexer/lexer.cpp)
set(PARSER_Y    ${ANALYZER_DIR}/parser/parser.y)
set(PARSER_CPP  ${ANALYZER_DIR}/parser/parser.cpp)
set(
        SOURCE_FILES
        ${LEXER_CPP}
        ${PARSER_CPP}
)

include_directories(${ANALYZER_DIR})

flex_target(lexer ${LEXER_L} ${LEXER_CPP})
bison_target(parser ${PARSER_Y} ${PARSER_CPP} COMPILE_FLAGS -d)
add_flex_bison_dependency(lexer parser)

add_library(analyzer ${SOURCE_FILES})

target_link_libraries(analyzer ast)