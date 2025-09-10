#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

/**
 * Function required for Unity testing framework.
 */
void setUp(void) {}

/**
 * Function required for Unity testing framework.
 */
void tearDown(void) {}

/**
 * Test to ensure that a variable can be assigned and hold 
 * its value on the pico board.
 */
void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed."); // Throw an error if the statemnt is not true. 
}

/**
 * Test to ensure that division of two integers can be 
 * performed and hold its value on the pico board.
 */
void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value."); // Throw an error if the statemnt is not true. 
}

int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    while (1) {
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        sleep_ms(5000);
        UNITY_END();
    }
}
