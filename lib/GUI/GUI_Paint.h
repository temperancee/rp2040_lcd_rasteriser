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
#define WHITE          0xff
#define BLACK          0x00
#define BLUE           0x03
#define BRED           0XF81F
#define GRED           0XFFE0
#define GBLUE          0X07FF
#define RED            0xe0
#define MAGENTA        0xF81F
#define GREEN          0x1c
#define CYAN           0x7f
#define YELLOW         0xfc
#define BROWN          0XBC40
#define BRRED          0XFC07
#define GRAY           0X8430

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK


void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint8_t Color);
void Paint_SelectImage(uint8_t *image);
void Paint_SetPixel(uint16_t X, uint16_t Y, uint16_t Colour);
void Paint_SetScale(uint8_t scale);
void Paint_Clear(uint8_t Color);

#endif
