#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/gpio.h>

#define BUTTON_PIN  4  // Example GPIO pin for the button
#define LED_PIN     2   // Example GPIO pin for an LED (you can change this)

void cyclic_task(void *pvParameters) {
    while (1) {
        // Print your student identifier every second
        printf("2012667\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
    }
}

void acyclic_task(void *pvParameters) {
    
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    while (1) {
        if (gpio_get_level(BUTTON_PIN) == 0) {
            // Button is pressed, print "ESP32"
            printf("ESP32\n");
            vTaskDelay(pdMS_TO_TICKS(1000));  // Delay to avoid multiple button presses
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // Poll the button every 10ms
    }
}

void app_main() {
    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);

    // Create the cyclic task
    xTaskCreate(cyclic_task, "cyclic_task", 2048, NULL, 2, NULL);

    // Create the acyclic task
    xTaskCreate(acyclic_task, "acyclic_task", 2048, NULL, 2, NULL);
}