#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "system.h"
#include <errno.h>
#include <semaphore.h>

sem_t lightSem, tempSem;
sem_t sensor_finish_sem;
sem_t procSem, logSem;
void sighler (union sigval val);
void *sequencerThread(void *threadp);


#endif
