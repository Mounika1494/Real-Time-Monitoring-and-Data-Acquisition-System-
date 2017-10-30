#include "system.h"

void *temperatureThread(void *threadp)
{

  // semwait ( we receive semaphore from signal handler of sequencer)
  // Initializing in main
  // Read temperature sensor value
  // Add any error encountered
  // Add current status
  // open message queue
  // If temperature value over a certain threshold (pushfront, update type enum to light_interrupt)
  // Else pushback
  printf("\n temp thread \n");
}
