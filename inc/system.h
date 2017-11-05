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
#include "datetime_service.h"

#define NUM_THREADS 5
#define POSIX_QUEUE
#define MAX_SIZE 60

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
  PROCESS_QUEUE =  1,
  QUERY_QUEUE,
  LOG_FILE
}destination_t;

typedef enum{
  BAD = 1,
  GOOD
}status_t;

typedef enum{
  LIGHT = 1,
  TEMPERATURE
}sensor_t;

typedef enum{
  NIGHT = 1,
  DAY,
  HOT,
  COLD
}state_t;

typedef struct
{
  destination_t type;
  sensor_t sensor;
  status_t status;
  state_t state;
  error_t error;
  char timestamp[40];
  data_t data;
}message_t;

void int_handler();
void *lightThread(void *threadp);
void *temperatureThread(void *threadp);
void *loggerThread(void *threadp);
void *sequencerThread(void *threadp);
void *processorThread(void *threadp);

#endif
