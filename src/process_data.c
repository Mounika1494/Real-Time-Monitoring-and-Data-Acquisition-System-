#include "system.h"
#include "sequencer.h"

void *processorThread(void *threadp)
{
  // wait on the queue
  // Read from message queue
  //switch case based on type of message_t

  // switch (source):
  //
  // case light:
  //
  //     calc luminosity from datasheet eqns
  //     pushback to queue with message type logger, data lightdata (calculated luminosity val)
  // case light_interrupt:
  //     identify dark or light_interrupt
  //     pushback to queue with message type logger, data loggerdata
  // case temperature:
  //     calc in degC from datasheet eqns
  //     pushback to queue with message type logger, data tempdata (calculated degC val)
  //
  // case temperature_interrupt:
  //     identify dark or light_interrupt
  //     pushback to queue with message type logger, data loggerdata
  //
  // case error:
  //     pushback to queue (not yours!!!)
  //
  // case logger:
  //     pushback to queue (not yours!!!)
  //
  // default:
  //
  //     pushback to queue (not yours!!!)
  //
  printf("\n process thread waiting on proc_sem\n");
  while(1){
    sem_wait(&procSem);
    printf("got into process thread\n");
  }
}
