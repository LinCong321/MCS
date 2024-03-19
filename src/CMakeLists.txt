project(src)

set(SRC_DIR ${PROJECT_SOURCE_DIR})
set(AST_DIR ${SRC_DIR}/AST)
set(IR_DIR  ${SRC_DIR}/IR)
set(LAP_DIR ${SRC_DIR}/LAP)

include_directories(${SRC_DIR})

add_executable(compiler main.cpp)

target_include_directories(compiler PRIVATE ${AST_DIR} ${IR_DIR})

target_link_libraries(compiler lexer_parser)

add_subdirectory(AST)
add_subdirectory(IR)
add_subdirectory(LAP)