set (
        SOURCE_FILES
        branch/branch.cpp
        constant/constant.cpp
        function/function.cpp
        instruction/instruction.cpp
        memory/memory.cpp
        operation/operation.cpp
        public/public.cpp
        variable/variable.cpp
)

include_directories(${BUILDER_DIR})

add_library(builder ${SOURCE_FILES})

target_link_libraries(builder ir)