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
#include "error.h"

#define NUM_THREADS 5
#define POSIX_QUEUE
#define MAX_SIZE 20

typedef struct
{
  int threadIdx;
} threadParams_t;

threadParams_t threadParams[NUM_THREADS];

typedef union{

  float_t lightData;
  float_t temperatureData;
  char loggerData[MAX_SIZE];
}data_t;

typedef enum{
  LIGHT_SENSOR_DATA,
  LIGHT_SENSOR_INTERRUPT,
  TEMP_SENSOR_DATA,
  TEMP_SENSOR_INTERRUPT,
  LOGGER_DATA
}source_t;

typedef enum{
  BAD = 1,
  GOOD
}status_t;

typedef struct
{
  source_t type;
  status_t status;
  error_t error;
  time_t timestamp;
  data_t data;
}message_t;

void *lightThread(void *threadp);
void *temperatureThread(void *threadp);
void *loggerThread(void *threadp);
void *sequencerThread(void *threadp);
void *processorThread(void *threadp);

#endif
