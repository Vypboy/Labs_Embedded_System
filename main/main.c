#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>


void delay_ms(int ms){
    clock_t start = clock();
    while ((clock() - start)*1000 /CLOCKS_PER_SEC < ms );
}
void Task1 (void *pvParameters) {
    while(1){
        printf("Task 1 (High Priority Task) is blocked...\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void Task2(void *pvParameters) {
    while(1){
        printf("Task 2 (Medium Priority Task) is blocked...\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
        
void Task3(void *pvParameters) {
    while(1){
        printf("Task 3 (Low Priority Task) is running...\n");
        delay_ms(100);
        printf("Task 1 (High Priority Task) is ready...\n");
        xTaskCreatePinnedToCore(Task2, "Task 2", 1000, NULL, 2, NULL, 0);
        delay_ms(100);
        printf("Task 2 (Medium Priority Task) is ready...\n");
        xTaskCreatePinnedToCore(Task1, "Task 1", 1000, NULL, 3, NULL, 0);
        delay_ms(200);
        printf("Excecutes...\n");
        taskYIELD();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void vApplicationIdleHook (void) {
}


void app_main(void) {
    xTaskCreatePinnedToCore(Task3, "Task 3", 1000, NULL, 1, NULL, 0);
}
