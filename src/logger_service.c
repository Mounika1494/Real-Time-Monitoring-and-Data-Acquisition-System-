#include "system.h"
#include "sequencer.h"

void *loggerThread(void *threadp)
{

  //
  // switch (source):
  //
  // case logger:
  //     open message queue
  //     write to file
  // case light:
  //     pushback to queue (not yours!!!)
  // case light_interrupt:
  //     pushback to queue (not yours!!!)
  // case temperature:
  //     pushback to queue (not yours!!!)
  // case temperature_interrupt:
  //     pushback to queue (not yours!!!)
  // case error:
  //     pushback to queue (not yours!!!)
  //     tODO: if many error occur continously, send a signal to sequencer to reinitialize
  // default:
  //     pushback to queue (not yours!!!)
  printf("\n waiting in logSem \n");
  while(1){
    sem_wait(&logSem);
    printf("got into log thread\n");
  }

}
