// #include <cstddef>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <time.h>
#include <string.h>

struct QueueData {
    int requestID;
    char message [20];
    char reject;
};
struct TaskType {
    int taskID;
    char taskName [20];
};
QueueHandle_t xQueue;
struct TaskType Led = {.taskName = "led", .taskID = 0};
struct TaskType Pump = {.taskName = "pump", .taskID = 1};
struct TaskType Fan = {.taskName = "fan", .taskID = 2};

void xQueue_manager(void * pvParameter) {
    // create a queue, each slot contant a pointer, because arcording to the website,
    // this struct is "too big!"
    xQueue = xQueueCreate(10, sizeof(struct QueuneData *));
    if (xQueue == NULL) {
    printf ("Failed to create queue: not enough RAM.");
    }
    vTaskDelete(NULL);
}

void recepiton_Task(void * pvParameter) {
    time_t t;
    srand ((unsigned) time(&t));
    for (; ;) {
        while (xQueue == NULL) {
        // do mothing
        }
        int ranJob = (rand() % 4);
        int ranDelay = (rand() % 5) + 1;
        // allocate a dynamic space for the data, since our queue only save the "copy" of the pointer.
        struct QueueData *xData = malloc(sizeof(struct QueueData));
        if (xData != NULL) {
            switch(ranJob) {
                case 0:
                    xData->requestID = 0;
                    strcpy (xData->message, "LED");
                    xData->reject = 0;
                break;
                case 1:
                case 2:
                    xData->requestID = 2;
                    strcpy (xData->message, "FAN");
                    xData->reject = 0;
                break;
                case 3:
                    xData->requestID = 99;
                    strcpy (xData->message, "noob");
                    xData->reject = 0;
                break;
            }
        }
        if (xQueueSend(xQueue, (void *)&xData, 100) == errQUEUE_FULL) {
            printf("Failed to Import job with ID %d", ranJob);
        } else {
            // if malloc is not successful, it will return NULL.
            printf("Can’t allocate new struct");
        }
        vTaskDelay(pdMS_TO_TICKS(100 * ranDelay));
    }
    vTaskDelete(NULL);
}

void active_Task(void* pvParameter) {
    for (; ;) {
        struct TaskType *task = (struct TaskType *)pvParameter;
        struct QueueData *pRxMessage;
        if (xQueue != NULL) {
            if (xQueueReceive (xQueue, &pRxMessage, (TickType_t)10) == pdPASS) {
                if (pRxMessage->requestID == task->taskID) {
                    printf("%s\n", pRxMessage->message);
                    // always remember to free the memory when done.
                    free (pRxMessage);
                } else {
                    printf("%s: received %s, but it’s not my task\n",task->taskName,
                    pRxMessage ->message);
                    if (pRxMessage->reject < 2) {
                        pRxMessage->reject++;
                        xQueueSendToFront(xQueue, (void *)&pRxMessage, (TickType_t) 10);
                    } else {
                        printf("This task %s is rejected %d times, skiping the task\n",
                        pRxMessage ->message, pRxMessage->reject);
                        free (pRxMessage);
                    }
                }
            } else {
                // printf ("fan: queue empty\n");
            } 
        }
        vTaskDelay (pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    xTaskCreate(&xQueue_manager , "queue_manage", 2048, NULL, 10, NULL);
    xTaskCreate(&recepiton_Task, "rec", 2048, NULL, 10, NULL);
    xTaskCreate(&active_Task, "led", 2048, (void *)&Led, 10, NULL);
    xTaskCreate(&active_Task, "pump", 2048, (void *)&Pump, 10, NULL);
    xTaskCreate(&active_Task, "fan", 2048, (void *)&Fan, 10, NULL);
}
