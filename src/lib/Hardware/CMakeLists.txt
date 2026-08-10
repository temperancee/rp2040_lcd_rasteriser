aux_source_directory(. DIR_Hardware_SRCS)

add_library(Hardware ${DIR_Hardware_SRCS})
target_link_libraries(Hardware PUBLIC pico_stdlib pico_stdio pico_time hardware_spi hardware_gpio hardware_pwm hardware_dma)
