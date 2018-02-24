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
  message_t sensor_recv;
  //Scheduler declarations
  pthread_attr_t main_attr;
  pid_t mainpid;
  data_file = malloc(sizeof(10));
  logger_file =  malloc(sizeof(10));
  
  if (argc < 3)
	{
		printf("USAGE:  <data file> <logger file>\n");
		exit(1);
	}
	
	data_file = argv[1];
  logger_file = argv[2];


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
  for(i=0; i < NUM_THREADS; i++)
  {
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
        sprintf(sensor_recv.data.loggerData,"%s","DEBUG ERROR:pthread create error\n");
        sensor_recv.status = BAD;
        sensor_recv.error = errno;
        sprintf(sensor_recv.timestamp,"%s",getDateString());
        sensor_recv.type = QUERY_QUEUE;
        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
        {
         perror("mq_send");
        }
        else
        {
         printf("Core Dumped\n", nbytes);
        }
        
	}


/*********************************************************************************/
 pthread_join(threads[4], NULL);
 pthread_join(threads[0], NULL);
/*********************************************************************************/
}
