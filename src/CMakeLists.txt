project(src)

set(SRC_DIR ${PROJECT_SOURCE_DIR})
set(LAP_DIR ${SRC_DIR}/lexer_parser)

include_directories(${SRC_DIR})

add_executable(compiler main.cpp)

target_link_libraries(compiler lexer_parser)

add_subdirectory(AST)
add_subdirectory(IR)
add_subdirectory(lexer_parser)