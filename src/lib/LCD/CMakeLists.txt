aux_source_directory(. DIR_LCD_SRCS)

include_directories(../Hardware)

add_library(LCD ${DIR_LCD_SRCS})
target_link_libraries(LCD PUBLIC Hardware pico_stdlib hardware_pwm hardware_dma hardware_spi)
