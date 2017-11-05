#include "system.h"
#include "sequencer.h"
#include "error.h"
#include "led_driver.h"
#include "APDS9103.h"


//logger thread handler
void *loggerThread(void *threadp)
{

  FILE *fp_data = NULL;
  FILE *fp_logger = NULL;
  int nbytes,prio;
  message_t sensor_recv;
  uint8_t previous_state = 0;

 while(1){
   fp_data = fopen("data.txt", "a");
  if(fp_data == NULL)
  {
    printf("Couldn't log data %d\n",FILE_ERROR);
    exit(-1);
  }
   fp_logger = fopen("logger.txt", "a");
   if(fp_logger == NULL)
   {
     printf("Couldn't log status %d\n",FILE_ERROR);
     exit(-1);
   }
    if((nbytes = mq_receive(log_mq,(char*)&sensor_recv, MAX_MSG_SIZE, &prio)) == ERROR)
    {
      perror("mq_receive");
    }
    else
    {
      if (sensor_recv.type == QUERY_QUEUE) {//if query from temp/light is send to each other

        if(sensor_recv.sensor == LIGHT){
        
          fprintf(fp_data, "%s Queried Light is %f \n\n", sensor_recv.timestamp,sensor_recv.data.lightData);

        }
        else if (sensor_recv.sensor == TEMPERATURE){

          fprintf(fp_data, "%s Queried Temperature is %fC\n\n", sensor_recv.timestamp, sensor_recv.data.temperatureData);

        }

      }
      if (sensor_recv.type == PROCESS_QUEUE) {//if it is because of time out in sequencer
        
        if(sensor_recv.sensor == LIGHT){
          
          fprintf(fp_data, "%s Light is %f \n\n", sensor_recv.timestamp,sensor_recv.data.lightData);
  
        }
        else if (sensor_recv.sensor == TEMPERATURE){
  
          fprintf(fp_data, "%s Temperature is %fF \n\n", sensor_recv.timestamp, sensor_recv.data.temperatureData);
  
        }

      }
        else if (sensor_recv.type == LOG_FILE) {// If an error occured
  
          fprintf(fp_logger, "%s %s \n\n",sensor_recv.timestamp, sensor_recv.data.loggerData);
  
        }
      
      //Heart beat monitoring
      if (sensor_recv.status == BAD){
        blink_led(10000);
        previous_state =1;
      }
      if(sensor_recv.status == GOOD)
      {
        if(previous_state == 1)
        {
          previous_state = 0;
          APDS9301_init();
          APDS9301_poweron();
        }
      }
    }
    fclose(fp_data);
    fclose(fp_logger);
}
}
