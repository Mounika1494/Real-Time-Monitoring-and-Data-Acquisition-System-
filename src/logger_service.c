#include "system.h"
#include "sequencer.h"




void *loggerThread(void *threadp)
{

  FILE *fp;
  int nbytes,prio;
  message_t sensor_recv;
  struct timeval tv;


 while(1){
   fp = fopen("logger.txt", "a");
    if((nbytes = mq_receive(log_mq,(char*)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {
      if(sensor_recv.sensor == LIGHT){
        // printf("receive: msg %d received with priority = %d, length = %d\n",
        //      sensor_recv->type, prio, nbytes);

        fprintf(fp, "Light is %f at timestamp %lu\n\n", sensor_recv.data.lightData, sensor_recv.timestamp);

      }
      else if (sensor_recv.sensor == TEMPERATURE){

        fprintf(fp, "Temperature is %f at timestamp %lu\n\n", sensor_recv.data.temperatureData, sensor_recv.timestamp);

      }

    }
    fclose(fp);
}


}
