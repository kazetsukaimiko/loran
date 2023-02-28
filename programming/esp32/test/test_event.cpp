#include "unity.h"
#include "RTOSEvent.h"
#include <FreeRTOS.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void testEventsGetProcessed(void) {
  // test stuff

  struct Event e;
  e.source = 

  // Assign a value to the string using the strcpy function
  strcpy(e.myString, "Some text");
  fireEvent();
}

void test_function_should_doAlsoDoBlah(void) {
  // more test stuff
}

int runUnityTests(void) {
  UNITY_BEGIN();
  startEventWorker();
  vTaskStartScheduler(); 

  RUN_TEST(test_function_should_doBlahAndBlah);
  RUN_TEST(test_function_should_doAlsoDoBlah);


  return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
  * For native dev-platform or for some embedded frameworks

int main(void) {
  return runUnityTests();
}  */

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    UNITY_END();
}

/**
  * For Arduino framework
  */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  //delay(2000);

  runUnityTests();
}
void loop() {}

/**
  * For ESP-IDF framework
  */
void app_main() {
  runUnityTests();
}