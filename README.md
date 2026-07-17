# 3D Rasteriser for the RP2040

This project runs a 3D software rasteriser on the [Waveshare RP2040-Touch-LCD-1.28](https://www.waveshare.com/wiki/RP2040-Touch-LCD-1.28#GUI_API_Details), a 240$\times$240 LCD screen controlled by a RP2040 microcontroller. The rasteriser is written in C using the Pico C/C++ SDK. The driver for the LCD is the one included by the manufacturer, with some slight modifications to readability.

Here is a demo of a cube spinning in 3D space, viewed under an orthographic projection:

![Rasteriser Demo](rp2040_rasteriser_cube_spin.gif)

# Details

The RP2040 has two Cortex-M0+ processor cores, which lack floating point units (FPUs). This means floating point computations must be done in software, which can be very expensive. The libraries baked into the firmware of the Cortex-M0+ includes some instructions for speeding up floating point computations, but it still isn't as good as having a dedicated FPU. To get around this, I opted to write a small library of functions for Q16.16 (in [ARM notation](https://en.wikipedia.org/wiki/Fixed-point_arithmetic#Notations)) [fixed-point arithmetic](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) instead. These were a little complicated to implement, but they paid off in speeding up the rendering significantly.

Currently, the engine is capable of rendering triangles using Barycentric coordinates, and interpolating vertex colours across each triangle. Meshes can be manipulated using homogenous transformations as seen above, where the cube has had two rotations applied: one around the Y axis, and one around the Z axis, at a different rate.

# Running

Once you have cloned the repository, you can upload the current `main.uf2` file by using `picotool` to flash your own Waveshare RP2040 1.28 LCD Display.

# Building 

If you want to modify the code and build your changes, navigate to `build/` and run `cmake -DPICO_BOARD=waveshare_rp2040_touch_lcd_1.28 ..`, then run `make`. This will generate a new `main.uf2` which you can flash, again by using `picotool`.

This repository contains all the Pico C/C++ SDK files needed to build this project.

# License

No license, do as you will with the code.
