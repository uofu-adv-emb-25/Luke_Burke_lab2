#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unity.h>
#include "unity_config.h"
#include "hello_freertos_functions.h"

/**
 * Function required for Unity testing framework.
 */
void setUp(void) {}

/**
 * Function required for Unity testing framework.
 */
void tearDown(void) {}

/**
 * Tests to make sure the state does not change before 11 calls.
 */
void test_output_variable_no_state_change()
{
    int number = 0;
    bool state = false;
    blink(&number, &state);
    TEST_ASSERT_TRUE_MESSAGE(number == 1, "Count variable not incremented");
    TEST_ASSERT_TRUE_MESSAGE(state == false, "State variable changed incorrectly");

}

/**
 * Tests to make sure the state change occures after 11 calls.
 */
void test_output_variable_state_change()
{
    int number = 10;
    bool state = false;
    blink(&number, &state);
    TEST_ASSERT_TRUE_MESSAGE(number == 11, "Count variable not incremented");
    TEST_ASSERT_TRUE_MESSAGE(state == true, "State variable did not change correctly");
}

/**
 * Test to convert lowercase to uppercase.
 */
void test_lowercase_to_uppercase(void)
{ 
    TEST_ASSERT_TRUE_MESSAGE(change_case('a') == 'A', "Failed to convert lowercase to uppercase");
}

/**
 * Test to convert uppercase to lowercase.
 */
void test_uppercase_to_lowercase(void)
{
    TEST_ASSERT_TRUE_MESSAGE(change_case('A') == 'a', "Failed to convert uppercase to lowercase");
}

/**
 * Test to make sure non-letter characters are not changed.
 */
void test_nonletter_character(void)
{
    TEST_ASSERT_TRUE_MESSAGE(change_case('1') == '1', "Changed a non-letter character");
}



/**
 * Main function - initializes stdio, then runs the Unity tests.
 */
int main (void)
{
    stdio_init_all();
    sleep_ms(5000); // Give time for TTY to attach.
    while (1) {
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_output_variable_no_state_change);
        RUN_TEST(test_lowercase_to_uppercase);
        RUN_TEST(test_uppercase_to_lowercase);
        RUN_TEST(test_nonletter_character);
        printf("All done!\n");
        sleep_ms(5000);
        UNITY_END();
    }
}
