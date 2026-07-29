# 3D Rasteriser for the RP2040

This project runs a 3D software rasteriser on the [Waveshare RP2040-Touch-LCD-1.28](https://www.waveshare.com/wiki/RP2040-Touch-LCD-1.28#GUI_API_Details), a $240 \times 240$ LCD screen controlled by a RP2040 microcontroller. The rasteriser is written in C using the Pico C/C++ SDK. The driver for the LCD is the one included by the manufacturer, with some slight modifications to readability, and a change to how the framebuffer is sent to the board. My code uses DMA driven SPI instead of standard SPI (although, currently, this is blocking DMA due to memory constraints, but I am actively working on this).

Here is a demo of a cube spinning in 3D space, viewed under an orthographic projection:

![Rasteriser Demo](media/rp2040_rasteriser_cube_spin.gif)

# Details

The RP2040 has two Cortex-M0+ processor cores, which lack floating point units (FPUs). This means floating point computations must be done in software, which can be very expensive. The libraries baked into the firmware of the Cortex-M0+ includes some instructions for speeding up floating point computations, but it still isn't as good as having a dedicated FPU. To get around this, I opted to write a small library of functions for Q16.16 (in [ARM notation](https://en.wikipedia.org/wiki/Fixed-point_arithmetic#Notations)) [fixed-point arithmetic](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) instead. These were a little complicated to implement, but they paid off in speeding up the rendering significantly.

Currently, the engine is capable of rendering triangles using Barycentric coordinates, and interpolating vertex colours across each triangle. Meshes can be manipulated using homogenous transformations as seen above, where the cube has had two rotations applied: one around the Y axis, and one around the Z axis, at a different rate.

## Pin connection

In case you want to run this on a [Waveshare LCD without an RP2040](https://www.waveshare.com/wiki/1.28inch_Touch_LCD), here is the pin connection diagram:

| Connection | Pin |
| --------| ---|
| I2C_SDA | 6  |
| I2C_SDA | 7  |
| DC      | 8  |
| CS      | 9  |
| SCK     | 10 |
| DIN     | 11 |
| RST     | 12 |
| BL      | 25 |
| BAT_ADC | 29 |


# Building and running

To build and run this project, you will need
- `cmake`
- `make`
- A copy of the pico-sdk on your system

Clone and navigate to the repository: 
```
git clone https://github.com/temperancee/rp2040_lcd_rasteriser.git
cd rp2040_lcd_rasteriser
```
Make sure you have set the PICO_SDK_PATH environment variable to your `pico-sdk` directory
```
export PICO_SDK_PATH="path/to/pico-sdk"
```
Then create a build directory and build the project
```
mkdir build
cmake -DPICO_BOARD=waveshare_rp2040_touch_lcd_1.28 ..
make
```
Finally, upload the generated `main.uf2` file to your board. This can be done by mounting the board as a USB device, using `picotool`, using `openocd`, and probably some other ways that I don't know about. See [Getting Started with Raspberry Pi Pico-series](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-2-getting-started-with-pico.pdf) for information on installing `picotool` or `openocd`, otherwise, press down the BOOTSEL key on your Pico, and it should show up in whatever file explorer you use.

# License

No license, do as you will with the code.
