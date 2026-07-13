aux_source_directory(. DIR_Rasteriser_SRCS)

include_directories(../Config)

add_library(Rasteriser ${DIR_Rasteriser_SRCS})
target_link_libraries(Rasteriser PUBLIC Config)
