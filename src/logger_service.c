#include "system.h"

void *loggerThread(void *threadp)
{
  printf("\n logger thread \n");
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

}
