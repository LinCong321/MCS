set (
        SOURCE_FILES
        func/func.cpp
        pub/pub.cpp
        var/var.cpp
)

include_directories(${CODE_GEN_DIR})

add_library(code_gen ${SOURCE_FILES})

target_link_libraries(code_gen ir)