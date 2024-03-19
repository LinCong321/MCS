set(
        SOURCE_FILES
        logger.cpp
)

include_directories(${UTILS_DIR})

add_library(utils ${SOURCE_FILES})