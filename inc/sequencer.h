#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "system.h"
#include <errno.h>
#include <semaphore.h>

sem_t lightSem, tempSem;
void sighler (union sigval val);
void *sequencerThread(void *threadp);


#endif
