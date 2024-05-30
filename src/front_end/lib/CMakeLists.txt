set (
        SOURCE_FILES
        lib.cpp
)

include_directories(${LIB_DIR})

add_library(lib ${SOURCE_FILES})

target_link_libraries(lib ir)