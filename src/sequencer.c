#include "system.h"


void *sequencerThread(void *threadp)
{


  //create 2 timers (http://man7.org/linux/man-pages/man2/timer_create.2.html)
  // 2 signals and 2 signal handlers
  // signal handlers releases the semaphore
  printf("\n sequencer thread \n");
}
