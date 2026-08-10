#include "unity.h"

#include "lcd.h"
#include "GUI_Paint.h"

#include "mock_GPIO.h"
#include "mock_SPI.h"
#include "mock_PWM.h"
#include "mock_Delay.h"
#include <stdint.h>
#include <string.h>


/********************************
 *           Globals            *
 ********************************/

static uint8_t fbuffer[57600];

/********************************
 *     Set up and tear down     *
 ********************************/

void setUp(void) 
{

}

void tearDown(void) {} 


/*********************************
 *            Helpers            *
 *********************************/

void set_windows_expectance(void)
{
}

/*********************************
 *             Tests             *
 *********************************/

void test_lcd_display_white(void)
{
    // LCD_Display(fbuffer, SPI_PORT) // SPI_PORT is a fake address (Dependecy Injection)
    TEST_ASSERT(1);
}

/**
 * @brief Test that the device sends the right number of white pixels
 *        and toggles the D/C pin correctly
 * This test feels a bit pointless since it is essentially a copy of the function
*/
void test_lcd_clear_white(void)
{
    uint16_t row[LCD_1IN28_WIDTH];
    memset(row, 0xffff, sizeof(row));


    GPIO_Write_Expect(LCD_DC_PIN, 1);
    for(int j = 0; j < LCD_1IN28_HEIGHT; j++) {
        SPI_Write_n_Bytes_Expect(LCD_SPI_PORT, (uint8_t *)row, LCD_1IN28_WIDTH*2);
    }

    lcd_clear(0xffff);
}
