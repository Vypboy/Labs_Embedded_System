#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include <stdio.h>

#define AHIHI_TIMER_ID 0
#define IHAHA_TIMER_ID 1
#define AHIHI_TOTAL_PRINTS 10
#define IHAHA_TOTAL_PRINTS 5

typedef struct {
    int id;
    int remaining_prints;
    int tick_count;
} custom_timer_data_t;

void timer_callback(TimerHandle_t xTimer) {
    custom_timer_data_t *timer_data = (custom_timer_data_t *) pvTimerGetTimerID(xTimer);

    timer_data->tick_count++;

    int prints_completed = (timer_data->id == AHIHI_TIMER_ID) ? 
                            AHIHI_TOTAL_PRINTS - timer_data->remaining_prints : 
                            IHAHA_TOTAL_PRINTS - timer_data->remaining_prints;

    if (timer_data->id == AHIHI_TIMER_ID) {
        printf("Second %d: ahihi (%d/%d)\n", timer_data->tick_count * 2, prints_completed + 1, AHIHI_TOTAL_PRINTS);
        if (--timer_data->remaining_prints <= 0) {
            xTimerStop(xTimer, 0);
        }
    } else if (timer_data->id == IHAHA_TIMER_ID) {
        printf("Second %d: ihaha (%d/%d)\n", timer_data->tick_count * 3, prints_completed + 1, IHAHA_TOTAL_PRINTS);
        if (--timer_data->remaining_prints <= 0) {
            xTimerStop(xTimer, 0);
        }
    }
}

void app_main(void) {
    static custom_timer_data_t ahihi_timer_data = { .id = AHIHI_TIMER_ID, .remaining_prints = AHIHI_TOTAL_PRINTS, .tick_count = 0 };
    static custom_timer_data_t ihaha_timer_data = { .id = IHAHA_TIMER_ID, .remaining_prints = IHAHA_TOTAL_PRINTS, .tick_count = 0 };

    TimerHandle_t ahihi_timer = xTimerCreate("AhihiTimer", pdMS_TO_TICKS(2000), pdTRUE, &ahihi_timer_data, timer_callback);
    TimerHandle_t ihaha_timer = xTimerCreate("IhahaTimer", pdMS_TO_TICKS(3000), pdTRUE, &ihaha_timer_data, timer_callback);

    xTimerStart(ahihi_timer, 0);
    xTimerStart(ihaha_timer, 0);
}
