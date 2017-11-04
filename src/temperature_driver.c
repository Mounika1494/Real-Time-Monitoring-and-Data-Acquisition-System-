#include "system.h"
#include "sequencer.h"
#include <sys/time.h>

void *temperatureThread(void *threadp)
{

  int nbytes,prio;
  message_t sensor_recv;
  struct timeval tv;


 while(1){

    printf("Waiting for temp_mq\n");
    if((nbytes = mq_receive(temp_mq, (char *)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {

      printf("temp receive: msg %d received with priority = %d, length = %d\n",
           sensor_recv.type, prio, nbytes);
      if(sensor_recv.type == PROCESS_QUEUE){
        // memset(&sensor_recv,0,sizeof(sensor_recv));
        gettimeofday(&tv,NULL);
        sensor_recv.sensor = TEMPERATURE;
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.status = GOOD;
        sensor_recv.data.temperatureData = 22.5;

        if((nbytes = mq_send(proc_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
       // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("2_T. temp thread sending proc q: %d bytes: message successfully sent\n", nbytes);
         }

      }

    }

  }

}
