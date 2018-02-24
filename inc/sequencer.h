/**********************************************************************************************************
* Copyright (C) 2017 by Mounika Reddy Edula
*
*Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
* @file sequencer.h
* @brief This is like a scheduler which triggers the threads
*
* This header file provides message queue variables,and thir respective virtual file systems
* 
* @author Mounika Reddy Edula
* @       Jay Krishnan
* @date September 11/4/2017
* @version 1.0
*
*/

#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "system.h"
#include <errno.h>
#include <semaphore.h>
#include <mqueue.h>


#define MAX_MSG_SIZE 256 //maximum message width
#define ERROR (-1) //Error when mq open fails
//virtual filesystem for respective queues
#define SNDRCV_MQ3 "/send_receive_mq3" 
#define SNDRCV_MQ4 "/send_receive_mq4"
#define SNDRCV_MQ5 "/send_receive_mq5"
#define SNDRCV_MQ6 "/send_receive_mq6"

// message queue attributes
struct mq_attr mq_attr;

//messgage queue for every thread
mqd_t temp_mq, light_mq;
mqd_t proc_mq, log_mq;

//signal handler for ctrl+c 
void sighler (union sigval val);

//Sequencer thread
void *sequencerThread(void *threadp);


#endif
