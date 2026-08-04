aux_source_directory(. DIR_Touch_SRCS)

include_directories(../Hardware)

add_library(Touch ${DIR_Touch_SRCS})
target_link_libraries(Touch PUBLIC Hardware)
