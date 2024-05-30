project(back_end)

set (
        SOURCE_FILES
        allocation_order/allocation_order.cpp
        live_debug_variables/live_debug_variables.cpp
        reg_alloc/reg_alloc.cpp
        reg_alloc/reg_alloc_base.cpp
        generator/generator.cpp
)

include_directories(${BACK_END_DIR})

add_library(back_end ${SOURCE_FILES})

target_include_directories(back_end PRIVATE ${FRONT_END_DIR})

target_link_libraries(back_end ir)