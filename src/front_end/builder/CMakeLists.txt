set (
        SOURCE_FILES
        constant/constant.cpp
        function/function.cpp
        operation/operation.cpp
        public/public.cpp
        variable/variable.cpp
)

include_directories(${BUILDER_DIR})

add_library(builder ${SOURCE_FILES})

target_link_libraries(builder ir)