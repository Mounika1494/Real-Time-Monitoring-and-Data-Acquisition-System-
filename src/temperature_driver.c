#include "system.h"
#include "sequencer.h"

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
  printf("\n waiting for temp semaphore\n");
  while(1){

    sem_wait(&tempSem);
    printf("\n temp thread \n");
    sem_post(&sensor_finish_sem);
  }

}
