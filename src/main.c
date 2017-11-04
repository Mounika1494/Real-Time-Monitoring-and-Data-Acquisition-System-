#include "system.h"
#include "sequencer.h"

int main (int argc, char *argv[])
{

  int8_t rc;
  int8_t i;

  pthread_t threads[NUM_THREADS];
  //Scheduler declarations
  pthread_attr_t rt_sched_attr[NUM_THREADS];
  int rt_max_prio, rt_min_prio;
  struct sched_param rt_param[NUM_THREADS];
  struct sched_param main_param;
  pthread_attr_t main_attr;
  pid_t mainpid;

  sem_init(&lightSem,0,0);
  sem_init(&tempSem,0,0);
  sem_init(&procSem,0,0);
  sem_init(&logSem,0,0);
  sem_init(&sensor_finish_sem,0,2);

  /* setup common message q attributes */
  mq_attr.mq_maxmsg = 20;
  mq_attr.mq_msgsize = MAX_MSG_SIZE;
  mq_attr.mq_flags = 0;

  temp_mq = mq_open(SNDRCV_MQ3, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  light_mq = mq_open(SNDRCV_MQ4, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  proc_mq = mq_open(SNDRCV_MQ5, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  log_mq = mq_open(SNDRCV_MQ6, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);


  mainpid=getpid();

  /* Scheduler */

  rc=sched_getparam(mainpid, &main_param);
  if (rc)
   {
     printf("ERROR; sched_setscheduler rc is %d\n", rc);
     perror(NULL);
     exit(-1);
   }
   //Obtain the priorities of the scheduler
  rt_max_prio = sched_get_priority_max(SCHED_FIFO);
  rt_min_prio = sched_get_priority_min(SCHED_FIFO);

  main_param.sched_priority=rt_max_prio ;
  rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
  if(rc < 0) perror("main_param");


  for(i=0; i < NUM_THREADS; i++)
  {
     rc=pthread_attr_init(&rt_sched_attr[i]);
     rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
     rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
     rt_param[i].sched_priority=rt_max_prio-i-1;
     pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
     threadParams[i].threadIdx=i;
   }
/*********************************************************************************/
  //initializeSensors();
  // Open msg queue and send loggerdata message
  signal(SIGINT, int_handler);
/*********************************************************************************/

	//Thread creation
  pthread_create(&threads[0],   // pointer to thread descriptor
		 &rt_sched_attr[0],     // use default attributes
		 lightThread, // thread function entry point
		 (void *)&(threadParams[0]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

  pthread_create(&threads[1],   // pointer to thread descriptor
		 &rt_sched_attr[0],     // use default attributes
		 temperatureThread, // thread function entry point
		 (void *)&(threadParams[1]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

  pthread_create(&threads[2],   // pointer to thread descriptor
		 &rt_sched_attr[2],     // use default attributes
		 processorThread, // thread function entry point
		 (void *)&(threadParams[2]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

  pthread_create(&threads[3],   // pointer to thread descriptor
		 &rt_sched_attr[3],     // use default attributes
		 loggerThread, // thread function entry point
		 (void *)&(threadParams[3]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

  pthread_create(&threads[4],   // pointer to thread descriptor
		 &rt_sched_attr[4],     // use default attributes
		 sequencerThread, // thread function entry point
		 (void *)&(threadParams[4]) // parameters to pass in		//Cant pass nothing so just pass a number
		);

    main_param.sched_priority=rt_max_prio - NUM_THREADS - 2;
    rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
    if(rc < 0) perror("main_param");

//sequence//

/*********************************************************************************/
 pthread_join(threads[4], NULL);
 pthread_join(threads[0], NULL);
 // pthread_join(threads[1],NULL);
/*********************************************************************************/
  printf("\nDone\n");
}
