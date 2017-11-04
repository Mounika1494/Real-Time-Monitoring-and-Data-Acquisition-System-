#include "system.h"
#include "sequencer.h"
#include <sys/time.h>

void *processorThread(void *threadp)
{
  int nbytes,prio;
  message_t sensor_recv;
  struct timeval tv;


 while(1){
   printf("\n waiting on process_mq \n");
    if((nbytes = mq_receive(proc_mq,(char*)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {
      printf("processed info received: msg type: %d, sensor: %d data: %f datareceived with priority = %d, length = %d\n",
           sensor_recv.type,sensor_recv.sensor,sensor_recv.data.lightData, prio, nbytes);

      if(sensor_recv.sensor == LIGHT){
        //memset(&sensor_recv,0,sizeof(sensor_recv));
        gettimeofday(&tv,NULL);
        sensor_recv.sensor = LIGHT;
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.status = GOOD;
        sensor_recv.data.lightData = sensor_recv.data.lightData;

        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
       // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("3_L. process thread sending processed light to logmq: %d bytes: message successfully sent\n", nbytes);
         }
      }
      else if(sensor_recv.sensor == TEMPERATURE){
        memset(&sensor_recv,0,sizeof(sensor_recv));
        gettimeofday(&tv,NULL);
        sensor_recv.sensor = TEMPERATURE;
        sensor_recv.timestamp = tv.tv_sec;
        sensor_recv.status = GOOD;
        sensor_recv.data.temperatureData = 70;

        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
       // if((nbytes = mq_send(temp_mq, proc_msg, 13, 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("3_T. process thread sending processed temperature to logmq: %d bytes: message successfully sent\n", nbytes);
         }

      }

    }

}
}