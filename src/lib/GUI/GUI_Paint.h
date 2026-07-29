#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include <stdint.h>

/**
 * Image attributes
**/
typedef struct {
    uint8_t *Image;
    uint16_t Width;
    uint16_t Height;
    uint16_t Colour;
    uint16_t Scale;
    uint16_t WidthByte;
    uint16_t HeightByte;
} PAINT;
extern PAINT Paint;


/**
 * Colours
**/
#define WHITE          0xfff
#define BLACK          0x000
#define BLUE           0x00f
#define BRED           0XF81F
#define GRED           0XFFE0
#define GBLUE          0X07FF
#define RED            0xf00
#define MAGENTA        0xF81F
#define GREEN          0x0f0
#define CYAN           0x6ff
#define YELLOW         0xff0
#define BROWN          0XBC40
#define BRRED          0XFC07
#define GRAY           0X8430

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK


void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Color);
void Paint_SelectImage(uint8_t *image);
void Paint_SetPixel(uint16_t X, uint16_t Y, uint16_t Colour);
void Paint_Clear(uint16_t Color);

#endif
