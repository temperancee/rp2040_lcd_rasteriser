cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(RP2040_3D_Rasteriser)
pico_sdk_init()

add_subdirectory(./src/lib/Hardware)
add_subdirectory(./src/lib/GUI)
add_subdirectory(./src/lib/LCD)
add_subdirectory(./src/lib/Rasteriser)
# add_subdirectory(./src/lib/Touch)
# add_subdirectory(./src/lib/QMI8658)


include_directories(./src/lib/Hardware)
include_directories(./src/lib/GUI)
include_directories(./src/lib/LCD)
include_directories(./src/lib/Rasteriser)
# include_directories(./src/lib/Touch)
# include_directories(./src/lib/QMI8658)

add_executable(main ./src/main.c)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)
# Disable Pico C SDK float libraries (we use fixed-point only)
pico_set_float_implementation(main none)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main LCD GUI Rasteriser Hardware) # Hardware pico_stdlib hardware_spi ) #QMI8658 hardware_i2c Touch 
