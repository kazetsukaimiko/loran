#include <RTOSEvent.h>
/*
void Task1( void *pvParameters );
void Task2( void *pvParameters );
*/

EventFunction_t REACTION;


void eventPollTask(void *pvParameters) {
    for( ;; ) {
        if (tasksInFlight()) {
            struct *Event e = retrieveNextTask();
            REACTION(e);
        } else {
            vTaskDelay( 10 / portTICK_PERIOD_MS );
        }
        vTaskDelay( 1 / portTICK_PERIOD_MS );
    }
}

void startEventWorker(EventFunction_t eventFunction) {
    REACTION = eventFunction;
    //xTaskCreate( TaskFunction_t pvTaskCode, const char * const pcName, uint16_t usStackDepth, void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask );
    xTaskCreate(eventPollTask, "eventPollTask", 128, NULL, 1, NULL);
    // Now call: vTaskStartScheduler(); 
}

struct Event  *retrieveNextTask() {
    struct Event e;
    return *e;
}

int taskInFlight() {
    return 0;
    // TODO Check a queue for tasks present.
}