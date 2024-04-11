project(front_end)

include_directories(${FRONT_END_DIR})

add_subdirectory(analyzer)
add_subdirectory(AST)
add_subdirectory(builder)
add_subdirectory(IR)