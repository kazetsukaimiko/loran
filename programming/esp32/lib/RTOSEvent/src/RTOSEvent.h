

enum EventSource { LOCAL, CAN, LORA, MQTT };
enum EventType   { SENSOR, BUTTON }; // Maybe this should be something more dynamic

struct Event {
  enum EventSource source;
  enum EventType type;
  char originId[36];
  char originKey[64];
  char destinationId[36];
};

typedef void (* EventFunction_t )( struct Event * );

/**
 * Starts the event worker, needed before fireEvent.
*/
void startEventWorker(EventFunction_t pvTaskCode);

/**
 * Stops the event worker and blows away any queues.
*/
void stopEventWorker();

/**
 * Non-blocking call to fire an event.
*/
void fireEvent(struct Event s);


/**
 * How many tasks are there in flight?
*/
int tasksInFlight();

/**
 * Gets the next task for processing.
*/
struct Event *retrieveNextTask();

