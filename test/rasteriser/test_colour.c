#include "unity.h"     // Compile/link in Unity test framework
#include "colour.h"     // Header file with no *.c file -- no compilation/linking

void setUp(void) {}    // Every test file requires this function;
                       // setUp() is called by the generated runner before each test case function

void tearDown(void) {} // Every test file requires this function;
                       // tearDown() is called by the generated runner after each test case function

// A test case function
void test_col3_to_hex_white(void)
{
    col3ub colour = {255, 255, 255};
    TEST_ASSERT_EQUAL(0xFF, col3_to_hex(colour)); // Foo_Function1() is under test (Unity assertion):
                                              //  (a) Calls Bar_AndGrill() from bar.h
                                              //  (b) Returns a byte compared to 0xFF
}


// Another test case function
void test_col3_to_hex_black(void)
{
    col3ub colour = {0, 0, 0};
    TEST_ASSERT_EQUAL(0x00, col3_to_hex(colour)); // Foo_Function1() is under test (Unity assertion):
                                              //  (a) Calls Bar_AndGrill() from bar.h
                                              //  (b) Returns a byte compared to 0xFF
}


// Another test case function
void test_col3_to_hex_middle_value(void)
{
    col3ub colour = {17, 100, 204};
    TEST_ASSERT_EQUAL(0x0a, col3_to_hex(colour)); // Foo_Function1() is under test (Unity assertion):
                                              //  (a) Calls Bar_AndGrill() from bar.h
                                              //  (b) Returns a byte compared to 0xFF
}
