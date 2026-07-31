#include "GUI_Paint.h"
#include <stdint.h>

PAINT Paint;

/**
 * @brief Initialise the Paint object
 * @param image - pointer to the framebuffer
 * @param Width - width of the image in pixels
 * @param Height - height of the image in pixels
 */
void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height)
{
    Paint.Image = image;

    Paint.Width = Width;
    Paint.Height = Height;

    Paint.WidthByte = Paint.Width; 
    Paint.HeightByte = Height;    
}

/**
 * @brief Select framebuffer
 * @param image - pointer to the framebuffer
 */
void Paint_SelectImage(uint8_t *image)
{
    Paint.Image = image;
}

/**
 * @brief Set pixel (X, Y) to colour Colour
 * @param X - x position
 * @param Y - y position
 * @param Colour - RGB332 colour to set the pixel to
 */
void Paint_SetPixel(uint16_t X, uint16_t Y, uint8_t Colour)
{
    if(X >= Paint.Width || Y >= Paint.Height){
        return;
    }

    uint32_t Addr = X + Y*Paint.WidthByte;
    Paint.Image[Addr] = Colour;
}

/**
 * @brief Fill the picture with Colour
 * @param Colour - the colour to fill the image with
 */
void Paint_Clear(uint8_t Colour)
{
    for (uint16_t Y = 0; Y < Paint.Height; Y++) {
        for (uint16_t X = 0; X < Paint.Width; X++ ) {
            uint32_t Addr = X + Y*Paint.WidthByte;
            Paint.Image[Addr] = Colour;
        }
    }
}

