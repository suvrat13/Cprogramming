#include "unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_addition(void) {
    TEST_ASSERT_EQUAL(2, 1 + 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    return UNITY_END();
}