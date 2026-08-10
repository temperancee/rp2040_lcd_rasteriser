/*****************************************************************************
* | File      	:   lcd.h
* | Author      :   Waveshare team, edited by temperancee
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
******************************************************************************/
#ifndef __LCD_1IN28_H
#define __LCD_1IN28_H	
	
#include <stdint.h>
#include "SPI.h"

#define LCD_1IN28_HEIGHT 240
#define LCD_1IN28_WIDTH 240
#define LCD_SCREEN_SIZE LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH
#define LCD_8_BIT_FBUFFER_SIZE LCD_SCREEN_SIZE

#define HORIZONTAL 0
#define VERTICAL   1

enum {
    LCD_SPI_PORT = SPI_PORT_1
};

enum{
    LCD_DC_PIN = 8, // DC is data or command. DC=1 means data selected.
    LCD_CS_PIN = 9,
    LCD_CLK_PIN = 10,
    LCD_MOSI_PIN = 11,
    LCD_MISO_PIN = 12,
    LCD_RST_PIN = 13,
// When debugging, we run this code on a Pico W
// The Pico W does not expose GPIO25, so we have
// to reassign it. 
// This check determines if we are running on a Pico W
// #if defined(CYW43_WL_GPIO_LED_PIN)
    LCD_BL_PIN  = 15,
// #else
    // LCD_BL_PIN = 25,
// #endif
};

enum {
    SLEEP_MODE_ON = 0x10,
    SLEEP_MODE_OFF,
    PARTIAL_MODE_ON = 0x12, // Draw only to the partial area, designated in PARTIAL_AREA
    PARTIAL_MODE_OFF,
    DISPLAY_INVERSION_OFF = 0x20, // Inverts every colour bit, so 0xffff becomes 0x00, and 0xf800 (red) becomes 0x07ff (cyan) (in 16 bit mode)
    DISPLAY_INVERSION_ON,
    DISPLAY_OFF = 0x28, // Nothing is displayed, but note, the module doesn't actually turn off and lose power. Also, memory is not emptied or changed.
    DISPLAY_ON,
    COLUMN_ADDR_SET = 0x2A, // Defines the area of memory accessible by memory writes from the MCU running this code
    ROW_ADDR_SET, // As above
    MEMORY_WRITE = 0x2C,
    PARTIAL_AREA = 0x30, // Defines the display area in partial mode
    VERTICAL_SCROLLING_DEF = 0x33, // Not really sure how this works, but I don't think I need it since we aren't scrolling
    TEARING_EFFECT_LINE_OFF,
    TEARING_EFFECT_LINE_ON, // "Turn on the output signal from the TE signal line" - our module doesn't use this line
    MEMORY_ACCESS_CTRL = 0x36, // Defines the scanning direction of frame memory, i.e., rotates/flips the image depending on its value
    VERTICAL_SCROLLING_START_ADDR = 0x37, // Used with VERTICAL_SCROLLING_DEF: essentially defines how big a scroll is, by defining which row is displayed at the top of the screen after the current top value is scrolled away
    IDLE_MODE_OFF = 0x38,
    IDLE_MODE_ON, // In idle mode, only 8 colours are available
    COLMOD = 0x3A, // Sets the pixel format for MCU or RGB format, which we aren't using, so irrelevant
    WRITE_MEMORY_CONTINUE = 0x3C, // Writes from the host processor to the LCD's frame memory continuing from the pixel location last written to by WRITE_MEMORY_CONTINUE or MEMORY_WRITE

    INTER_REG_ENABLE1 = 0xFE,
    INTER_REG_ENABLE2 = 0xEF,
};

typedef struct {
	uint16_t WIDTH;
	uint16_t HEIGHT;
	uint8_t SCAN_DIR;
} LCD_1IN28_ATTRIBUTES;
extern LCD_1IN28_ATTRIBUTES LCD_1IN28;

void lcd_init(uint8_t scan_dir, uint8_t brightness);
void lcd_clear(uint16_t Color);
void lcd_display(uint8_t *Image);
#endif // __LCD_1IN28_H	
