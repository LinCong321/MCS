set (
        SOURCE_FILES
        constant/constant.cpp
        function/function.cpp
        operation/operation.cpp
        public/public.cpp
        variable/variable.cpp
)

include_directories(${CODE_GEN_DIR})

add_library(code_gen ${SOURCE_FILES})

target_link_libraries(code_gen ir)