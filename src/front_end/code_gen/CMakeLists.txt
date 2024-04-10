set (
        SOURCE_FILES
        function/function.cpp
        public/public.cpp
        variable/variable.cpp
)

include_directories(${CODE_GEN_DIR})

add_library(code_gen ${SOURCE_FILES})

target_link_libraries(code_gen ir)