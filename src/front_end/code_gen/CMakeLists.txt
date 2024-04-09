set (
        SOURCE_FILES
        func/func.cpp
        pub/pub.cpp
)

include_directories(${CODE_GEN_DIR})

add_library(code_gen ${SOURCE_FILES})

target_include_directories(code_gen PRIVATE ${IR_DIR})

target_link_libraries(code_gen ir)