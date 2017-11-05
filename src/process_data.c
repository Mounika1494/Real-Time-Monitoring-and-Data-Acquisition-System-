#include "system.h"
#include "sequencer.h"
#include <sys/time.h>
#include "TMP102.h"
#include "datetime_service.h"

void *processorThread(void *threadp)
{
  int nbytes,prio;
  message_t sensor_recv;
  int8_t current_state = 0;
  int8_t previous_state = 1;
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
        sensor_recv.type = PROCESS_QUEUE;
        sensor_recv.sensor = LIGHT;
        sprintf(sensor_recv.timestamp,"%s",getDateString());
        sensor_recv.status = GOOD;
        sensor_recv.data.lightData = sensor_recv.data.lightData;
        if(sensor_recv.data.lightData < 1)
            current_state = NIGHT;
        else
            current_state = DAY;
        if(current_state != previous_state)
        {
            sensor_recv.type = LOG_FILE;
            sensor_recv.status = GOOD;
            previous_state = current_state;
            sprintf(sensor_recv.data.loggerData,"%s","DEBUG INFO: light state changed\n");
        }
        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
         {
           perror("mq_send");
         }
         else
         {
           printf("3_L. process thread sending processed light to logmq: %d bytes: message successfully sent\n", nbytes);
         }
      }
      else if(sensor_recv.sensor == TEMPERATURE){
        sensor_recv.type = PROCESS_QUEUE;
        sensor_recv.sensor = TEMPERATURE;
        sprintf(sensor_recv.timestamp,"%s",getDateString());
        sensor_recv.status = GOOD;
        sensor_recv.data.temperatureData = temperature_F(sensor_recv.data.temperatureData);

        if((nbytes = mq_send(log_mq, (char *)&sensor_recv, sizeof(sensor_recv), 30)) == ERROR)
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
