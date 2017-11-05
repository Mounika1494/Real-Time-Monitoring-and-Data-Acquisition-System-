#include "system.h"
#include "sequencer.h"

int main (int argc, char *argv[])
{

  int8_t rc;
  int8_t i;
  int nbytes;
  int8_t error_flag = 0;
  int8_t errorno = 0;
  pthread_t threads[NUM_THREADS];
  struct timeval tv;
  message_t sensor_recv;
  //Scheduler declarations
  pthread_attr_t rt_sched_attr[NUM_THREADS];
  int rt_max_prio, rt_min_prio;
  struct sched_param rt_param[NUM_THREADS];
  struct sched_param main_param;
  pthread_attr_t main_attr;
  pid_t mainpid;


  /* setup common message q attributes */
  mq_attr.mq_maxmsg = 20;
  mq_attr.mq_msgsize = MAX_MSG_SIZE;
  mq_attr.mq_flags = 0;

  temp_mq = mq_open(SNDRCV_MQ3, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  if(temp_mq == (mqd_t)ERROR){ 
    error_flag = 1;  
  }
  
  light_mq = mq_open(SNDRCV_MQ4, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  if(light_mq == (mqd_t)ERROR){ 
    error_flag = 1; 
    
  }
  
  proc_mq = mq_open(SNDRCV_MQ5, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  if(proc_mq == (mqd_t)ERROR){ 
     error_flag = 1; 
  }
  
  log_mq = mq_open(SNDRCV_MQ6, O_CREAT|O_RDWR, S_IRWXU, &mq_attr);
  if(log_mq == (mqd_t)ERROR){ 
     error_flag = 1; 
  }
  if(error_flag == 1){
    printf("Error opening message queue\n");
    exit(-1);  
  }


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
//   rt_max_prio = sched_get_priority_max(SCHED_FIFO);
//   rt_min_prio = sched_get_priority_min(SCHED_FIFO);

//   main_param.sched_priority=rt_max_prio ;
//   rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
//   if(rc < 0) perror("main_param");


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
  errno = pthread_create(&threads[0],   // pointer to thread descriptor
                		 NULL,     // use default attributes
                		 lightThread, // thread function entry point
                		 (void *)&(threadParams[0]) // parameters to pass in		//Cant pass nothing so just pass a number
                		);
		if(errno){
		    error_flag = 1;
		}

  errno = pthread_create(&threads[1],   // pointer to thread descriptor
                		 NULL,     // use default attributes
                		 temperatureThread, // thread function entry point
                		 (void *)&(threadParams[1]) // parameters to pass in		//Cant pass nothing so just pass a number
                		);
		if(errno){
	        error_flag = 1;
	    }            		

  errno  = pthread_create(&threads[2],   // pointer to thread descriptor
                		 NULL,     // use default attributes
                		 processorThread, // thread function entry point
                		 (void *)&(threadParams[2]) // parameters to pass in		//Cant pass nothing so just pass a number
                		);
		if(errno){
            error_flag = 1;
        }        		

  errno = pthread_create(&threads[3],   // pointer to thread descriptor
                		 NULL,     // use default attributes
                		 loggerThread, // thread function entry point
                		 (void *)&(threadParams[3]) // parameters to pass in		//Cant pass nothing so just pass a number
                		);
		if(errno){
		    error_flag = 1;
		}
  errno = pthread_create(&threads[4],   // pointer to thread descriptor
                		 NULL,     // use default attributes
                		 sequencerThread, // thread function entry point
                		 (void *)&(threadParams[4]) // parameters to pass in		//Cant pass nothing so just pass a number
                		);
		if(errno){
		    error_flag = 1;
		}   
	if(error_flag == 1)
	{
        error_flag = 0;
        sprintf(sensor_recv.data.loggerData,"%s","pthread create error\n");
        sensor_recv.status = BAD;
        sensor_recv.error = errno;
        gettimeofday(&tv,NULL);
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.type = QUERY_QUEUE;
        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
           // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
        {
         perror("mq_send");
        }
        else
        {
         printf("Core Dumped\n", nbytes);
        }
        
	}

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
