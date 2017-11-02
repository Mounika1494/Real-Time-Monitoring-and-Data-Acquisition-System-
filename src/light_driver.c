#include "system.h"
#include "APDS9103.h"
#include "sequencer.h"

#ifdef POSIX_QUEUE
  #include <mqueue.h>
#else
  #include <message_service.h>
#endif

void *lightThread(void *threadp)
{

  // semwait ( we receive semaphore from signal handler of sequencer)
  // Initializing in main
  // Read Light sensor value
  // Add any error encountered
  // Add current status
  // open message queue
  // If light value over a vertain threshold (pushfront, update type enum to light_interrupt)
  // Else pushback
  printf("\n waiting for lightsem \n");
  while(1){
    sem_wait(&lightSem);
    printf("\n light thread \n");
    sem_post(&sensor_finish_sem);

  }

}
