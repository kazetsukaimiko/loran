#include <FreeRTOS.h>

enum EventSource { LOCAL, CAN, LORA, MQTT };
enum EventType   { SENSOR,  }; // Maybe this should be something more dynamic

struct Event {
  enum EventSource source;
  enum EventType type;
  char originId[36];
  char originKey[64];
  char destinationId[36];
};


/**
 * Starts the event worker, needed before fireEvent.
*/
void startEventWorker();

/**
 * Stops the event worker and blows away any queues.
*/
void stopEventWorker();

/**
 * Non-blocking call to fire an event.
*/
void fireEvent(Event s);


/**
 * How many tasks are there in flight?
*/
int tasksInFlight();

/**
 * Gets the next task for processing.
*/
Event retrieveNextTask();