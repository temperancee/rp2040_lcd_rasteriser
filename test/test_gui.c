#include "unity.h"
#include "GUI_Paint.h"
#include <stdint.h>

/*********************************
 *            Globals            *
 *********************************/

uint8_t fb[57600];

/********************************
 *     Set up and tear down     *
 ********************************/

void setUp(void) 
{
    Paint_NewImage(fb, 240, 240);
}

void tearDown(void) {} 


/**********************************
 *        Helper Functions        *
 **********************************/

void paint_clear_helper(uint8_t colour)
{
    Paint_Clear(colour);
    for (uint32_t i = 0; i < 57600; i++) {
        TEST_ASSERT_EQUAL_UINT8_MESSAGE(colour, Paint.Image[i], "Paint_Clear failed to set colour correctly!");
    }
}

void paint_setpixel_helper(uint8_t x, uint8_t y, uint8_t colour)
{
    Paint_SetPixel(x, y, colour);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(colour, Paint.Image[x + y*Paint.WidthByte], "Paint_SetPixel failed");
}

/*********************************
 *             Tests             *
 *********************************/

void test_paint_clear(void)
{
    // Test white ("max" colour)
    paint_clear_helper(0xff);
    // Test black ("min" colour)
    paint_clear_helper(0x00);
    // Test a random colour in the middle of the allowed range
    paint_clear_helper(0x78);
}

void test_paint_set_pixel(void)
{
    // White, max and min
    paint_setpixel_helper(0, 0, 0xff);
    paint_setpixel_helper(239, 239, 0xff);
    // Black, max and min
    paint_setpixel_helper(0, 0, 0x00);
    paint_setpixel_helper(239, 239, 0x00);
    // Middle colours, middle coordinates
    paint_setpixel_helper(203, 127, 0xa8);
    paint_setpixel_helper(28, 19, 0x7c);
}
