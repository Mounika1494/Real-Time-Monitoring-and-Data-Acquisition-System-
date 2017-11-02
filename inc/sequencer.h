#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "system.h"
#include <errno.h>
#include <semaphore.h>

sem_t lightSem, tempSem;
<<<<<<< HEAD
sem_t sensor_finish_sem;
sem_t procSem, logSem;
=======
>>>>>>> 9686106a71d7cb035e8916a18592d36b8555fbe4
void sighler (union sigval val);
void *sequencerThread(void *threadp);


#endif
