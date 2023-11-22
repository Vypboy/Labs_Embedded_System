#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void Task1 (void *pvParameters) {
    while(1){
        printf("Task 1 (Event task) is running...\n");
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

void Task2(void *pvParameters) {
    while(1){
        printf("Task 2 (Idle Task) is running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
        
void vApplicationIdleHook(void){
    // ulIdleCycleCount++;
}


void app_main(void) {
    xTaskCreatePinnedToCore(Task1, "Task 1", 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(Task2, "Task 2", 1000, NULL, 0, NULL, 0);
}
            