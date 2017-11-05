/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
* @file system.h
* @brief all the structures used by system
*
*This header file provides functions to initialise i2c,write one byte,read one byte,read two byte
*
* @author Mounika Reddy Edula
* @       Jay Krishnan
* @date September 11/4/2017
* @version 1.0
*
*/
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

//thread creation
typedef struct
{
  int threadIdx;
} threadParams_t;

threadParams_t threadParams[NUM_THREADS];

//common data in the message_t structure
typedef union{

  float_t lightData;
  float_t temperatureData;
  char loggerData[MAX_SIZE];
}data_t;

//Destination type for different threads
typedef enum{
  PROCESS_QUEUE =  1,
  QUERY_QUEUE,
  LOG_FILE
}destination_t;

//Based on error
typedef enum{
  BAD = 1,
  GOOD
}status_t;

//To differentiate sensors
typedef enum{
  LIGHT = 1,
  TEMPERATURE
}sensor_t;

//State of environment 
typedef enum{
  NIGHT = 1,
  DAY,
  HOT,
  COLD
}state_t;

//Message structure for message queues
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

//thread handlers for all threads
void int_handler();//signal handler
void *lightThread(void *threadp);
void *temperatureThread(void *threadp);
void *loggerThread(void *threadp);
void *sequencerThread(void *threadp);
void *processorThread(void *threadp);
char *data_file;
char *logger_file;
#endif
