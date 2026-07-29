#include "unity.h"
#include "matrix.h"


void setUp(void) {}

void tearDown(void) {} 

void test_mat_mult(void)
{
    matrix4q16 id1 = mat4_id();
    matrix4q16 id2 = mat4_id();

    // Test identity multiplication
    TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(id1.elements, mat_mat_multq16(&id1, &id2).elements, 16, "Identity multiplication failed!");
}
