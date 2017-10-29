#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define NUM_THREADS 5
#define POSIX_QUEUE

typedef struct
{
  int threadIdx;
} threadParams_t;

threadParams_t threadParams[NUM_THREADS];

typedef union{

  uint8_t type;
  uint8_t status;
  uint8_t error;
  float_t lightData;
  float_t temperatureData;
  time_t timestamp;
}message_t;

void *lightThread(void *threadp);
void *temperatureThread(void *threadp);
void *loggerThread(void *threadp);
void *sequencerThread(void *threadp);
void *processorThread(void *threadp);

#endif
