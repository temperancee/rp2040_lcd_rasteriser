#include "unity.h"
// #include "lcd.h"


/***********************************
 *             Globals             *
 ***********************************/

static uint8_t fbuffer[57600];

/********************************
 *     Set up and tear down     *
 ********************************/

void setUp(void) 
{

}

void tearDown(void) {} 


/*********************************
 *             Tests             *
 *********************************/

void test_lcd_display_white(void)
{
    // LCD_Display(fbuffer, SPI_PORT) // SPI_PORT is a fake address (Dependecy Injection)
    TEST_ASSERT(1);
}

