#include "system.h"
#include "sequencer.h"
#include "led_driver.h"
#include "datetime_service.h"

static int i = 0;

void int_handler(){


  mq_close(temp_mq);
  mq_close(light_mq);
  mq_close(proc_mq);
  mq_close(log_mq);
  mq_unlink(SNDRCV_MQ3);
  mq_unlink(SNDRCV_MQ4);
  mq_unlink(SNDRCV_MQ5);
  mq_unlink(SNDRCV_MQ6);
  printf("\n caught crl c \n");
  exit(0);

}

void sighler (union sigval val){
  //printf("Handler entered with value :%d for %d times\n", val.sival_int, ++i);
  static int count;
  int nbytes;
  ++count;
  char *proc_msg = "push_to_proc";
  char *query_msg = "push_to_query";
  message_t sensor_data ;


  switch(count){

    case 1:
      printf("***triggered temp****\n");
      sensor_data.type = PROCESS_QUEUE;
      printf("size of message_t %d\n", sizeof(message_t));
     if((nbytes = mq_send(temp_mq, (char*)&sensor_data, sizeof(message_t), 30)) == ERROR)
      {
        perror("mq_send");
      }
      else
      {
        printf("1_T. sequencer to temp q: %d bytes: message successfully sent\n", nbytes);
      }
      break;

    case 2:
    printf("***triggered light****\n");
    sensor_data.type = PROCESS_QUEUE;
      if((nbytes = mq_send(light_mq, (char *)&sensor_data, sizeof(message_t), 30)) == ERROR)
      {
        perror("mq_send");
      }
      else
      {
        printf("1_L. sequencer to light q: message successfully sent\n");
      }
      
      break;
    default:
      break;
    
    case 3:
       printf("***triggered heartbeat****\n");
       blink_led(1000);
       count = 0;
  }
}

void *sequencerThread(void *threadp){

      
      printf("\n sequencer thread \n");
    
      int Ret;
      struct timeval tv;
      message_t sensor_recv;
      int nbytes;
      // printf("\n in timer \n");
    
      pthread_attr_t attr;
      pthread_attr_init( &attr );
    
      struct sched_param parm;
      parm.sched_priority = 50;
      pthread_attr_setschedparam(&attr, &parm);
    
      struct sigevent sig;
      sig.sigev_notify = SIGEV_THREAD;
      sig.sigev_notify_function = sighler;
      sig.sigev_value.sival_int =20;
      sig.sigev_notify_attributes = &attr;
    
      //create a new timer.
      timer_t timerid;
      Ret = timer_create(CLOCK_REALTIME, &sig, &timerid);
      if (Ret == 0)
          {
          struct itimerspec in, out;
          in.it_value.tv_sec = 4;
          in.it_value.tv_nsec = 0;
          in.it_interval.tv_sec = 0;
          in.it_interval.tv_nsec = 100000000;
          //issue the periodic timer request here.
          Ret = timer_settime(timerid, 0, &in, &out);
          while(1){
          
          }
          timer_delete(timerid);
          }
      else
      {
          sprintf(sensor_recv.data.loggerData,"%s","timer create error\n");
          sensor_recv.status = BAD;
          sensor_recv.error = Ret;
          gettimeofday(&tv,NULL);
          //sensor_recv.timestamp = tv.tv_sec;
          sprintf(sensor_recv.timestamp,"%s",getDateString());
          sensor_recv.type = LOG_FILE;
          if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
          {
           perror("mq_send");
          }
          else
          {
           printf("Core Dumped\n", nbytes);
          }
          printf("timer_create() failed with %d\n", Ret);
          exit(-1); 
      }

}
