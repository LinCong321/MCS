project(src)

set(SRC_DIR         ${PROJECT_SOURCE_DIR})
set(FRONT_END_DIR   ${SRC_DIR}/front_end)
set(UTILS_DIR       ${SRC_DIR}/utils)

set(ANALYZER_DIR    ${FRONT_END_DIR}/analyzer)
set(AST_DIR         ${FRONT_END_DIR}/AST)
set(BUILDER_DIR     ${FRONT_END_DIR}/builder)
set(IR_DIR          ${FRONT_END_DIR}/IR)

include_directories(${SRC_DIR})

add_executable(compiler main.cpp)

target_include_directories(compiler PRIVATE ${FRONT_END_DIR})

target_link_libraries(compiler analyzer)

add_subdirectory(front_end)
add_subdirectory(utils)