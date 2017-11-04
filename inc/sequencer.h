#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "system.h"
#include <errno.h>
#include <semaphore.h>
#include <mqueue.h>

#define MAX_MSG_SIZE 256
#define ERROR (-1)
#define SNDRCV_MQ3 "/send_receive_mq3"
#define SNDRCV_MQ4 "/send_receive_mq4"
#define SNDRCV_MQ5 "/send_receive_mq5"
#define SNDRCV_MQ6 "/send_receive_mq6"

sem_t lightSem, tempSem;
sem_t sensor_finish_sem;
sem_t procSem, logSem;

// message queue attributes
struct mq_attr mq_attr;

mqd_t temp_mq, light_mq;
mqd_t proc_mq, log_mq;

void sighler (union sigval val);
void *sequencerThread(void *threadp);


#endif
