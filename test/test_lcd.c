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
uint32_t addr_base;

/********************************
 *     Set up and tear down     *
 ********************************/

void setUp(void) 
{
    addr_base = 0x20006000;
}

void tearDown(void) {} 


/*********************************
 *            Helpers            *
 *********************************/


/*********************************
 *             Tests             *
 *********************************/


/* Colour LUT */
void test_clut_entry_address_index_0(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x20006000, clut_entry_addr(addr_base, 0));
}

void test_clut_entry_address_index_1(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x20006002, clut_entry_addr(addr_base, 1));
}

void test_clut_entry_address_index_255(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x200061fe, clut_entry_addr(addr_base, 255));
}


