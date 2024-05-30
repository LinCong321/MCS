project(middle_end)

set (
        SOURCE_FILES
        loop_deletion/loop_deletion.cpp
        mem2reg_pass/mem2reg_pass.cpp
        mem2reg_pass/mem2reg_pass_helper.cpp
        pass_manager/pass_manager.cpp
)

include_directories(${MIDDLE_END_DIR})

add_library(middle_end ${SOURCE_FILES})

target_include_directories(middle_end PRIVATE ${FRONT_END_DIR})

target_link_libraries(middle_end ir)