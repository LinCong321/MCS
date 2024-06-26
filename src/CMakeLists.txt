project(src)

set(SRC_DIR         ${PROJECT_SOURCE_DIR})
set(FRONT_END_DIR   ${SRC_DIR}/front_end)
set(MIDDLE_END_DIR  ${SRC_DIR}/middle_end)
set(BACK_END_DIR    ${SRC_DIR}/back_end)
set(UTILS_DIR       ${SRC_DIR}/utils)

set(ANALYZER_DIR    ${FRONT_END_DIR}/analyzer)
set(AST_DIR         ${FRONT_END_DIR}/AST)
set(BUILDER_DIR     ${FRONT_END_DIR}/builder)
set(IR_DIR          ${FRONT_END_DIR}/IR)
set(LIB_DIR         ${FRONT_END_DIR}/lib)

include_directories(${SRC_DIR})

add_executable(compiler main.cpp)

target_include_directories(compiler PRIVATE ${FRONT_END_DIR})

target_link_libraries(compiler analyzer middle_end back_end)

add_subdirectory(front_end)
add_subdirectory(middle_end)
add_subdirectory(back_end)
add_subdirectory(utils)