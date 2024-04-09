project(front_end)

include_directories(${FRONT_END_DIR})

add_subdirectory(analyzer)
add_subdirectory(AST)
add_subdirectory(code_gen)
add_subdirectory(IR)