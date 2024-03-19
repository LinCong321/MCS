set(SOURCE_FILES node.cpp)

add_library(AST ${SOURCE_FILES})

target_link_libraries(AST IR)