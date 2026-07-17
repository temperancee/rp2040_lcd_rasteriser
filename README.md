# 3D Rasteriser for the RP2040

This project runs a 3D software rasteriser on the [Waveshare RP2040-Touch-LCD-1.28](https://www.waveshare.com/wiki/RP2040-Touch-LCD-1.28#GUI_API_Details), a 240$\times$240 LCD screen controlled by a RP2040 microcontroller. The rasteriser is written in C using the Pico C/C++ SDK. The driver for the LCD is the one included by the manufacturer, with some slight modifications to readability.

Here is a demo of a cube spinning in 3D space, viewed under an orthographic projection:

![Rasteriser Demo](rp2040_rasteriser_cube_spin.gif)

## Running

Once you have cloned the repository, you can upload the current `main.uf2` file by using `picotool` to flash your own Waveshare RP2040 1.28 LCD Display.

## Building 

If you want to modify the code and build your changes, navigate to `build/` and run `cmake -DPICO_BOARD=waveshare_rp2040_touch_lcd_1.28 ..`, then run `make`. This will generate a new `main.uf2` which you can flash, again by using `picotool`.

This repository contains all the Pico C/C++ SDK files needed to build this project.

# License

No license, do as you will with the code.
