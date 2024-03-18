set(SOURCE_FILES basic_block.cpp context.cpp)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_library(IR ${SOURCE_FILES})

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(IR ${llvm_libs})