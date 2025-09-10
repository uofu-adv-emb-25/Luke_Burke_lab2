/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "hello_freertos_functions.h"

// Establish task priorities and stack sizes.
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

/**
 * Blink task - toggles the on-board LED every 500ms, but only
 * changes state every 11th time.
 */
void blink_task(__unused void *params) {
    int count = 0;
    bool on = false;
    hard_assert(cyw43_arch_init() == PICO_OK); // Initialize the WiFi chip, which also sets up the LED pin.
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        blink(&count, &on);
        vTaskDelay(500);
    }
}

/**
 * Main task - creates the blink task, then reads characters from
 * standard input, converting lower-case to upper-case and vice versa,
 * before echoing them back to standard output.
 */
void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while(c = getchar()) {
        putchar(change_case(c));
    }
}

/**
 * Main function - initializes stdio and FreeRTOS, then creates
 * the main task before starting the scheduler.
 */
int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler(); // This function should never return.
    return 0;
}
