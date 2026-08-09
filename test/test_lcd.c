#include "lcd.h"
#include "GUI_Paint.h"
#include "unity.h"
// #include "lcd.h"
#include "mock_GPIO.h"


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

void test_lcd_clear_white(void)
{
    GPIO_Write_Expect(LCD_DC_PIN, 1);

    LCD_1IN28_Clear(WHITE);
}
